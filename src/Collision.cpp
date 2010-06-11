#include "Collision.hpp"



sfp::Collision::Collision()
{
}



sfp::Collision::~Collision()
{
}




// ---------------------------------------------------- //



bool sfp::Collision::GetCollision(sfp::CollisionEvent& event)
{
	if(myCollisionEvents.empty())
	{
		UpdateCollisionEvents();
	}
	else
	{
		myCollisionEvents.pop();
	}
	
	if(!myCollisionEvents.empty())
	{
		event=myCollisionEvents.front();
		return true;
	}
	
	return false;
}




void sfp::Collision::Bounce(sfp::Object& firstobject, sfp::Object& secondobject)
{
	
}



void sfp::Collision::UpdateCollisionEvents()
{
	
}



