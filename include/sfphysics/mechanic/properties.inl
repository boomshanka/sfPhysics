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


inline sfp::properties::properties()
{

}


inline sfp::properties::~properties()
{

}



inline float sfp::properties::mass() const
{
	return m_mass;
}


inline void sfp::properties::mass(float mass)
{
	m_mass = mass;
	m_density = m_mass / m_area;
}


inline float sfp::properties::density() const
{
	return m_density;
}


inline void sfp::properties::density(float dens)
{
	m_density = dens;
	m_mass = m_area * m_density;
}


inline float sfp::properties::area() const
{
	return m_area;
}


inline void sfp::properties::area(float area)
{
	m_area = area;
	m_mass = m_area * m_density;
}


inline float sfp::properties::inertia_moment() const
{
	return m_inertia_moment;
}


inline void sfp::properties::inertia_moment(float inertia)
{
	m_inertia_moment = inertia;
}


inline float sfp::properties::restitution() const
{
	return m_restitution;
}


inline void sfp::properties::restitution(float res)
{
	m_restitution = res;
}


inline float sfp::properties::dynamic_friction() const
{
	return m_dynamic_friction;
}


inline bool sfp::properties::dynamic_friction(float dyn)
{
	if(dyn > m_static_friction)
		return false;
	
	m_dynamic_friction = dyn;
	return true;
}


inline float sfp::properties::static_friction() const
{
	return m_static_friction;
}


inline bool sfp::properties::static_friction(float stat)
{
	if(stat < m_dynamic_friction)
		return false;
	
	m_static_friction = stat;
	return true;
}


inline bool sfp::properties::friction(float stat, float dyn)
{
	if(stat < dyn)
		return false;
	
	m_static_friction = stat;
	m_dynamic_friction = dyn;
	return true;
}


