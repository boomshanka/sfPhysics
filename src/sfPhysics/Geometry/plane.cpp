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


#include <sfPhysics/Geometry/plane.hpp>

#include <limits>


sfp::PlaneShape::PlaneShape(const sfp::vector2f& normal, const sfp::vector2f& center) :
m_normal(normal),
m_center(center)
{

}

sfp::PlaneShape::~PlaneShape()
{

}


sfp::vector2f sfp::PlaneShape::center() const
{
	return m_center;
}

void sfp::PlaneShape::center(const sfp::vector2f& center)
{
	m_center = center;
}


const sfp::vector2f& sfp::PlaneShape::normal() const
{
	return m_normal;
}


sfp::vector2f sfp::PlaneShape::normal(const sfp::transformf& transform) const
{
	return transform.transform(m_center+m_normal) - transform.transform(m_center);
}


void sfp::PlaneShape::normal(const sfp::vector2f& normal)
{
	m_normal = normal;
}


float sfp::PlaneShape::area() const
{
	return std::numeric_limits<float>::infinity();
}


float sfp::PlaneShape::inertiaMoment() const
{
	return std::numeric_limits<float>::infinity();
}


sfp::boxf sfp::PlaneShape::bounds() const
{
	return bounds(transformf());
}


sfp::boxf sfp::PlaneShape::bounds(const sfp::transformf& transform) const
{
	float inf = std::numeric_limits<float>::infinity();
	vector2f normal = transform.transform(m_normal) - transform.transform(vector2f(0,0));
	
	if (normal == vector2f(1, 0))
	{
		return boxf(vector2f(-inf, -inf), vector2f(transform.transform(m_center).x, inf));
	}
	else if (normal == vector2f(-1, 0))
	{
		return boxf(vector2f(transform.transform(m_center).x, -inf), vector2f(inf, inf));
	}
	else if (normal == vector2f(0, 1))
	{
		return boxf(vector2f(-inf, -inf), vector2f(inf, transform.transform(m_center).y));
	}
	else if (normal == vector2f(0, -1))
	{
		return boxf(vector2f(-inf, transform.transform(m_center).y), vector2f(inf, inf));
	}
	
	return boxf(vector2f(-inf, -inf), vector2f(inf, inf));
}


sfp::minmaxf sfp::PlaneShape::project(const sfp::vector2f& axis) const
{
	// since plane is infinite projection doesn't make sense in most cases
	return minmaxf();
}


sfp::minmaxf sfp::PlaneShape::project(const sfp::vector2f& axis, const sfp::transformf& transform) const
{
	// since plane is infinite projection doesn't make sense in most cases
	return minmaxf();
}


std::unique_ptr<sfp::Shape> sfp::PlaneShape::copy() const
{
	return std::unique_ptr<Shape>{new PlaneShape(m_normal, m_center)};
}


void sfp::PlaneShape::accept(sfp::ShapeDispatcher& dispatcher) const
{
	dispatcher.dispatch(*this);
}


