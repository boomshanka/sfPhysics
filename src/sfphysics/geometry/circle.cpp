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
 

#include <sfphysics/geometry/circle>

#include <sfphysics/geometry/trigonometry>
#include <sfphysics/geometry/math>


sfp::circle::circle(const sfp::vector2f& center, float radius) :
m_center(center), m_radius(radius)
{

}


sfp::circle::~circle()
{

}



sfp::vector2f sfp::circle::center() const
{
	return m_center;
}

void sfp::circle::center(const sfp::vector2f& center)
{
	m_center = center;
}


float sfp::circle::radius() const
{
	return m_radius;
}

void sfp::circle::radius(float radius)
{
	m_radius = radius;
}


float sfp::circle::area() const
{
	return trigf::pi * mathf::square(m_radius);
}


float sfp::circle::inertia_moment() const
{
	return 0.5 * trigf::pi * mathf::square(mathf::square(m_radius)); // 0.5 * m * r² ; m = pi r² -> 0.5 * pi * r^4
}


