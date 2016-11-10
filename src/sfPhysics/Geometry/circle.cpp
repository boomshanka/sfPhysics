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
 

#include <sfPhysics/Geometry/circle.hpp>
#include <sfPhysics/Geometry/trigonometry.hpp>


sfp::CircleShape::CircleShape(float radius, const sfp::vector2f& center) :
m_radius(radius),
m_center(center)
{

}


sfp::CircleShape::~CircleShape()
{

}



sfp::vector2f sfp::CircleShape::center() const
{
	return m_center;
}

void sfp::CircleShape::center(const sfp::vector2f& center)
{
	m_center = center;
}


float sfp::CircleShape::radius() const
{
	return m_radius;
}

void sfp::CircleShape::radius(float radius)
{
	m_radius = radius;
}


float sfp::CircleShape::area() const
{
	return trigf::pi * m_radius*m_radius;
}


float sfp::CircleShape::inertiaMoment() const
{
	// 0.5 * m * r^2 ; m = pi r^2 -> 0.5 * pi * r^4
	return 0.5 * trigf::pi * m_radius*m_radius*m_radius*m_radius;
}


sfp::boxf sfp::CircleShape::bounds() const
{
	return boxf(m_center - vector2f(m_radius, m_radius), m_center + vector2f(m_radius, m_radius));
}


sfp::boxf sfp::CircleShape::bounds(const sfp::transformf& transform) const
{
	// Since the transformation contains only translation and rotation the size stays as it is
	vector2f transformed_center(transform.transform(m_center));
	return boxf(transformed_center - vector2f(m_radius, m_radius), transformed_center + vector2f(m_radius, m_radius));
}


sfp::minmaxf sfp::CircleShape::project(const sfp::vector2f& axis) const
{
	return project(axis, sfp::transformf());
}


sfp::minmaxf sfp::CircleShape::project(const sfp::vector2f& axis, const sfp::transformf& transform) const
{
	minmaxf projection;
	float center = dot_product(axis, transform.transform(m_center));
	
	return projection.apply(center - m_radius).apply(center + m_radius);
}



std::unique_ptr<sfp::Shape> sfp::CircleShape::copy() const
{
	return std::unique_ptr<Shape>{new CircleShape(m_radius, m_center)};
}


void sfp::CircleShape::accept(sfp::ShapeDispatcher& dispatcher) const
{
	dispatcher.dispatch(*this);
}



