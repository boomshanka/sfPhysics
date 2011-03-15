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


#include <sfPhysics/System/Physicable.hpp>

#include <queue>



sfp::Physicable::Physicable()
:myRotationVelocity(0), myArea(1000), myInertiaMoment(10),
myMass(1000), myDensity(1), myRestitution(1), myDynamicFriction(0.3), myStaticFriction(0.5)
{

}


//   -----   Getter & Setter   -----   //


bool sfp::Physicable::SetMass(float mass)
{
	if(mass<=0)
		return false;
	
	myInertiaMoment/=myMass;
	myInertiaMoment*=mass;
	
	myMass=mass;
	myDensity=myMass/myArea;
	return true;
}


bool sfp::Physicable::SetDensity(float density)
{
	if(density<=0)
		return false;
	
	myInertiaMoment/=myDensity;
	myInertiaMoment*=density;
	
	myDensity=density;
	myMass=myDensity*myArea;
	return true;
}


bool sfp::Physicable::SetArea(float area)
{
	if(area<=0)
		return false;
	
	myInertiaMoment/=(myDensity*myArea);
	myInertiaMoment*=(myDensity*area);
	
	myArea=area;
	myMass=myDensity*myArea;
	return true;
}


bool sfp::Physicable::SetRestitution(float restitution)
{
	if(restitution<0)
		return false;
	
	myRestitution=restitution;
	return true;
}


bool sfp::Physicable::SetFriction(float friction)
{
	if(friction<0)
		return false;
	
	myDynamicFriction=myStaticFriction=friction;
	return true;
}


bool sfp::Physicable::SetDynamicFriction(float friction)
{
	if(friction<0 || friction>myStaticFriction)
		return false;
	
	myDynamicFriction=friction;
	return true;
}


bool sfp::Physicable::SetStaticFriction(float friction)
{
	if(friction<0 || friction<myStaticFriction)
		return false;
	
	myStaticFriction=friction;
	return true;
}


bool sfp::Physicable::SetInertiaMoment(float inertiamoment)
{
	if(inertiamoment<=0)
		return false;
	
	myInertiaMoment=inertiamoment;
	return true;
}


