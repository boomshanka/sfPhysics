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
:myFirstConvexShapes(0), mySecondConvexShapes(0)
{
}



sfp::Collision::~Collision()
{
}




/*
bool sfp::Collision::PlanePolygon(sfp::Object& first, sfp::Object& second, size_t a, size_t b)
{
	second.GetConvexShape(b).GetSeparatingAxis().UpdateRotation(second.GetRotation());
	
	if(second.GetConvexShape(b).GetPointCount() > 1)
	{
		sfp::Vector2f vec;
		if(ComputeSAT(first, second, a, b, vec))
		{
			ComputePlanePolygon(first, second, a, b);
			myCollisionEvents.top().intersection.push(-vec);
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
*/

//////////


bool sfp::Collision::PollCollisions(sfp::CollisionEvent& event)
{
	if((mySecondObject != event.second) || (myFirstObject != event.first))
	{
		if(event.first->GetConvexShapeCount() == 0 || (event.first->IsFixed() && event.second->IsFixed()) || !CheckBoundingBoxCollision(event)) //FIXME
			return false;
		
		myFirstConvexShapes = 0;
		mySecondConvexShapes = 0;
		
		myFirstObject = event.first;
		mySecondObject = event.second;
	}
	
	event.CollisionType = sfp::BoundingBoxCollision;
	
	while(event.CollisionType == sfp::BoundingBoxCollision)
	{
		if(myFirstConvexShapes == event.first->GetConvexShapeCount())
		{
			if(++mySecondConvexShapes == event.second->GetConvexShapeCount())
			{
				myFirstObject = NULL;
				mySecondObject = NULL;
				return false;
			}
		
			myFirstConvexShapes = 0;
		}
		
		event.FirstConvexObject = myFirstConvexShapes;
		event.SecondConvexObject = mySecondConvexShapes;
		SeparateObjects(event);
		
		++myFirstConvexShapes;
	}
	
	ComputeCollisionProperties(event);
	
	return true;
}


void sfp::Collision::SeparateObjects(sfp::CollisionEvent& event)
{
	switch(event.first->GetConvexShape(myFirstConvexShapes).GetShapeType())
	{
		case Shape::Type::Polygon:
		case Shape::Type::Rectangle:
			switch(event.second->GetConvexShape(mySecondConvexShapes).GetShapeType())
			{
				case Shape::Type::Polygon:
				case Shape::Type::Rectangle:
					//if(BoundingBoxes)
						PolygonPolygon(event);
				break;
				
				case Shape::Type::Plane:
					PlanePolygon(event);
				break;
				
				case Shape::Type::Circle:
					//if(BoundingBoxes)
						PolygonCircle(event);
				break;
				
				case Shape::Type::NegCircle:
					//FIXME
				break;
				
				default:
				break;
			}
		break;
				
		case Shape::Type::Plane:
			switch(event.second->GetConvexShape(mySecondConvexShapes).GetShapeType())
			{
				case Shape::Type::Polygon:
				case Shape::Type::Rectangle:
					PlanePolygon(event);
				break;
				
				case Shape::Type::Circle:
					PlaneCircle(event);
				break;
				
				case Shape::Type::NegCircle:
					//FIXME
				break;
				
				case Shape::Type::Plane:
				default:
				break;
			}
		break;
			
		case Shape::Type::Circle:
			switch(event.second->GetConvexShape(mySecondConvexShapes).GetShapeType())
			{
				case Shape::Type::Polygon:
				case Shape::Type::Rectangle:
					//if(BoundingBoxes)
						PolygonCircle(event);
				break;
				
				case Shape::Type::Plane:
					SwapEventObjects(event);
					PlaneCircle(event);
					SwapEventObjects(event);
				break;
				
				case Shape::Type::Circle:
					//if(BoundingBoxes)
						CircleCircle(event);
				break;
				
				case Shape::Type::NegCircle:
					//FIXME
				break;
				
				default:
				break;
			}
		break;
		
		case Shape::Type::NegCircle:
			//switch(second.GetConvexShape(mySecondConvexShapes).GetShapeType())
			{
			
			}
		break;
		
		default:
		break;
	}
}



bool sfp::Collision::CheckBoundingBoxCollision(sfp::CollisionEvent& event)
{
	return true;
}



bool sfp::Collision::CheckCollision(sfp::CollisionEvent& event)
{
	return false;
}



void sfp::Collision::PolygonPolygon(sfp::CollisionEvent& event)
{

}


void sfp::Collision::PolygonCircle(sfp::CollisionEvent& event)
{

}


void sfp::Collision::PlanePolygon(sfp::CollisionEvent& event)
{

}


void sfp::Collision::PlaneCircle(sfp::CollisionEvent& event)
{
	sfp::Vector2f hyp(event.first->ToGlobal(event.first->GetConvexShape(event.FirstConvexObject).GetShapeCenter()) -
						event.second->ToGlobal(event.second->GetConvexShape(event.SecondConvexObject).GetShapeCenter()));
	float distance = std::abs(std::cos((event.first->GetConvexShape(event.FirstConvexObject).GetPlaneNormal().GetDirection() -
						hyp.GetDirection())*M_PI/180.f)) * hyp.GetForce();
	
	if(distance < event.second->GetConvexShape(event.SecondConvexObject).GetCircleRadius()) //FIXME <=?
	{
		event.Collisionpoint = event.second->ToGlobal(event.second->GetConvexShape(event.SecondConvexObject).GetShapeCenter()) -
								event.first->GetConvexShape(event.FirstConvexObject).GetPlaneNormal() * distance;
		event.Collisionnormal = event.first->GetConvexShape(event.FirstConvexObject).GetPlaneNormal();
		event.Intersection = -event.first->GetConvexShape(event.FirstConvexObject).GetPlaneNormal() *
								(event.second->GetConvexShape(event.SecondConvexObject).GetCircleRadius() - distance);
		
		event.CollisionType = sfp::PreciseCollision;
	}
}


void sfp::Collision::CircleCircle(sfp::CollisionEvent& event)
{
	sfp::Vector2f distance(event.second->ToGlobal(event.second->GetConvexShape(event.SecondConvexObject).GetShapeCenter()) -
								event.first->ToGlobal(event.first->GetConvexShape(event.FirstConvexObject).GetShapeCenter()));
	float length = (event.first->GetConvexShape(event.FirstConvexObject).GetCircleRadius() +
					event.second->GetConvexShape(event.SecondConvexObject).GetCircleRadius()) - distance.GetForce();
	
	if(length > 0)
	{
		event.Collisionnormal = distance.GetUnitVector();
		event.Intersection = -event.Collisionnormal * length; // FIXME Warum -
		distance.SetForce(event.first->GetConvexShape(event.FirstConvexObject).GetCircleRadius() -
						((event.first->GetConvexShape(event.FirstConvexObject).GetCircleRadius() +
				 			event.second->GetConvexShape(event.SecondConvexObject).GetCircleRadius()) - distance.GetForce())/2.f);
		distance += event.first->ToGlobal(event.first->GetConvexShape(event.FirstConvexObject).GetShapeCenter());
		event.Collisionpoint = distance;
		
		event.CollisionType = sfp::PreciseCollision;
	}
}




void sfp::Collision::SwapEventObjects(sfp::CollisionEvent& event)
{
	sfp::Object* obj = event.first;
	event.first = event.second;
	event.second = obj;
	
	std::size_t convex = event.FirstConvexObject;
	event.FirstConvexObject = event.SecondConvexObject;
	event.SecondConvexObject = convex;
	
	event.Collisionnormal *= -1.f;
	event.Intersection *= -1.f;
}



void sfp::Collision::ComputeCollisionProperties(sfp::CollisionEvent& event)
{
	event.R1 = event.Collisionpoint - event.first->GetPosition();
	event.R2 = event.Collisionpoint - event.second->GetPosition();
	
	if(event.first->IsFixed())
	{
		event.Movement = event.second->GetMovement(event.second->ToLocal(event.Collisionpoint));
		event.Impulse = (1 + event.first->GetRestitution() * event.second->GetRestitution()) * DotProduct(event.Movement, event.Collisionnormal);
		event.Impulse /= 1.f/event.second->GetMass() +
				std::abs(DotProduct((1.f/event.second->GetInertiaMoment() * CrossProduct(event.R2, event.Collisionnormal) * event.R2), event.Collisionnormal));
	}
	else if(event.second->IsFixed())
	{
		event.Movement = -event.first->GetMovement(event.first->ToLocal(event.Collisionpoint));
		event.Impulse = -(1 + event.first->GetRestitution() * event.second->GetRestitution()) * DotProduct(event.Movement, event.Collisionnormal);
		event.Impulse /= 1.f/event.first->GetMass() +
				std::abs(DotProduct((1.f/event.first->GetInertiaMoment() * CrossProduct(event.R1, event.Collisionnormal) * event.R1), event.Collisionnormal));
	}
	else
	{
		event.Movement = event.second->GetMovement(event.second->ToLocal(event.Collisionpoint)) -
						event.first->GetMovement(event.first->ToLocal(event.Collisionpoint));
		event.Impulse = -(1 + event.first->GetRestitution() * event.second->GetRestitution()) * DotProduct(event.Movement, event.Collisionnormal);
		event.Impulse /= 1.f/event.first->GetMass() + 1.f/event.second->GetMass() +
				std::abs(DotProduct((1.f/event.first->GetInertiaMoment() * CrossProduct(event.R1, event.Collisionnormal) * event.R1 +
						1.f/event.second->GetInertiaMoment() * CrossProduct(event.R2, event.Collisionnormal) * event.R2), event.Collisionnormal));
	}
	
	//FIXME friction?
}


