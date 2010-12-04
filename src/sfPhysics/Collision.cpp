#include <sfPhysics/Collision.hpp>
#include <sfPhysics/SAT.hpp>

#include <cmath>


#define _USE_MATH_DEFINES


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
			collisionevent.secondobject->ToGlobal(collisionevent.secondobject->GetConvexPolygon(collisionevent.convexobjects.top().second).GetPolygonCenter()) -
			collisionevent.firstobject->ToGlobal(collisionevent.firstobject->GetConvexPolygon(collisionevent.convexobjects.top().first).GetPolygonCenter())
		);
		
		if(((movement.x>0 && positions.x>=0) || (movement.x<0 && positions.x<0) )||/*&&*/ ( (movement.y>0 && positions.y>=0) || (movement.y<0 && positions.y<0)))
		{
			std::cout<<collisionevent.collisionangle.top()<<" - "<<collisionevent.collisionpoints.top().x<<" "<<collisionevent.collisionpoints.top().y<<"\n";
			
			sfp::Vector2f speed=sfp::Vector2f(collisionevent.firstobject->GetSpeed()); speed.y*=-0.8;
			collisionevent.firstobject->SetSpeed(speed);
			speed=sfp::Vector2f(collisionevent.secondobject->GetSpeed()); speed.y*=-0.8;
			collisionevent.secondobject->SetSpeed(speed);
			
			
		}
		else
		{std::cout<<"ich kollidiere NICHT!!\n";}
		
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
		
		for(unsigned int i=0; i<first.GetConvexPolygonCount(); ++i) //Schleife für die konkaven Formen von Obj 1
		{
			switch(first.GetConvexPolygon(i).GetPolygonType())
			{
				case Shape:
				case Rectangle:
					for(unsigned int j=0; j<second.GetConvexPolygonCount(); ++j) //Von Objekt 2
					{
						switch(second.GetConvexPolygon(j).GetPolygonType())
						{
							case Shape:
							case Rectangle:
								//if(BoundingBoxes)
									if(ShapeShape(first,second)) //FIXME beidseitig!
										isCollided=true;
							break;
							
							case Plane:
								if(ShapePlane(first,second))
									isCollided=true;
							break;
							
							case Circle:
								//if(BoundingBoxes)
									if(ShapeCircle(first,second))
										isCollided=true;
							break;
							
							case NegCircle:
								//FIXME
							break;
						}
					}
				break;
					
				case Plane:
					for(unsigned int j=0; j<second.GetConvexPolygonCount(); ++j) //Von Objekt 2
					{
						switch(second.GetConvexPolygon(j).GetPolygonType())
						{
							case Shape:
							case Rectangle:
								if(ShapePlane(second,first))
									isCollided=true;
							break;
							
							case Circle:
								if(PlaneCircle(first,second))
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
					for(unsigned int j=0; j<second.GetConvexPolygonCount(); ++j) //Von Objekt 2
					{
						switch(second.GetConvexPolygon(j).GetPolygonType())
						{
							case Shape:
							case Rectangle:
								//if(BoundingBoxes)
									if(ShapeCircle(second,first))
										isCollided=true;
							break;
							
							case Plane:
								if(PlaneCircle(second,first))
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
					for(unsigned int j=0; j<second.GetConvexPolygonCount(); ++j) //Von Objekt 2
					{
						//switch(second.GetConvexPolygon(j).GetPolygonType())
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



bool sfp::Collision::ShapeShape(sfp::Object& first, sfp::Object& second)
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



bool sfp::Collision::ShapePlane(sfp::Object& first, sfp::Object& second)
{

}



bool sfp::Collision::ShapeCircle(sfp::Object& first, sfp::Object& second)
{
return false;
}



bool sfp::Collision::PlaneCircle(sfp::Object& first, sfp::Object& second)
{

}



bool sfp::Collision::CircleCircle(sfp::Object& first, sfp::Object& second, unsigned int i, unsigned int j)
{
	sfp::Vector2f distance(second.ToGlobal(second.GetConvexPolygon(j).GetPolygonCenter())-first.ToGlobal(first.GetConvexPolygon(i).GetPolygonCenter()));
	if(distance.GetForce() > (first.GetConvexPolygon(i).GetCircleRadius()+second.GetConvexPolygon(j).GetCircleRadius()))
		return false;
	
	distance.SetForce(first.GetConvexPolygon(i).GetCircleRadius()-((first.GetConvexPolygon(i).GetCircleRadius()+second.GetConvexPolygon(j).GetCircleRadius())-distance.GetForce())/2);

	myCollisionEvents.top().collisionpoints.push(/*sf::Vector2f(50,450));/*/distance);
	float angle=distance.GetDirection(); if(angle>270) {angle-=270;} else {angle+=90;}
	myCollisionEvents.top().collisionangle.push(/*0);/*/angle);
	myCollisionEvents.top().convexobjects.push(std::make_pair(i,j));
	
	return true;
}






/*				sfp::Vector2f intersection; //FIXME läuft kein meter
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
			}*/

