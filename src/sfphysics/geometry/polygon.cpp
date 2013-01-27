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


#include <sfphysics/geometry/polygon>

#include <sfphysics/geometry/triangle>



sfp::polygon::polygon() :
m_area(0), m_inertia_moment(0), m_center(sfp::vector2f(0, 0))
{

}

sfp::polygon::~polygon()
{

}


void sfp::polygon::point_count(std::size_t count)
{
	m_points.resize(count);
	
	update();
}

std::size_t sfp::polygon::point_count() const
{
	return m_points.size();
}


void sfp::polygon::point(std::size_t pos, const sfp::vector2f& point)
{
	m_points[pos] = point;
	
	update();
}

const sfp::vector2f& sfp::polygon::point(std::size_t pos) const
{
	return m_points[pos];
}


void sfp::polygon::add_point(const sfp::vector2f& point)
{
	m_points.push_back(point);
	
	if(m_points.size() > 2)
		add_triangle(m_points.size() - 1);
}


void sfp::polygon::clear()
{
	m_points.clear();
	m_area = 0;
	m_inertia_moment = 0;
	m_center = sfp::vector2f(0, 0);
}


float sfp::polygon::area() const
{
	return m_area;
}


float sfp::polygon::inertia_moment() const
{
	return m_inertia_moment;
}


sfp::vector2f sfp::polygon::center() const
{
	return m_center;
}


void sfp::polygon::update()
{
	m_area = 0;
	m_inertia_moment = 0;
	m_center = sfp::vector2f(0, 0);
	
	for(std::size_t i = 2; i < m_points.size(); ++i)
	{
		add_triangle(i);
	}
}


void sfp::polygon::add_triangle(std::size_t pos)
{
	triangle<float> tri(m_points[0], m_points[pos - 1], m_points[pos]);
	float tri_area = tri.area();
	
	// Schwerpunktsverschiebung
	vector2f diff(tri.center() - m_center);
	float factor = tri_area / (tri_area + m_area);
	
	// Trägheitsmomente erhöhen und addieren
	m_inertia_moment += m_area * vector2f(factor * diff).get_squared_length();
	m_inertia_moment += tri.inertia_moment() + tri_area * vector2f((1 - factor) * diff).get_squared_length();
	
	// Werte addieren
	m_area += tri_area;
	m_center += factor * diff;
}


