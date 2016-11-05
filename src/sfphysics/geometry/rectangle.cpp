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


#include <sfphysics/geometry/rectangle.hpp>


sfp::RectangleShape::RectangleShape(const sfp::vector2f& size, const sfp::vector2f& center) :
m_size(size),
m_center(center)
{

}

sfp::RectangleShape::~RectangleShape()
{

}


sfp::vector2f sfp::RectangleShape::center() const
{
	return m_center;
}


void sfp::RectangleShape::center(const sfp::vector2f& center)
{
	m_center = center;
}


const sfp::vector2f& sfp::RectangleShape::size() const
{
	return m_size;
}


void sfp::RectangleShape::size(const sfp::vector2f& size)
{
	m_size = size;
}


float sfp::RectangleShape::area() const
{
	return m_size.x * m_size.y;
}


float sfp::RectangleShape::inertiaMoment() const
{
	return area() * m_size.squaredLength() / 12.f;
}


sfp::boxf sfp::RectangleShape::bounds() const
{
	return boxf(m_center - (m_size/2.f), m_center + (m_size/2.f));
}


sfp::boxf sfp::RectangleShape::bounds(const transformf& transform) const
{
	vector2f min, max;
	min = max = transform.transform(corner(0));
	for (vector2f n : {corner(1), corner(2), corner(3)})
	{
		n = transform.transform(n);
		if (n.x > max.x)
		{
			max.x = n.x;
		}
		else if (n.x < min.x)
		{
			min.x = n.x;
		}
		
		if (n.y > max.y)
		{
			max.y = n.y;
		}
		else if (n.y < min.y)
		{
			min.y = n.y;
		}
	}
	
	return boxf(min, max);
}

/*
sfp::vector2f sfp::RectangleShape::separatingAxis(unsigned int index, const transformf& transform) const
{
	if (index == 0)
	{
		return transform.transform(corner(0))-transform.transform(corner(1));
	}
	else // TODO: nur für index 1, alle andere invalid
	{
		return transform.transform(corner(1))-transform.transform(corner(2));
	}
}*/


sfp::minmaxf sfp::RectangleShape::project(const sfp::vector2f& axis) const
{
	return project(axis, sfp::transformf());
}


sfp::minmaxf sfp::RectangleShape::project(const sfp::vector2f& axis, const sfp::transformf& transform) const
{
	minmaxf projection;
	
	for (sfp::vector2f point : {corner(0), corner(1), corner(2), corner(3)})
	{
		projection.apply(dot_product(axis, transform.transform(point)));
	}
	
	return projection;
}


std::unique_ptr<sfp::Shape> sfp::RectangleShape::copy() const
{
	return std::unique_ptr<Shape>{new RectangleShape(m_size, m_center)};
}


void sfp::RectangleShape::accept(sfp::ShapeDispatcher& dispatcher) const
{
	dispatcher.dispatch(*this);
}


sfp::vector2f sfp::RectangleShape::corner(unsigned int i) const
{
	switch(i)
	{
		case 0:
			return m_center + (vector2f(-m_size.x, -m_size.y) / 2.f);
			
		case 1:
			return m_center + (vector2f(m_size.x, -m_size.y) / 2.f);
			
		case 2:
			return m_center + (vector2f(m_size.x, m_size.y) / 2.f);
			
		default:
			return m_center + (vector2f(-m_size.x, m_size.y) / 2.f);
	}
}

