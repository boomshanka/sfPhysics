#include "Physicable.hpp"



sfp::Physicable::Physicable()
:myRotationSpeed(0), myRotation(0),
myMass(10), myDensity(1), myRestitution(0), myFriction(0),
myArea(10)
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
	if(restitution<0 || restitution>1)
		return false;
	
	myRestitution=restitution;
	return true;
}


bool sfp::Physicable::SetFriction(float friction)
{
	if(friction<0 || friction>1)
		return false;
	
	myFriction=friction;
	return true;
}



void sfp::Physicable::ComputeArea(const std::vector<sf::Vector2f>& points)
{

}


