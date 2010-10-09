#include <sfPhysics/Collision.hpp>
#include <sfPhysics/SAT.hpp>

#include <cmath>


#define _USE_MATH_DEFINES



sfp::Collision::Collision()
:myNoCollisionEventEnabled(false)
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
		//Compute SAT
		for(std::list<sfp::Object*>::iterator it=myObjects.begin(); it!=myObjects.end(); ++it)
		{
			if((*it)->IsSeparatingAxisEnabled())
				(*it)->ComputeSeparatingAxis();
		}
		
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
		std::list<sfp::Object*>::iterator it2=it;
		for(++it2; it2!=myObjects.end(); ++it2)
		{
			myCollisionEvents.push(CollisionEvent(*(*it),*(*it2)));
			
			if(CheckCollision(*(*it),*(*it2)) && CheckCollision(*(*it2),*(*it)))
			{
				myCollisionEvents.front().CollisionType=sfp::PreciseCollision;
			}
			else
			{
				if(!myNoCollisionEventEnabled && myCollisionEvents.front().CollisionType==NoCollision)
					myCollisionEvents.pop(); //FIXME ist pop hier richtig? (wie wärs wenn einfach kein objekt erstellt wird?)
			}
		}
	}
}



bool sfp::Collision::CheckCollision(sfp::Object& first, sfp::Object& second) //Funktion aufteilen und mehrere formen pro objekt unterstützen
{
	//if
	{
		myCollisionEvents.front().CollisionType=sfp::BoundingBox;
		
		if(first.IsSeparatingAxisEnabled() && second.IsSeparatingAxisEnabled())
		{
			for(int i=0; i<first.GetSeparatingAxis().GetAxisCount(); ++i)
			{
				float firstmax; float secondmax;
				float firstmin; float secondmin;
				
				if(first.GetPointCount()>1)
					firstmax=firstmin=first.ToGlobal(first.GetPoint(0)).x*first.GetSeparatingAxis().GetAx(i).x+first.ToGlobal(first.GetPoint(0)).y*first.GetSeparatingAxis().GetAx(i).y;
				for(int j=1;j<first.GetPointCount();++j)
				{
					float tmp=first.ToGlobal(first.GetPoint(j)).x*first.GetSeparatingAxis().GetAx(i).x+first.ToGlobal(first.GetPoint(j)).y*first.GetSeparatingAxis().GetAx(i).y;
					
					if(tmp>firstmax)
						{firstmax=tmp;}
					else if(tmp<firstmin)
						{firstmin=tmp;}
				}
				
				if(second.GetPointCount()>1)
					secondmax=secondmin=second.ToGlobal(second.GetPoint(0)).x*first.GetSeparatingAxis().GetAx(i).x+second.ToGlobal(second.GetPoint(0)).y*first.GetSeparatingAxis().GetAx(i).y;
				for(int j=1;j<second.GetPointCount();++j)
				{
					float tmp=second.ToGlobal(second.GetPoint(j)).x*first.GetSeparatingAxis().GetAx(i).x+second.ToGlobal(second.GetPoint(j)).y*first.GetSeparatingAxis().GetAx(i).y;
					
					if(tmp>secondmax)
						{secondmax=tmp;}
					else if(tmp<secondmin)
						{secondmin=tmp;}
				}
				
				if(firstmax < secondmin || firstmin > secondmax)
					return false;
				
				sfp::Vector2f intersection; //FIXME läuft kein meter
				intersection.SetForce(firstmin>secondmax ? (firstmin-secondmax) : (secondmin-firstmax), sfp::Vector2f(first.GetSeparatingAxis().GetAx(i)).GetDirection());
				
				if(first.GetSpeed().x!=0)
				{
					sf::Vector2f speed=first.GetSpeed()+second.GetSpeed();
					float time=intersection.x/speed.x;
					
					if(time<myCollisionEvents.front().CollisionTime || myCollisionEvents.front().CollisionTime==0)
						myCollisionEvents.front().CollisionTime=time;
				}
				else if(first.GetSpeed().y!=0)
				{
					sf::Vector2f speed=first.GetSpeed()+second.GetSpeed();
					float time=intersection.y/speed.y;
					
					if(time<myCollisionEvents.front().CollisionTime || myCollisionEvents.front().CollisionTime==0)
						myCollisionEvents.front().CollisionTime=time;
				}
			}
		}
		//myCollisionEvents.front()
		return true;
		
	}
	return false;
}





