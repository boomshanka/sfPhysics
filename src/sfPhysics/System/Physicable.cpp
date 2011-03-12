#include <sfPhysics/System/Physicable.hpp>

#include <queue>



sfp::Physicable::Physicable()
:myRotationSpeed(0), myArea(1000), myInertiaMoment(10),
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


