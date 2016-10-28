/******************************************************************************
 **	sfPhysics - A simple 2D physics engine
 ** Copyright (C) 2011  Olaf Vogt aka Boomshanka
 ** 
 ** This program is free software; you can redistribute it and/or modify it
 ** under the terms of the GNU General Public License as published by the Free
 ** Software Foundation; either version 3 of the License, or (at your option)
 ** any later version. 
 ** 
 ** This program is distributed in the hope that it will be useful, but WITHOUT
 ** ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 ** FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 ** more details. 
 ** 
 ** You should have received a copy of the GNU General Public License along
 ** with this program; if not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************/


#include <sfphysics/geometry/polygon.hpp>
#include <sfphysics/geometry/triangle.hpp>


sfp::PolygonShape::PolygonShape() :
m_area(0), m_inertia_moment(0), m_center(sfp::vector2f(0, 0))
{

}

sfp::PolygonShape::~PolygonShape()
{

}


void sfp::PolygonShape::point_count(std::size_t count)
{
	m_points.resize(count);
	
	update();
}

std::size_t sfp::PolygonShape::point_count() const
{
	return m_points.size();
}


void sfp::PolygonShape::point(std::size_t pos, const sfp::vector2f& point)
{
	m_points[pos] = point;
	
	update();
}

const sfp::vector2f& sfp::PolygonShape::point(std::size_t pos) const
{
	return m_points[pos];
}


void sfp::PolygonShape::add_point(const sfp::vector2f& point)
{
	m_points.push_back(point);
	
	if(m_points.size() > 2)
		add_triangle(m_points.size() - 1);
}


void sfp::PolygonShape::clear()
{
	m_points.clear();
	m_area = 0;
	m_inertia_moment = 0;
	m_center = sfp::vector2f(0, 0);
}


float sfp::PolygonShape::area() const
{
	return m_area;
}


float sfp::PolygonShape::inertia_moment() const
{
	return m_inertia_moment;
}


sfp::vector2f sfp::PolygonShape::center() const
{
	return m_center;
}


sfp::boxf sfp::PolygonShape::bounds() const
{
	return bounds(transformf());
}


sfp::boxf sfp::PolygonShape::bounds(const transformf& transform) const
{
	if (!m_points.empty())
	{
		vector2f min = transform.transform(m_points[0]);
		vector2f max = min;
		
		for(unsigned int i = 1 ; i < m_points.size(); ++i)
		{
			vector2f point = transform.transform(m_points[i]);
			
			if (point.x < min.x)
			{
				min.x = point.x;
			}
			else if(point.x > max.x)
			{
				max.x = point.x;
			}
			
			if (point.y < min.y)
			{
				min.y = point.y;
			}
			else if(point.y > max.y)
			{
				max.y = point.y;
			}
		}
		
		return boxf(min, max);
	}
	
	return boxf();
}


unsigned int sfp::PolygonShape::separatingAxisCount() const
{
	return m_points.size();
}

sfp::vector2f sfp::PolygonShape::separatingAxis(unsigned int index) const
{
	separatingAxis(index, transformf());
}

sfp::vector2f sfp::PolygonShape::separatingAxis(unsigned int index, const transformf& transform) const
{
	if (index < m_points.size())
	{
		// special case at the end: Vector from last point to first point
		if (index == m_points.size()-1)
		{
			return transform.transform(m_points[0])-transform.transform(m_points[index]);
		}
		
		// Vector from point to next point
		return transform.transform(m_points[index+1])-transform.transform(m_points[index]);
	}
	
	return sfp::vector2f(1,0); // TODO oder (0,0) als invaliden vektor
}


sfp::minmaxf sfp::PolygonShape::project(const sfp::vector2f& axis) const
{
	return project(axis, sfp::transformf());
}


sfp::minmaxf sfp::PolygonShape::project(const sfp::vector2f& axis, const sfp::transformf& transform) const
{
	minmaxf projection;
	
	for (auto point : m_points)
	{
		projection.apply(dot_product(axis, transform.transform(point)));
	}
	
	return projection;
}


void sfp::PolygonShape::update()
{
	m_area = 0;
	m_inertia_moment = 0;
	m_center = sfp::vector2f(0, 0);
	
	for(std::size_t i = 2; i < m_points.size(); ++i)
	{
		add_triangle(i);
	}
}


// FIXME: Verschiebung muss einfacher gehen, nicht erst relative verschiebung zum alten punkt ausrechnen. das andere versteh ich nicht mehr
// FIXME: Nirgendwo wird geprüft ob polygon konvex ist
void sfp::PolygonShape::add_triangle(std::size_t pos)
{
	triangle<float> tri(m_points[0], m_points[pos - 1], m_points[pos]);
	float tri_area = tri.area();
	
	// Move center of gravity
	vector2f diff(tri.center() - m_center);
	float factor = tri_area / (tri_area + m_area);
	
	// Trägheitsmomente erhöhen und addieren
	m_inertia_moment += m_area * vector2f(factor * diff).squaredLength();
	m_inertia_moment += tri.inertia_moment() + tri_area * vector2f((1 - factor) * diff).squaredLength();
	
	// Add area and move center
	m_area += tri_area;
	m_center += factor * diff;
}


std::unique_ptr<sfp::Shape> sfp::PolygonShape::copy() const
{
	PolygonShape* polygon = new PolygonShape();
	
	polygon->m_points = m_points;
	polygon->m_area = m_area;
	polygon->m_inertia_moment = m_inertia_moment;
	polygon->m_center = m_center;
	
	return std::unique_ptr<Shape>{polygon};
}


void sfp::PolygonShape::accept(sfp::ShapeDispatcher& dispatcher) const
{
	dispatcher.dispatch(*this);
}


