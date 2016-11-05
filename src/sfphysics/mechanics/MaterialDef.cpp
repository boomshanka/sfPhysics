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


#include <sfphysics/mechanics/MaterialDef.hpp>


sfp::MaterialDef wood = sfp::MaterialDef(1, 0.5, 0.4, 0.6);
sfp::MaterialDef steel = sfp::MaterialDef(1, 0.5, 0.4, 0.6);
sfp::MaterialDef aluminium = sfp::MaterialDef(1, 0.5, 0.4, 0.6);
sfp::MaterialDef stone = sfp::MaterialDef(1, 0.5, 0.4, 0.6);
sfp::MaterialDef rubber = sfp::MaterialDef(1, 0.5, 0.4, 0.6);
sfp::MaterialDef soil = sfp::MaterialDef(1, 0.5, 0.4, 0.6);


sfp::MaterialDef::MaterialDef() :
m_density(1),
m_restitution(0.5),
m_dynamic_friction(0.4),
m_static_friction(0.6)
{

}

sfp::MaterialDef::MaterialDef(float dens, float res, float stat_friction, float dyn_friction) :
m_density(dens),
m_restitution(res),
m_dynamic_friction(stat_friction),
m_static_friction(dyn_friction)
{

}

sfp::MaterialDef::MaterialDef(const MaterialDef& mat) :
m_density(mat.m_density),	
m_restitution(mat.m_restitution),
m_dynamic_friction(mat.m_dynamic_friction),
m_static_friction(mat.m_static_friction)
{

}


float sfp::MaterialDef::density() const
{
	return m_density;
}

void sfp::MaterialDef::density(float dens)
{
	m_density = dens;
}


float sfp::MaterialDef::restitution() const
{
	return m_restitution;
}

void sfp::MaterialDef::restitution(float res)
{
	m_restitution = res;
}


float sfp::MaterialDef::dynamic_friction() const
{
	return m_dynamic_friction;
}


bool sfp::MaterialDef::dynamic_friction(float dyn)
{
	if(dyn > m_static_friction)
		return false;
	
	m_dynamic_friction = dyn;
	return true;
}


float sfp::MaterialDef::static_friction() const
{
	return m_static_friction;
}


bool sfp::MaterialDef::static_friction(float stat)
{
	if(stat < m_dynamic_friction)
		return false;
	
	m_static_friction = stat;
	return true;
}


bool sfp::MaterialDef::friction(float stat, float dyn)
{
	if(stat < dyn)
		return false;
	
	m_static_friction = stat;
	m_dynamic_friction = dyn;
	return true;
}


