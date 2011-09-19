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


#include <sfPhysics/Mechanic/Hinge.hpp>



sfp::Hinge::Hinge()
:Linkable()
{

}


sfp::Hinge::Hinge(sfp::Object* one, sfp::Object* two, const sfp::Vector2f& vone, const sfp::Vector2f& vtwo)
:Linkable(one, two, vone, vtwo)
{

}



float sfp::Hinge::RenderForces(sfp::Uint32 time)
{
	sfp::Vector2f force;
	
	if(Linkable::second != NULL)
	{
		force = Linkable::second->GetImpulse(Linkable::secondlink);
	}
	
	if(Linkable::first != NULL)
	{
		force -= Linkable::first->GetImpulse(Linkable::firstlink);
	}
	
	
	if(Linkable::first != NULL) Linkable::first->Impulse(Linkable::firstlink, force);
	if(Linkable::second != NULL) Linkable::second->Impulse(Linkable::secondlink, -force);
	
	return force.GetForce();
}



