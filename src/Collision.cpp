#include "Collision.hpp"
#include "SAT.hpp"



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
	for(std::list<sfp::Object*>::iterator it=myObjects.begin(); it!=myObjects.end(); ++it)
	{
		//if sat==enabled
			sfp::SeparatingAxis axis(*(*(it)));
		
		std::list<sfp::Object*>::iterator it2=it;
		for(++it2; it2!=myObjects.end(); ++it2)
		{
			//if(bounding rectangle && sat==enabled)
			{
			
			}
		
		}
	}
}



