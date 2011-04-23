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



void sfp::Collision::CollisionResponse(sfp::CollisionEvent& event)
{
	ComputeContact(event);
	
	while(!event.collisionpoint.empty())
	{
		Collisionpoint = &event.collisionpoint.top();
		Normal = &event.collisionnormal.top();
		Intersection = &event.intersection.top();
		Restitution = event.first->GetRestitution() * event.second->GetRestitution();
		A = event.convexobjects.top().first;
		B = event.convexobjects.top().second;
		
		if(event.first->IsFixed())
		{
			Movement = -event.second->GetMovement(event.second->ToLocal(*Collisionpoint), -*Normal);//FIXME
			Movement2 = event.second->GetMovement(event.second->ToLocal(*Collisionpoint));
		}
		else if(event.second->IsFixed())
		{
			Movement = -event.first->GetMovement(event.first->ToLocal(*Collisionpoint), *Normal);
			Movement2 = -event.first->GetMovement(event.first->ToLocal(*Collisionpoint));
		}
		else
		{
			Movement = event.second->GetMovement(event.second->ToLocal(*Collisionpoint), -*Normal) -
							event.first->GetMovement(event.first->ToLocal(*Collisionpoint), *Normal);
			Movement2 = event.second->GetMovement(event.second->ToLocal(*Collisionpoint)) -
							event.first->GetMovement(event.first->ToLocal(*Collisionpoint));
		}
		
		sfp::Vector2f friction = Friction(event.first, event.second);
		Bounce(event.first, event.second);
		
		if(!event.first->IsFixed()) event.first->Impulse(event.first->ToLocal(*Collisionpoint), -friction);
		if(!event.second->IsFixed()) event.second->Impulse(event.second->ToLocal(*Collisionpoint), friction);
		
		event.collisionpoint.pop();
		event.collisionnormal.pop();
		event.intersection.pop();
		event.convexobjects.pop();
	}
}


sfp::Vector2f sfp::Collision::Friction(sfp::Object* first, sfp::Object* second)
{
	sfp::Vector2f friction(-Normal->y, Normal->x);
	friction *= CrossProduct(Movement2, *Normal);
	
	if(first->IsFixed())
	{
//		friction *= std::abs(DotProduct(second->GetImpulse(), *Normal));
	}
	else if(second->IsFixed())
	{
//		friction *= std::abs(DotProduct(first->GetImpulse(), *Normal));
	}
	else
	{
//		friction *= std::abs(DotProduct(Movement2 * (first->GetMass() + second->GetMass()), *Normal));
	}
	
	if(myContactManager.GetContact(first, second) != NULL && myContactManager.GetContact(first, second)->type == Contact::StaticContact)
	{
		friction *= first->GetStaticFriction() * second->GetStaticFriction();
	}
	else
	{
		friction *= first->GetDynamicFriction() * second->GetDynamicFriction();
	}
	
	return friction;
}


void sfp::Collision::Bounce(sfp::Object* first, sfp::Object* second)
{
	if(first->IsFixed())
	{
		BounceFixed(*second, *Collisionpoint, -*Normal, Movement, Restitution);
		
		second->AddIntersection(-*Intersection, sf::Vector2f()); //FIXME
	}
	else if(second->IsFixed())
	{
		BounceFixed(*first, *Collisionpoint, *Normal, Movement, Restitution);
		
		first->AddIntersection(*Intersection, sf::Vector2f()); //FIXME
	}
	else
	{
		sfp::Vector2f r(*Collisionpoint - second->ToGlobal(second->GetConvexShape(B).GetShapeCenter()));
		
		Bounce(*first, *second, *Collisionpoint, *Normal, Movement);
		
		float factor = first->GetMass() / (first->GetMass() + second->GetMass());
		
		first->AddIntersection(*Intersection * factor, sf::Vector2f()); //FIXME
		second->AddIntersection(-*Intersection * (1-factor), sf::Vector2f()); //FIXME
	}
}



void sfp::Collision::Bounce(sfp::Object& first, sfp::Object& second, const sfp::Vector2f& P, const sfp::Vector2f& n, const sfp::Vector2f& vr)
{
	sfp::Vector2f r1(P-first.GetPosition());
	sfp::Vector2f r2(P-second.GetPosition());
			
	float j=-(1 + first.GetRestitution()*second.GetRestitution()) * DotProduct(vr, n);
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
			
	float j = - ++e * DotProduct(vr, n);
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
		myContactManager.UpdateContacts();
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
	for(std::list<sfp::Object*>::iterator it = myObjects.begin(); it != myObjects.end(); ++it)
	{
		std::list<sfp::Object*>::iterator it2 = it;
		for(++it2; it2 != myObjects.end(); ++it2)
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




void sfp::Collision::ComputeContact(sfp::CollisionEvent& event)
{
	myContactManager.ComputeContact(event);
}





bool sfp::Collision::CheckCollision(sfp::Object& first, sfp::Object& second)
{
	//FIXME BoundingBoxes
	
	myCollisionEvents.top().CollisionType = NoCollision; //sfp::BoundingBox; //FIXME
	
	bool isCollided = false;
	
	for(size_t i = 0; i < first.GetConvexShapeCount(); ++i) //Schleife für die konkaven Formen von Obj 1
	{
		switch(first.GetConvexShape(i).GetShapeType())
		{
			case Shape::Type::Polygon:
			case Shape::Type::Rectangle:
				for(size_t j = 0; j < second.GetConvexShapeCount(); ++j) //Von Objekt 2
				{
					switch(second.GetConvexShape(j).GetShapeType())
					{
						case Shape::Type::Polygon:
						case Shape::Type::Rectangle:
							//if(BoundingBoxes)
								if(PolygonPolygon(first, second, i, j))
								{
									isCollided=true;
									myCollisionEvents.top().convexobjects.push(std::make_pair(i,j));
								}
						break;
						
						case Shape::Type::Plane:
							if(PlanePolygon(second, first, j, i))
							{
								isCollided=true;
								myCollisionEvents.top().convexobjects.push(std::make_pair(i,j));
								myCollisionEvents.top().collisionnormal.top()*=-1.f;
							}
						break;
						
						case Shape::Type::Circle:
							//if(BoundingBoxes)
								if(PolygonCircle(first, second, i, j))
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
				for(size_t j = 0; j < second.GetConvexShapeCount(); ++j) //Von Objekt 2
				{
					switch(second.GetConvexShape(j).GetShapeType())
					{
						case Shape::Type::Polygon:
						case Shape::Type::Rectangle:
							if(PlanePolygon(first, second, i, j))
							{
								isCollided=true;
								myCollisionEvents.top().convexobjects.push(std::make_pair(i,j));
							}
						break;
						
						case Shape::Type::Circle:
							if(PlaneCircle(first, second, i, j))
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
				for(size_t j = 0; j < second.GetConvexShapeCount(); ++j) //Von Objekt 2
				{
					switch(second.GetConvexShape(j).GetShapeType())
					{
						case Shape::Type::Polygon:
						case Shape::Type::Rectangle:
							//if(BoundingBoxes)
								if(PolygonCircle(second, first, j, i))
								{
									isCollided=true;
									myCollisionEvents.top().convexobjects.push(std::make_pair(i,j));
									myCollisionEvents.top().collisionnormal.top()*=-1.f;
								}
						break;
						
						case Shape::Type::Plane:
							if(PlaneCircle(second, first, j, i))
							{
								isCollided=true;
								myCollisionEvents.top().convexobjects.push(std::make_pair(i,j));
								myCollisionEvents.top().collisionnormal.top()*=-1.f;
							}
						break;
						
						case Shape::Type::Circle:
							//if(BoundingBoxes)
								if(CircleCircle(first, second, i, j))
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
				for(size_t j = 0; j < second.GetConvexShapeCount(); ++j) //Von Objekt 2
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



bool sfp::Collision::PlanePolygon(sfp::Object& first, sfp::Object& second, size_t a, size_t b)
{
	second.GetConvexShape(b).GetSeparatingAxis().UpdateRotation(second.GetRotation());
	
	if(second.GetConvexShape(b).GetPointCount() > 1)
	{
		sfp::Vector2f vec;
		if(ComputeSAT(first, second, a, b, vec))
		{
			ComputePlanePolygon(first, second, a, b);
			myCollisionEvents.top().intersection.push(vec);
			return true;
		}
	}
	
	return false;
}


bool sfp::Collision::PolygonPolygon(sfp::Object& first, sfp::Object& second, size_t a, size_t b)
{
	first.GetConvexShape(a).GetSeparatingAxis().UpdateRotation(first.GetRotation());
	second.GetConvexShape(b).GetSeparatingAxis().UpdateRotation(second.GetRotation());
	
	if(first.GetConvexShape(a).GetPointCount() > 1 && second.GetConvexShape(b).GetPointCount() > 1)
	{
		sfp::Vector2f vec1, vec2;
		if(ComputeSAT(first, second, a, b, vec1) && ComputeSAT(second, first, b, a, vec2))
		{
			ComputePolygonPolygon(first, second, a, b);
			sfp::Vector2f& vec = vec1.GetForce() < vec2.GetForce() ? vec1 : vec2;
			if(DotProduct(vec, second.ToGlobal(second.GetConvexShape(b).GetShapeCenter()) - first.ToGlobal(first.GetConvexShape(a).GetShapeCenter())) >= 0)
			//FIXME >= oder >
			{
				vec *= -1.f;
			}
			myCollisionEvents.top().intersection.push(vec);
			
			return true;
		}
	}
	
	return false;
}


bool sfp::Collision::ComputeSAT(sfp::Object& first, sfp::Object& second, size_t a, size_t b, sfp::Vector2f& vec)
{
	bool first_iteration = true;
	
	for(size_t i = 0; i < first.GetConvexShape(a).GetSeparatingAxis().GetAxisCount(); ++i)
	{
		float firstmin = DotProduct(first.GetConvexShape(a).GetSeparatingAxis().GetAx(i), first.ToGlobal(first.GetConvexShape(a).GetPoint(0)));
		float firstmax = firstmin;
		
		for(size_t j=1; j < first.GetConvexShape(a).GetPointCount(); ++j)
		{
			float tmp = DotProduct(first.GetConvexShape(a).GetSeparatingAxis().GetAx(i), first.ToGlobal(first.GetConvexShape(a).GetPoint(j)));
			
			if(tmp > firstmax) firstmax=tmp;
			else if(tmp < firstmin) firstmin=tmp;
		}
		
		
		float secondmin = DotProduct(first.GetConvexShape(a).GetSeparatingAxis().GetAx(i), second.ToGlobal(second.GetConvexShape(b).GetPoint(0)));
		float secondmax = secondmin;
		
		for(size_t j=1; j < second.GetConvexShape(b).GetPointCount(); ++j)
		{
			float tmp = DotProduct(first.GetConvexShape(a).GetSeparatingAxis().GetAx(i), second.ToGlobal(second.GetConvexShape(b).GetPoint(j)));
			
			if(tmp > secondmax) secondmax=tmp;
			else if(tmp < secondmin) secondmin=tmp;
		}
		
		if(firstmax < secondmin || firstmin > secondmax)
			return false;
		
		
		float k1 = firstmax - secondmin;
		float k2 = secondmax - firstmin;

		sfp::Vector2f tmp;
		if(std::abs(k1) < std::abs(k2))
			tmp = first.GetConvexShape(a).GetSeparatingAxis().GetAx(i) * k1;
		else
			tmp = first.GetConvexShape(a).GetSeparatingAxis().GetAx(i) * k2;
		
		if(first_iteration)
		{
			vec = tmp;
			first_iteration = false;
		}
		else if(tmp.x*tmp.x + tmp.y*tmp.y < vec.x*vec.x + vec.y*vec.y)
		{
			vec = tmp;
		}
	}
	
	return true;
}


void sfp::Collision::ComputePolygonPolygon(sfp::Object& first, sfp::Object& second, size_t a, size_t b)
{
	sfp::Vector2f p1; sfp::Vector2f p2;
	char points = 0;
	
	for(size_t i = 0; i < first.GetConvexShape(a).GetPointCount(); ++i)
	{
		sfp::FloatLine line1;
		if(i == first.GetConvexShape(a).GetPointCount()-1)
		{
			line1 = sfp::FloatLine(first.ToGlobal(first.GetConvexShape(a).GetPoint(i)),
					first.ToGlobal(first.GetConvexShape(a).GetPoint(0))-first.ToGlobal(first.GetConvexShape(a).GetPoint(i)));
		}
		else
		{
			line1 = sfp::FloatLine(first.ToGlobal(first.GetConvexShape(a).GetPoint(i)),
					first.ToGlobal(first.GetConvexShape(a).GetPoint(i+1))-first.ToGlobal(first.GetConvexShape(a).GetPoint(i)));
		}
		
		for(size_t j = 0; j < second.GetConvexShape(b).GetPointCount(); ++j)
		{
			sfp::FloatLine line2;
			if(j == second.GetConvexShape(b).GetPointCount()-1)
			{
				line2 = sfp::FloatLine(second.ToGlobal(second.GetConvexShape(b).GetPoint(j)),
						second.ToGlobal(second.GetConvexShape(b).GetPoint(0))-second.ToGlobal(second.GetConvexShape(b).GetPoint(j)));
			}
			else
			{
				line2 = sfp::FloatLine(second.ToGlobal(second.GetConvexShape(b).GetPoint(j)),
						second.ToGlobal(second.GetConvexShape(b).GetPoint(j+1))-second.ToGlobal(second.GetConvexShape(b).GetPoint(j)));
			}
			
			float r1 = 0; float r2 = 0;
			
			if(((line1.Intersects(line2, r1)) && (line2.Intersects(line1, r2))) && ((r1 >= 0.f && r1 <= 1.f) && (r2 >= 0.f && r2 <= 1.f)))
			{
				if(points == 0)
				{
					p1 = line1.Point + r1 * line1.Direction;
					points = 1;
				}
				else
				{
					p2 = line1.Point + r1 * line1.Direction;
					points = 2;
				}
			}
		}
	}
	
	if(points == 2)
	{
		myCollisionEvents.top().collisionpoint.push((p1+p2)/2.f);
		
		myCollisionEvents.top().collisionnormal.push(p2-p1);
		myCollisionEvents.top().collisionnormal.top().Normalize();
		myCollisionEvents.top().collisionnormal.top().Rotate(90);
		if(DotProduct(myCollisionEvents.top().collisionnormal.top(),
		second.ToGlobal(second.GetConvexShape(b).GetShapeCenter()) - first.ToGlobal(first.GetConvexShape(a).GetShapeCenter())) < 0)
			myCollisionEvents.top().collisionnormal.top()*=-1.f;
		
	}
	else
	{
		myCollisionEvents.top().collisionpoint.push(sf::Vector2f());
		myCollisionEvents.top().collisionnormal.push(sf::Vector2f());
	}
}



void sfp::Collision::ComputePlanePolygon(sfp::Object& first, sfp::Object& second, size_t a, size_t b)
{
	sfp::Vector2f p1; sfp::Vector2f p2;
	
	char points = 0;
	
	sfp::Vector2f direction(first.GetConvexShape(a).GetPlaneNormal()); direction.Rotate(90);
	sfp::FloatLine planeline(first.ToGlobal(first.GetConvexShape(a).GetShapeCenter()), direction);
	
	for(size_t i = 0; i < second.GetConvexShape(b).GetPointCount(); ++i)
	{
		sfp::FloatLine line;
		if(i == second.GetConvexShape(b).GetPointCount()-1)
		{
			line = sfp::FloatLine(second.ToGlobal(second.GetConvexShape(b).GetPoint(i)),
					second.ToGlobal(second.GetConvexShape(b).GetPoint(0))-second.ToGlobal(second.GetConvexShape(b).GetPoint(i)));
		}
		else
		{
			line = sfp::FloatLine(second.ToGlobal(second.GetConvexShape(b).GetPoint(i)),
					second.ToGlobal(second.GetConvexShape(b).GetPoint(i+1))-second.ToGlobal(second.GetConvexShape(b).GetPoint(i)));
		}
		
		float r = 0;
	//	planeline.Intersects(line, r1);
		line.Intersects(planeline, r);
		
		if(r > 0.f && r < 1.f)
		{
			if(points == 0)
			{
				p1 = line.Point + r * line.Direction;
				points = 1;
			}
			else
			{
				p2 = line.Point + r * line.Direction;
				points = 2;
			}
		}
	}
	
	if(points == 2)
	{
		myCollisionEvents.top().collisionpoint.push((p1+p2)/2.f);
		myCollisionEvents.top().collisionnormal.push(first.GetConvexShape(a).GetPlaneNormal());
	}
	else
	{
		myCollisionEvents.top().collisionpoint.push(sf::Vector2f());
		myCollisionEvents.top().collisionnormal.push(sf::Vector2f());
	}
}



bool sfp::Collision::PolygonCircle(sfp::Object& first, sfp::Object& second, size_t i, size_t j)
{
if(i!=j) {;}
return false;
}



bool sfp::Collision::PlaneCircle(sfp::Object& first, sfp::Object& second, size_t i, size_t j)
{
	sfp::Vector2f hyp(first.ToGlobal(first.GetConvexShape(i).GetShapeCenter())-second.ToGlobal(second.GetConvexShape(j).GetShapeCenter()));
	float distance(std::abs(std::cos((first.GetConvexShape(i).GetPlaneNormal().GetDirection()-hyp.GetDirection())*M_PI/180.f)) * hyp.GetForce());
	
	if(distance >= second.GetConvexShape(j).GetCircleRadius())
		return false;
	
	myCollisionEvents.top().collisionpoint.push(second.ToGlobal(second.GetConvexShape(j).GetShapeCenter())-first.GetConvexShape(i).GetPlaneNormal()*distance);
	myCollisionEvents.top().collisionnormal.push(first.GetConvexShape(i).GetPlaneNormal());
	myCollisionEvents.top().intersection.push(first.GetConvexShape(i).GetPlaneNormal()*(second.GetConvexShape(j).GetCircleRadius()-distance));
	
	return true;
}



bool sfp::Collision::CircleCircle(sfp::Object& first, sfp::Object& second, size_t i, size_t j)
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
	distance+=first.ToGlobal(first.GetConvexShape(i).GetShapeCenter());
	
	myCollisionEvents.top().collisionpoint.push(distance);
	
	return true;
}




