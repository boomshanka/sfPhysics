#include <sfPhysics/Collision/Collision.hpp>
#include <sfPhysics/System/SAT.hpp>


#define _USE_MATH_DEFINES
#include <cmath>




sfp::Collision::Collision()
:myNoCollisionEventEnabled(false)
{
}



sfp::Collision::~Collision()
{
}




// ---------------------------------------------------- //



void sfp::Collision::Bounce(sfp::CollisionEvent& event)
{
	while(!event.collisionpoint.empty())
	{
		sfp::Vector2f movement=event.second->GetMovement(event.second->ToLocal(event.collisionpoint.top()))-
								event.first->GetMovement(event.first->ToLocal(event.collisionpoint.top()));
		sf::Vector2f positions
		(
			event.first->ToGlobal(event.first->GetConvexShape(event.convexobjects.top().first).GetShapeCenter()) -
			event.second->ToGlobal(event.second->GetConvexShape(event.convexobjects.top().second).GetShapeCenter())
		);
		
		
		if(true)//((movement.x<0 && po.x>=0) || (movement.x>0 && po.x<0) )||/*&&*/ ( (movement.y<0 && po.y>=0) || (movement.y>0 && po.y<0)))
		{
			sfp::Vector2f r1(event.collisionpoint.top()-event.first->GetPosition());
			sfp::Vector2f r2(event.collisionpoint.top()-event.second->GetPosition());
			
			float j=-(1+(event.first->GetRestitution()+event.second->GetRestitution())/2.f)*movement.DotProduct(event.collisionnormal.top());
			j /= (1.f/event.first->GetMass()) + (1.f/event.second->GetMass()) +
			std::abs(sfp::Vector2f(1.f/event.first->GetInertiaMoment() * r1.CrossProduct(event.collisionnormal.top()) * r1 + 1.f/event.second->GetInertiaMoment() *
			r2.CrossProduct(event.collisionnormal.top()) * r2).DotProduct(event.collisionnormal.top()));
										//FIXME wird aus dem ×r1 und ×r2 ein *r1 / *r2 (dimensionen!)?
			
				
			event.first->SetSpeed(event.first->GetSpeed() - (j/event.first->GetMass()) * event.collisionnormal.top());
			event.second->SetSpeed(event.second->GetSpeed() + (j/event.second->GetMass()) * event.collisionnormal.top());
			
			event.first->SetRotationSpeed(event.first->GetRotationSpeed() - j/event.first->GetInertiaMoment() * r1.CrossProduct(event.collisionnormal.top()));
			event.second->SetRotationSpeed(event.second->GetRotationSpeed() + j/event.second->GetInertiaMoment() * r2.CrossProduct(event.collisionnormal.top()));
			
			
			//Objekte auseinander schieben. FIXME es wird nur der kürzteste weg genutzt
			
			
		}
		
		event.collisionpoint.pop();
		event.collisionnormal.pop();
		event.convexobjects.pop();
	}
}




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
		event=myCollisionEvents.top();
		return true;
	}
	
	return false;
}




void sfp::Collision::UpdateCollisionEvents()
{
	for(std::list<sfp::Object*>::iterator it=myObjects.begin(); it!=myObjects.end(); ++it)
	{
		std::list<sfp::Object*>::iterator it2=it;
		for(++it2; it2!=myObjects.end(); ++it2)
		{
			myCollisionEvents.push(CollisionEvent(*(*it),*(*it2)));
			
			if(CheckCollision(*(*it),*(*it2)))
			{
				myCollisionEvents.top().CollisionType=sfp::PreciseCollision;
			}
			else
			{
				if(!myNoCollisionEventEnabled && myCollisionEvents.top().CollisionType==NoCollision)
					myCollisionEvents.pop(); //FIXME wie wärs wenn einfach kein objekt erstellt wird? Tolle Idee :D
			}
		}
	}
}




bool sfp::Collision::CheckCollision(sfp::Object& first, sfp::Object& second)
{
	//FIXME: Rewrite der funktion. Verschiedene Objekttypen müssen speziell behandelt werden.
	//		 Bei Kollision werden Punkte und konvexe Formen im Event gespeichert!
	
	myCollisionEvents.top().CollisionType=sfp::BoundingBox; //FIXME
	
	if(first.IsSeparatingAxisEnabled() && second.IsSeparatingAxisEnabled())
	{
		bool isCollided=false;
		
		for(unsigned int i=0; i<first.GetConvexShapeCount(); ++i) //Schleife für die konkaven Formen von Obj 1
		{
			switch(first.GetConvexShape(i).GetShapeType())
			{
				case Polygon:
				case Rectangle:
					for(unsigned int j=0; j<second.GetConvexShapeCount(); ++j) //Von Objekt 2
					{
						switch(second.GetConvexShape(j).GetShapeType())
						{
							case Polygon:
							case Rectangle:
								//if(BoundingBoxes)
									if(PolygonPolygon(first,second)) //FIXME beidseitig!
										isCollided=true;
							break;
							
							case Plane:
								if(PolygonPlane(first,second))
									isCollided=true;
							break;
							
							case Circle:
								//if(BoundingBoxes)
									if(PolygonCircle(first,second))
										isCollided=true;
							break;
							
							case NegCircle:
								//FIXME
							break;
						}
					}
				break;
					
				case Plane:
					for(unsigned int j=0; j<second.GetConvexShapeCount(); ++j) //Von Objekt 2
					{
						switch(second.GetConvexShape(j).GetShapeType())
						{
							case Polygon:
							case Rectangle:
								if(PolygonPlane(second,first))
									isCollided=true;
							break;
							
							case Circle:
								if(PlaneCircle(first,second, i, j))
									isCollided=true;
							break;
							
							case NegCircle:
								//FIXME
							break;
							
							case Plane:
							break;
						}
					}
				break;
					
				case Circle:
					for(unsigned int j=0; j<second.GetConvexShapeCount(); ++j) //Von Objekt 2
					{
						switch(second.GetConvexShape(j).GetShapeType())
						{
							case Polygon:
							case Rectangle:
								//if(BoundingBoxes)
									if(PolygonCircle(second,first))
										isCollided=true;
							break;
							
							case Plane:
								if(PlaneCircle(second,first, j, i))
									isCollided=true;
							break;
							
							case Circle:
								//if(BoundingBoxes)
									if(CircleCircle(first,second, i, j))
										isCollided=true;
							break;
							
							case NegCircle:
								//FIXME
							break;
						}
					}
				break;
				
				case NegCircle:
					for(unsigned int j=0; j<second.GetConvexShapeCount(); ++j) //Von Objekt 2
					{
						//switch(second.GetConvexShape(j).GetShapeType())
						{
						
						}
					}
				break;
			}
		}
		
		return isCollided;
	}
	
	return false;
}



bool sfp::Collision::PolygonPolygon(sfp::Object& first, sfp::Object& second) //FIXME Rewrite + kollisionspunkte rausfinden!! event beschreiben
{
	for(int i=0; i<first.GetSeparatingAxis().GetAxisCount(); ++i)
	{
		float firstmax=0; float secondmax=0;
		float firstmin=0; float secondmin=0;
		
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
	}
	return true;
}



bool sfp::Collision::PolygonPlane(sfp::Object& first, sfp::Object& second)
{
return false;
}



bool sfp::Collision::PolygonCircle(sfp::Object& first, sfp::Object& second)
{
return false;
}



bool sfp::Collision::PlaneCircle(sfp::Object& first, sfp::Object& second, unsigned int i, unsigned int j)
{
	sfp::Vector2f hyp(second.ToGlobal(second.GetConvexShape(j).GetShapeCenter())-first.ToGlobal(first.GetConvexShape(i).GetShapeCenter()));
	sfp::Vector2f distance(std::cos(hyp.GetDirection()-first.GetConvexShape(i).GetCircleRadius()*M_PI/180.f)*hyp.GetForce(),0);
	
	if(distance.x>second.GetConvexShape(j).GetCircleRadius())
		return false;
	
	distance.SetDirection(first.GetConvexShape(i).GetCircleRadius());
	myCollisionEvents.top().collisionpoint.push(second.GetConvexShape(j).GetShapeCenter()+distance);
//	myCollisionEvents.top().collisionangle.push(first.GetConvexShape(i).GetCircleRadius()+90.f);
	myCollisionEvents.top().convexobjects.push(std::make_pair(i,j));
	
	return true;
}



bool sfp::Collision::CircleCircle(sfp::Object& first, sfp::Object& second, unsigned int i, unsigned int j)
{
	sfp::Vector2f distance(second.ToGlobal(second.GetLocalShapeCenter(j))-first.ToGlobal(first.GetLocalShapeCenter(i)));
	if(distance.GetForce() > (first.GetConvexShape(i).GetCircleRadius()+second.GetConvexShape(j).GetCircleRadius()))
		return false;
	
	myCollisionEvents.top().collisionnormal.push(distance); myCollisionEvents.top().collisionnormal.top().Normalize();
	
	distance.SetForce(first.GetConvexShape(i).GetCircleRadius()-((first.GetConvexShape(i).GetCircleRadius()+
			 second.GetConvexShape(j).GetCircleRadius())-distance.GetForce())/2.f);
	distance+=first.GetPosition(); //FIXME
	
	myCollisionEvents.top().collisionpoint.push(distance);
	myCollisionEvents.top().convexobjects.push(std::make_pair(i,j));
	
	return true;
}




