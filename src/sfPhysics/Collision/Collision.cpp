#include <sfPhysics/Collision/Collision.hpp>
#include <sfPhysics/System/SAT.hpp>


#define _USE_MATH_DEFINES
#include <cmath>



#include <iostream>
sfp::Collision::Collision()
:myNoCollisionEventEnabled(false)
{
}



sfp::Collision::~Collision()
{
}




// ---------------------------------------------------- //



void sfp::Collision::Bounce(sfp::CollisionEvent& collisionevent)
{
	while(!collisionevent.collisionpoints.empty())
	{
		sfp::Vector2f movement=collisionevent.firstobject->GetMovement(collisionevent.firstobject->ToLocal(collisionevent.collisionpoints.top()))-
								collisionevent.secondobject->GetMovement(collisionevent.secondobject->ToLocal(collisionevent.collisionpoints.top()));
		sf::Vector2f positions
		(
			collisionevent.secondobject->ToGlobal(collisionevent.secondobject->GetConvexShape(collisionevent.convexobjects.top().second).GetShapeCenter()) -
			collisionevent.firstobject->ToGlobal(collisionevent.firstobject->GetConvexShape(collisionevent.convexobjects.top().first).GetShapeCenter())
		);
		
		if(((movement.x>0 && positions.x>=0) || (movement.x<0 && positions.x<0) )||/*&&*/ ( (movement.y>0 && positions.y>=0) || (movement.y<0 && positions.y<0)))
		{
	//		std::cout<<collisionevent.collisionangle.top()<<" - "<<collisionevent.collisionpoints.top().x<<" "<<collisionevent.collisionpoints.top().y<<"\n";
			
			sfp::Vector2f vec1(collisionevent.firstobject->GetForce(collisionevent.firstobject->ToLocal(collisionevent.collisionpoints.top()),
					collisionevent.collisionangle.top()+90, collisionevent.secondobject->GetSpeed()),0);
			sfp::Vector2f vec2(collisionevent.secondobject->GetForce(collisionevent.secondobject->ToLocal(collisionevent.collisionpoints.top()),
					collisionevent.collisionangle.top()-90, collisionevent.firstobject->GetSpeed()),0);
			
			vec1.SetDirection(collisionevent.collisionangle.top()-90);
			vec2.SetDirection(collisionevent.collisionangle.top()+90);
			
			vec1.SetForce(vec1.GetForce()*((collisionevent.firstobject->GetRestitution()+collisionevent.secondobject->GetRestitution())/2.f));
			vec2.SetForce(vec2.GetForce()*((collisionevent.firstobject->GetRestitution()+collisionevent.secondobject->GetRestitution())/2.f));
			
			collisionevent.firstobject->Force(collisionevent.collisionpoints.top(), vec2);
			collisionevent.secondobject->Force(collisionevent.collisionpoints.top(), vec1);
			
			
			//Objekte auseinander schieben. FIXME es wird nur der kürzteste weg genutzt
			
			
		}
		else
		{}//std::cout<<"NEIN!!\n";}
		
		collisionevent.collisionpoints.pop();
		collisionevent.collisionangle.pop();
		collisionevent.convexobjects.pop();
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



bool sfp::Collision::PolygonPolygon(sfp::Object& first, sfp::Object& second)
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
	}
	return true;
}



bool sfp::Collision::PolygonPlane(sfp::Object& first, sfp::Object& second)
{

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
	myCollisionEvents.top().collisionpoints.push(second.GetConvexShape(j).GetShapeCenter()+distance);
	myCollisionEvents.top().collisionangle.push(first.GetConvexShape(i).GetCircleRadius()+90.f);
	myCollisionEvents.top().convexobjects.push(std::make_pair(i,j));
	
	return true;
}



bool sfp::Collision::CircleCircle(sfp::Object& first, sfp::Object& second, unsigned int i, unsigned int j)
{
	sfp::Vector2f distance(second.ToGlobal(second.GetConvexShape(j).GetShapeCenter())-first.ToGlobal(first.GetConvexShape(i).GetShapeCenter()));
	if(distance.GetForce() > (first.GetConvexShape(i).GetCircleRadius()+second.GetConvexShape(j).GetCircleRadius()))
		return false;
	
	distance.SetForce(first.GetConvexShape(i).GetCircleRadius()-((first.GetConvexShape(i).GetCircleRadius()+second.GetConvexShape(j).GetCircleRadius())-distance.GetForce())/2);

	myCollisionEvents.top().collisionpoints.push(/*sf::Vector2f(50,450));/*/distance);
	float angle=distance.GetDirection(); if(angle>270) {angle-=270;} else {angle+=90;}
	myCollisionEvents.top().collisionangle.push(/*0);/*/angle);
	myCollisionEvents.top().convexobjects.push(std::make_pair(i,j));
	
	return true;
}





