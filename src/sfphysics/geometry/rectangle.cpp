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


#include <sfphysics/geometry/rectangle>

#include <sfphysics/geometry/math>


sfp::rectangle::rectangle(const sfp::vector2f& center, const sfp::vector2f& size) :
m_center(center), m_size(size)
{

}

sfp::rectangle::~rectangle()
{

}


sfp::vector2f sfp::rectangle::center() const
{
	return m_center;
}


void sfp::rectangle::center(const sfp::vector2f& center)
{
	m_center = center;
}


const sfp::vector2f& sfp::rectangle::size() const
{
	return m_size;
}


void sfp::rectangle::size(const sfp::vector2f& size)
{
	m_size = size;
}


float sfp::rectangle::area() const
{
	return m_size.x * m_size.y;
}


float sfp::rectangle::inertia_moment() const
{
	return area() * (sfp::mathf::square(m_size.x) + sfp::mathf::square(m_size.y)) / 12.f;
}


