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


#include <sfPhysics/System/Spring.hpp>



sfp::Spring::Spring()
:Linkable(), myLength(0), mySpringConstant(10), myDamping(0.1), myIsQuadratic(false)
{

}


sfp::Spring::Spring(sfp::Object* one, sfp::Object* two, const sfp::Vector2f& vone, const sfp::Vector2f& vtwo, float length, float springconst, float damping, bool quadratic)
:Linkable(one, two, vone, vtwo), myLength(length), mySpringConstant(springconst), myDamping(damping), myIsQuadratic(quadratic)
{

}



float sfp::Spring::RenderForces(sfp::Uint32 time)
{
	sfp::Vector2f distance;
	sfp::Vector2f velocity;
	
	if(Linkable::second != NULL)
	{
		distance = Linkable::second->ToGlobal(Linkable::secondlink);
		velocity = -Linkable::second->GetMovement(Linkable::secondlink);
	}
	else
	{
		distance = Linkable::secondlink;
	}
	
	if(Linkable::first != NULL)
	{
		distance -= Linkable::first->ToGlobal(Linkable::firstlink);
		velocity += Linkable::first->GetMovement(Linkable::firstlink);
	}
	else
	{
		distance -= Linkable::firstlink;
	}
	
	float length = distance.GetForce();
	distance /= length;
	
	length -= myLength;
	
	float force = length * mySpringConstant * (static_cast<float>(time) / 1000.f);
	if(myIsQuadratic) force *= length; //FIXME Brauch ich das / stimmt das?
	
	// Dämpfung
	force -= myDamping * DotProduct(velocity, distance) * (static_cast<float>(time) / 1000.f);
	
	if(Linkable::first != NULL) Linkable::first->Impulse(Linkable::firstlink, distance, force);
	if(Linkable::second != NULL) Linkable::second->Impulse(Linkable::secondlink, -distance, force);
	
	return force;
}


