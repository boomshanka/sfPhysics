#include <sfPhysics/System/Physicable.hpp>

#include <queue>



sfp::Physicable::Physicable()
:myRotationSpeed(0), myArea(1000), myInertiaMoment(10),
myMass(1000), myDensity(1), myRestitution(1), myFriction(0.5)
{

}



//   -----   Getter & Setter   -----   //
bool sfp::Physicable::SetMass(float mass)
{
	if(mass<=0)
		return false;
	
	myMass=mass;
	myDensity=myMass/myArea;
	return true;
}


bool sfp::Physicable::SetDensity(float density)
{
	if(density<=0)
		return false;
	
	myDensity=density;
	myMass=myDensity*myArea;
	return true;
}


bool sfp::Physicable::SetArea(float area)
{
	if(area<=0)
		return false;
	
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
	
	myFriction=friction;
	return true;
}




