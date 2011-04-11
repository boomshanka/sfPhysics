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
#include <sfPhysics/System/Line.hpp>


#define _USE_MATH_DEFINES
#include <cmath>



sfp::Collision::Collision()
:myNoCollisionEventEnabled(false) //FIXME myCollisionEventEnabled(true)
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
		if(event.first->IsFixed())
		{
			sfp::Vector2f movement=-event.second->GetMovement(event.second->ToLocal(event.collisionpoint.top()), -event.collisionnormal.top());
			
			float restitution = (event.first->GetRestitution()+event.second->GetRestitution()) / 2.f;
			BounceFixed(*event.second, event.collisionpoint.top(), -event.collisionnormal.top(), movement, restitution);
			
			event.second->AddIntersection(-event.intersection.top(), sf::Vector2f()); //FIXME
		}
		else if(event.second->IsFixed())
		{
			sfp::Vector2f movement=-event.first->GetMovement(event.first->ToLocal(event.collisionpoint.top()), event.collisionnormal.top());
			
			float restitution = (event.first->GetRestitution()+event.second->GetRestitution()) / 2.f;
			BounceFixed(*event.first, event.collisionpoint.top(), event.collisionnormal.top(), movement, restitution);
			
			event.first->AddIntersection(event.intersection.top(), sf::Vector2f()); //FIXME
		}
		else
		{
			sfp::Vector2f movement=event.second->GetMovement(event.second->ToLocal(event.collisionpoint.top()), -event.collisionnormal.top())-
								event.first->GetMovement(event.first->ToLocal(event.collisionpoint.top()), event.collisionnormal.top());
			
			sfp::Vector2f r(event.collisionpoint.top()-event.second->ToGlobal(event.second->GetConvexShape(event.convexobjects.top().second).GetShapeCenter()));
			float direction=r.GetDirection()-movement.GetDirection();
			
			if(direction<90 || direction>270) //FIXME if stimmt nicht
				Bounce(*event.first, *event.second, event.collisionpoint.top(), event.collisionnormal.top(), movement);
			
			float factor = event.first->GetMass() / (event.first->GetMass() + event.second->GetMass()); //FIXME Testen!
			
			event.first->AddIntersection(event.intersection.top() * factor, sf::Vector2f()); //FIXME
			event.second->AddIntersection(-event.intersection.top() * (1-factor), sf::Vector2f()); //FIXME
		}
		
		event.collisionpoint.pop();
		event.collisionnormal.pop();
		event.intersection.pop();
		event.convexobjects.pop();
	}
}



void sfp::Collision::Bounce(sfp::Object& first, sfp::Object& second, const sfp::Vector2f& P, const sfp::Vector2f& n, const sfp::Vector2f& vr)
{
	sfp::Vector2f r1(P-first.GetPosition());
	sfp::Vector2f r2(P-second.GetPosition());
			
	float j=-(1+(first.GetRestitution()+second.GetRestitution())/2.f) * DotProduct(vr, n);
	j /= 1.f/first.GetMass() + 1.f/second.GetMass() +
	std::abs(DotProduct((1.f/first.GetInertiaMoment() * CrossProduct(r1, n) * r1 + 1.f/second.GetInertiaMoment() * CrossProduct(r2, n) * r2), n));
	
	
	first.SetVelocity(first.GetVelocity() - (j/first.GetMass()) * n);
	second.SetVelocity(second.GetVelocity() + (j/second.GetMass()) * n);
	
	first.SetRotationVelocity(first.GetRotationVelocity() - j/first.GetInertiaMoment() * CrossProduct(r1, n) * 180.f/static_cast<float>(M_PI));
	second.SetRotationVelocity(second.GetRotationVelocity() + j/second.GetInertiaMoment() * CrossProduct(r2, n) * 180.f/static_cast<float>(M_PI));
	
	//Objekte auseinander schieben. FIXME es wird nur der kürzteste weg genutzt
	
	
}



void sfp::Collision::BounceFixed(sfp::Object& object, const sfp::Vector2f& P, const sfp::Vector2f& n, const sfp::Vector2f& vr, float e)
{
	sfp::Vector2f r1(P-object.GetPosition());
			
	float j= - ++e * DotProduct(vr, n);
	j /= 1.f/object.GetMass() + std::abs(DotProduct((1.f/object.GetInertiaMoment() * CrossProduct(r1, n) * r1), n));
	
	object.SetVelocity(object.GetVelocity() - (j/object.GetMass()) * n);
	object.SetRotationVelocity(object.GetRotationVelocity() - j/object.GetInertiaMoment() * CrossProduct(r1, n) * 180.f/static_cast<float>(M_PI));
	
	//Objekte auseinander schieben. FIXME es wird nur der kürzteste weg genutzt
	
	
}




bool sfp::Collision::PollCollision(sfp::CollisionEvent& event)
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
} //FIXME Rename UpdateCollision, wahlweise Events deaktivieren, Funktion zum Ableiten implementieren. Quadtree?




bool sfp::Collision::CheckCollision(sfp::Object& first, sfp::Object& second)
{
	//FIXME BoundingBoxes
	
	myCollisionEvents.top().CollisionType = NoCollision; //sfp::BoundingBox; //FIXME
	
	bool isCollided = false;
	
	for(unsigned int i=0; i<first.GetConvexShapeCount(); ++i) //Schleife für die konkaven Formen von Obj 1
	{
		switch(first.GetConvexShape(i).GetShapeType())
		{
			case Shape::Type::Polygon:
			case Shape::Type::Rectangle:
				for(unsigned int j=0; j<second.GetConvexShapeCount(); ++j) //Von Objekt 2
				{
					switch(second.GetConvexShape(j).GetShapeType())
					{
						case Shape::Type::Polygon:
						case Shape::Type::Rectangle:
							//if(BoundingBoxes)
								if(PolygonPolygon(first,second, i, j))
								{
									isCollided=true;
									myCollisionEvents.top().convexobjects.push(std::make_pair(i,j));
								}
						break;
						
						case Shape::Type::Plane:
							if(PolygonPlane(first,second, i, j))
							{
								isCollided=true;
								myCollisionEvents.top().convexobjects.push(std::make_pair(i,j));
							}
						break;
						
						case Shape::Type::Circle:
							//if(BoundingBoxes)
								if(PolygonCircle(first,second, i, j))
								{
									isCollided=true;
									myCollisionEvents.top().convexobjects.push(std::make_pair(i,j));
								}
						break;
						
						case Shape::Type::NegCircle:
							//FIXME
						break;
						
						default:
						break;
					}
				}
			break;
					
			case Shape::Type::Plane:
				for(unsigned int j=0; j<second.GetConvexShapeCount(); ++j) //Von Objekt 2
				{
					switch(second.GetConvexShape(j).GetShapeType())
					{
						case Shape::Type::Polygon:
						case Shape::Type::Rectangle:
							if(PolygonPlane(second,first, j, i))
							{
								isCollided=true;
								myCollisionEvents.top().convexobjects.push(std::make_pair(i,j));
								myCollisionEvents.top().collisionnormal.top()*=-1.f;
							}
						break;
						
						case Shape::Type::Circle:
							if(PlaneCircle(first,second, i, j))
							{
								isCollided=true;
								myCollisionEvents.top().convexobjects.push(std::make_pair(i,j));
							}
						break;
						
						case Shape::Type::NegCircle:
							//FIXME
						break;
						
						case Shape::Type::Plane:
						default:
						break;
					}
				}
			break;
				
			case Shape::Type::Circle:
				for(unsigned int j=0; j<second.GetConvexShapeCount(); ++j) //Von Objekt 2
				{
					switch(second.GetConvexShape(j).GetShapeType())
					{
						case Shape::Type::Polygon:
						case Shape::Type::Rectangle:
							//if(BoundingBoxes)
								if(PolygonCircle(second,first, j, i))
								{
									isCollided=true;
									myCollisionEvents.top().convexobjects.push(std::make_pair(i,j));
									myCollisionEvents.top().collisionnormal.top()*=-1.f;
								}
						break;
						
						case Shape::Type::Plane:
							if(PlaneCircle(second,first, j, i))
							{
								isCollided=true;
								myCollisionEvents.top().convexobjects.push(std::make_pair(i,j));
								myCollisionEvents.top().collisionnormal.top()*=-1.f;
							}
						break;
						
						case Shape::Type::Circle:
							//if(BoundingBoxes)
								if(CircleCircle(first,second, i, j))
								{
									isCollided=true;
									myCollisionEvents.top().convexobjects.push(std::make_pair(i,j));
								}
						break;
						
						case Shape::Type::NegCircle:
							//FIXME
						break;
						
						default:
						break;
					}
				}
			break;
			
			case Shape::Type::NegCircle:
				for(unsigned int j=0; j<second.GetConvexShapeCount(); ++j) //Von Objekt 2
				{
					//switch(second.GetConvexShape(j).GetShapeType())
					{
					
					}
				}
			break;
			
			default:
			break;
		}
	}
	
	return isCollided;
}



bool sfp::Collision::PolygonPolygon(sfp::Object& first, sfp::Object& second, unsigned int a, unsigned int b) //FIXME Rewrite + kollisionspunkte rausfinden!! event beschreiben
{
	first.GetConvexShape(a).GetSeparatingAxis().UpdateRotation(first.GetRotation());
	second.GetConvexShape(b).GetSeparatingAxis().UpdateRotation(second.GetRotation());
	
	if(first.GetConvexShape(a).GetPointCount() > 1 && second.GetConvexShape(b).GetPointCount() > 1)
	{
		return ComputePolygonPolygon(first, second, a, b) && ComputePolygonPolygon(second, first, a, b);
	}
	
	return false;
}


bool sfp::Collision::ComputePolygonPolygon(sfp::Object& first, sfp::Object& second, unsigned int a, unsigned int b)
{
	for(unsigned int i=0; i < first.GetConvexShape(a).GetSeparatingAxis().GetAxisCount(); ++i) //FIXME size_t
	{
		float firstmin = DotProduct(first.GetConvexShape(a).GetSeparatingAxis().GetAx(i), first.ToGlobal(first.GetConvexShape(a).GetPoint(0)));
		float firstmax = firstmin;
		
		for(int j=1; j < first.GetConvexShape(a).GetPointCount(); ++j)
		{
			float tmp = DotProduct(first.GetConvexShape(a).GetSeparatingAxis().GetAx(i), first.ToGlobal(first.GetConvexShape(a).GetPoint(j)));
			
			if(tmp > firstmax) firstmax=tmp;
			else if(tmp < firstmin) firstmin=tmp;
		}
		
		
		float secondmin = DotProduct(first.GetConvexShape(a).GetSeparatingAxis().GetAx(i), second.ToGlobal(second.GetConvexShape(b).GetPoint(0)));
		float secondmax = secondmin;
		
		for(int j=1; j < second.GetConvexShape(b).GetPointCount(); ++j)
		{
			float tmp = DotProduct(first.GetConvexShape(a).GetSeparatingAxis().GetAx(i), second.ToGlobal(second.GetConvexShape(b).GetPoint(j)));
			
			if(tmp > secondmax) secondmax=tmp;
			else if(tmp < secondmin) secondmin=tmp;
		}
		
		if(firstmax < secondmin || firstmin > secondmax)
			return false;
		
	}
	
	ComputePolygonPolygonCollision(first, second, a, b);
	
	return true;
}


void sfp::Collision::ComputePolygonPolygonCollision(sfp::Object& first, sfp::Object& second, unsigned int a, unsigned int b)
{
	sfp::Vector2f r1; sfp::Vector2f r2;
	
	
	
	myCollisionEvents.top().collisionpoint.push((r1+r2)/2.f); 
	myCollisionEvents.top().collisionnormal.push(sf::Vector2f());//DotProduct(r2-r1, r2-r1)); //FIXME second-first vllt umdrehen? stimmt das überhaupt?
	myCollisionEvents.top().intersection.push(sf::Vector2f()); //FIXME
}



bool sfp::Collision::PolygonPlane(sfp::Object& first, sfp::Object& second, unsigned int i, unsigned int j)
{
if(i!=j) {;}
return false;
}



bool sfp::Collision::PolygonCircle(sfp::Object& first, sfp::Object& second, unsigned int i, unsigned int j)
{
if(i!=j) {;}
return false;
}



bool sfp::Collision::PlaneCircle(sfp::Object& first, sfp::Object& second, unsigned int i, unsigned int j)
{//FIXME
	sfp::Vector2f hyp(first.ToGlobal(first.GetConvexShape(i).GetShapeCenter())-second.ToGlobal(second.GetConvexShape(j).GetShapeCenter()));
	float distance(std::abs(std::cos((first.GetConvexShape(i).GetPlaneNormal().GetDirection()-hyp.GetDirection())*M_PI/180.f)) * hyp.GetForce());
	
	if(distance >= second.GetConvexShape(j).GetCircleRadius())
		return false;
	
	myCollisionEvents.top().collisionpoint.push(second.ToGlobal(second.GetConvexShape(j).GetShapeCenter())-first.GetConvexShape(i).GetPlaneNormal()*distance);
	myCollisionEvents.top().collisionnormal.push(first.GetPlaneNormal());
	myCollisionEvents.top().intersection.push(first.GetConvexShape(i).GetPlaneNormal()*(second.GetConvexShape(j).GetCircleRadius()-distance));
	
	return true;
}



bool sfp::Collision::CircleCircle(sfp::Object& first, sfp::Object& second, unsigned int i, unsigned int j)
{
	sfp::Vector2f distance(second.ToGlobal(second.GetConvexShape(j).GetShapeCenter())-first.ToGlobal(first.GetConvexShape(i).GetShapeCenter()));
	float dis=(first.GetConvexShape(i).GetCircleRadius()+second.GetConvexShape(j).GetCircleRadius()) - distance.GetForce();
	if(dis <= 0)
		return false;
	
	myCollisionEvents.top().collisionnormal.push(distance); myCollisionEvents.top().collisionnormal.top().Normalize();
	myCollisionEvents.top().intersection.push(myCollisionEvents.top().collisionnormal.top());
	myCollisionEvents.top().intersection.top()*= -dis; //FIXME warum -
	
	distance.SetForce(first.GetConvexShape(i).GetCircleRadius()-((first.GetConvexShape(i).GetCircleRadius()+
			 second.GetConvexShape(j).GetCircleRadius())-distance.GetForce())/2.f);
	distance+=first.ToGlobal(first.GetConvexShape(i).GetShapeCenter()); //FIXME
	
	myCollisionEvents.top().collisionpoint.push(distance);
	
	return true;
}




