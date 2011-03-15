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


#include <sfPhysics/System/Collision.hpp>
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
			if(event.first->IsFixed())
			{
				float restitution = (event.first->GetRestitution()+event.second->GetRestitution()) / 2.f;
				BounceFixed(*event.second, event.collisionpoint.top(), -event.collisionnormal.top(), movement, restitution, true);
			}
			else if(event.second->IsFixed())
			{
				float restitution = (event.first->GetRestitution()+event.second->GetRestitution()) / 2.f;
				BounceFixed(*event.first, event.collisionpoint.top(), event.collisionnormal.top(), movement, restitution);
			}
			else
			{
				Bounce(*event.first, *event.second, event.collisionpoint.top(), event.collisionnormal.top(), movement);
			}
		}
		
		event.collisionpoint.pop();
		event.collisionnormal.pop();
		event.convexobjects.pop();
	}
}



void sfp::Collision::Bounce(sfp::Object& first, sfp::Object& second, const sfp::Vector2f& P, const sfp::Vector2f& n, const sfp::Vector2f& vr)
{
	sfp::Vector2f r1(P-first.GetPosition());
	sfp::Vector2f r2(P-second.GetPosition());
			
	float j=-(1+(first.GetRestitution()+second.GetRestitution())/2.f) * DotProduct(vr, n);
	j /= 1.f/first.GetMass() + 1.f/second.GetMass() + //FIXME std::abs?
	std::abs(DotProduct((1.f/first.GetInertiaMoment() * CrossProduct(r1, n) * r1 + 1.f/second.GetInertiaMoment() *
	CrossProduct(r2, n) * r2), n));
						//FIXME wird aus dem ×r1 und ×r2 ein *r1 / *r2 (dimensionen!)?
	
	
	first.SetVelocity(first.GetVelocity() - (j/first.GetMass()) * n);
	second.SetVelocity(second.GetVelocity() + (j/second.GetMass()) * n);
	
	first.SetRotationVelocity(first.GetRotationVelocity() - j/first.GetInertiaMoment() * CrossProduct(r1, n));
	second.SetRotationVelocity(second.GetRotationVelocity() + j/second.GetInertiaMoment() * CrossProduct(r2, n));
	
	//Objekte auseinander schieben. FIXME es wird nur der kürzteste weg genutzt
	
	
}



void sfp::Collision::BounceFixed(sfp::Object& object, const sfp::Vector2f& P, const sfp::Vector2f& n, const sfp::Vector2f& vr, float e, bool secondfixed)
{
	sfp::Vector2f r1(P-object.GetPosition());
			
	float j= - ++e * DotProduct(vr, n);
	j /= 1.f/object.GetMass() + //FIXME std::abs?
	std::abs(DotProduct((1.f/object.GetInertiaMoment() * CrossProduct(r1, n) * r1), n));
						//FIXME wird aus dem ×r1 und ×r2 ein *r1 / *r2 (dimensionen!)?
	
	
	if(!secondfixed)
	{
		object.SetVelocity(object.GetVelocity() - (j/object.GetMass()) * n);
		object.SetRotationVelocity(object.GetRotationVelocity() - j/object.GetInertiaMoment() * CrossProduct(r1, n));
	}
	else
	{
		object.SetVelocity(object.GetVelocity() + (j/object.GetMass()) * n);
		object.SetRotationVelocity(object.GetRotationVelocity() + j/object.GetInertiaMoment() * CrossProduct(r1, n));
	}
	
	//Objekte auseinander schieben. FIXME es wird nur der kürzteste weg genutzt
	
	
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
{//FIXME
	sfp::Vector2f hyp(first.ToGlobal(first.GetLocalShapeCenter(i))-second.ToGlobal(second.GetLocalShapeCenter(j)));
	float distance(std::abs(std::cos((first.GetPlaneNormal().GetDirection()-hyp.GetDirection())*M_PI/180.f)) * hyp.GetForce());
	
	if(distance > second.GetConvexShape(j).GetCircleRadius())
		return false;
	
	myCollisionEvents.top().collisionpoint.push(second.ToGlobal(second.GetLocalShapeCenter(j))-first.GetPlaneNormal()*distance);
	myCollisionEvents.top().collisionnormal.push(first.GetPlaneNormal());
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




