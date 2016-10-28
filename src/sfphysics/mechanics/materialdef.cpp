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


#include <sfphysics/mechanics/materialdef.hpp>


sfp::materialdef wood = sfp::materialdef(1, 0.5, 0.4, 0.6);
sfp::materialdef steel = sfp::materialdef(1, 0.5, 0.4, 0.6);
sfp::materialdef aluminium = sfp::materialdef(1, 0.5, 0.4, 0.6);
sfp::materialdef stone = sfp::materialdef(1, 0.5, 0.4, 0.6);
sfp::materialdef rubber = sfp::materialdef(1, 0.5, 0.4, 0.6);
sfp::materialdef soil = sfp::materialdef(1, 0.5, 0.4, 0.6);


sfp::materialdef::materialdef() :
m_density(1),
m_restitution(0.5),
m_dynamic_friction(0.4),
m_static_friction(0.6)
{

}

sfp::materialdef::materialdef(float dens, float res, float stat_friction, float dyn_friction) :
m_density(dens),
m_restitution(res),
m_dynamic_friction(stat_friction),
m_static_friction(dyn_friction)
{

}

sfp::materialdef::materialdef(const materialdef& mat) :
m_density(mat.m_density),	
m_restitution(mat.m_restitution),
m_dynamic_friction(mat.m_dynamic_friction),
m_static_friction(mat.m_static_friction)
{

}


float sfp::materialdef::density() const
{
	return m_density;
}

void sfp::materialdef::density(float dens)
{
	m_density = dens;
}


float sfp::materialdef::restitution() const
{
	return m_restitution;
}

void sfp::materialdef::restitution(float res)
{
	m_restitution = res;
}


float sfp::materialdef::dynamic_friction() const
{
	return m_dynamic_friction;
}


bool sfp::materialdef::dynamic_friction(float dyn)
{
	if(dyn > m_static_friction)
		return false;
	
	m_dynamic_friction = dyn;
	return true;
}


float sfp::materialdef::static_friction() const
{
	return m_static_friction;
}


bool sfp::materialdef::static_friction(float stat)
{
	if(stat < m_dynamic_friction)
		return false;
	
	m_static_friction = stat;
	return true;
}


bool sfp::materialdef::friction(float stat, float dyn)
{
	if(stat < dyn)
		return false;
	
	m_static_friction = stat;
	m_dynamic_friction = dyn;
	return true;
}


