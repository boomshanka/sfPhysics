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


#include <sfphysics/geometry/plane>


sfp::plane::plane(const sfp::vector2f& center, const sfp::vector2f& normal) :
m_center(center), m_normal(normal)
{

}

sfp::plane::~plane()
{

}


sfp::vector2f sfp::plane::center() const
{
	return m_center;
}

void sfp::plane::center(const sfp::vector2f& center)
{
	m_center = center;
}


const sfp::vector2f& sfp::plane::normal() const
{
	return m_normal;
}


void sfp::plane::normal(const sfp::vector2f& normal)
{
	m_normal = normal;
}


float sfp::plane::area() const
{
	return 1;
}


float sfp::plane::inertia_moment() const
{
	return 1;
}


