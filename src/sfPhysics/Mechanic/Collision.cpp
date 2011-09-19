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


#include <sfPhysics/Mechanic/Collision.hpp>
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
					SwapEventObjects(event);
					PlanePolygon(event);
					SwapEventObjects(event);
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
	event.first->GetConvexShape(event.FirstConvexObject).GetSeparatingAxis().UpdateRotation(event.first->GetRotation());
	event.second->GetConvexShape(event.SecondConvexObject).GetSeparatingAxis().UpdateRotation(event.second->GetRotation());
	
	if(event.first->GetConvexShape(event.FirstConvexObject).GetPointCount() > 1 && event.second->GetConvexShape(event.SecondConvexObject).GetPointCount() > 1)
	{
		sfp::Vector2f vec1, vec2;
		if(ComputeSAT(event, vec1))
		{
			SwapEventObjects(event); // Andere Seite testen!
			if(ComputeSAT(event, vec2))
			{
				SwapEventObjects(event); // Zurück tauschen
				
				ComputePolygonPolygonContact(event);
				sfp::Vector2f& vec = vec1.GetForce() < vec2.GetForce() ? vec1 : vec2;
				if(DotProduct(vec, event.second->ToGlobal(event.second->GetConvexShape(event.SecondConvexObject).GetShapeCenter()) -
								event.first->ToGlobal(event.first->GetConvexShape(event.FirstConvexObject).GetShapeCenter()) ) >= 0)  //FIXME >= oder >
				{
					event.Intersection = -vec;
				}
				else
				{
					event.Intersection = vec;
				}
				event.CollisionType = sfp::PreciseCollision;
			}
			else
			{
				SwapEventObjects(event); // Zurück tauschen
			}
		}
	}
}


void sfp::Collision::PolygonCircle(sfp::CollisionEvent& event)
{

}


void sfp::Collision::PlanePolygon(sfp::CollisionEvent& event)
{
	event.second->GetConvexShape(event.SecondConvexObject).GetSeparatingAxis().UpdateRotation(event.second->GetRotation());
	
	if(event.second->GetConvexShape(event.SecondConvexObject).GetPointCount() > 1)
	{
		sfp::Vector2f vec;
		if(ComputeSAT(event, vec))
		{
			ComputePlanePolygonContact(event);
			event.Intersection = -vec;
			event.CollisionType = sfp::PreciseCollision;
		}
	}
}


bool sfp::Collision::ComputeSAT(sfp::CollisionEvent& event, sfp::Vector2f& vec)
{
	bool first_iteration = true;
	
	for(size_t i = 0; i < event.first->GetConvexShape(event.FirstConvexObject).GetSeparatingAxis().GetAxisCount(); ++i)
	{
		float firstmin = DotProduct(event.first->GetConvexShape(event.FirstConvexObject).GetSeparatingAxis().GetAx(i), 
									event.first->ToGlobal(event.first->GetConvexShape(event.FirstConvexObject).GetPoint(0)));
		float firstmax = firstmin;
		
		for(size_t j = 1; j < event.first->GetConvexShape(event.FirstConvexObject).GetPointCount(); ++j)
		{
			float tmp = DotProduct(event.first->GetConvexShape(event.FirstConvexObject).GetSeparatingAxis().GetAx(i),
									event.first->ToGlobal(event.first->GetConvexShape(event.FirstConvexObject).GetPoint(j)));
			
			if(tmp > firstmax) firstmax = tmp;
			else if(tmp < firstmin) firstmin = tmp;
		}
		
		
		float secondmin = DotProduct(event.first->GetConvexShape(event.FirstConvexObject).GetSeparatingAxis().GetAx(i),
							event.second->ToGlobal(event.second->GetConvexShape(event.SecondConvexObject).GetPoint(0)));
		float secondmax = secondmin;
		
		for(size_t j = 1; j < event.second->GetConvexShape(event.SecondConvexObject).GetPointCount(); ++j)
		{
			float tmp = DotProduct(event.first->GetConvexShape(event.FirstConvexObject).GetSeparatingAxis().GetAx(i),
									event.second->ToGlobal(event.second->GetConvexShape(event.SecondConvexObject).GetPoint(j)));
			
			if(tmp > secondmax) secondmax = tmp;
			else if(tmp < secondmin) secondmin = tmp;
		}
		
		if(firstmax < secondmin || firstmin > secondmax)
			return false;
		
		
		float k1 = firstmax - secondmin;
		float k2 = secondmax - firstmin;

		sfp::Vector2f tmp;
		if(std::abs(k1) < std::abs(k2))
			tmp = event.first->GetConvexShape(event.FirstConvexObject).GetSeparatingAxis().GetAx(i) * k1;
		else
			tmp = event.first->GetConvexShape(event.FirstConvexObject).GetSeparatingAxis().GetAx(i) * k2;
		
		if(first_iteration)
		{
			vec = tmp;
			first_iteration = false;
		}
		else if(tmp.GetSquaredLength() < vec.GetSquaredLength())
		{
			vec = tmp;
		}
	}
	
	return true;
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


void sfp::Collision::ComputePolygonPolygonContact(sfp::CollisionEvent& event)
{
	sfp::Vector2f p1; sfp::Vector2f p2;
	unsigned int points = 0;
	
	for(size_t i = 0; i < event.first->GetConvexShape(event.FirstConvexObject).GetPointCount(); ++i)
	{
		sfp::FloatLine line1;
		if(i == event.first->GetConvexShape(event.FirstConvexObject).GetPointCount() - 1)
		{
			line1 = sfp::FloatLine(event.first->ToGlobal(event.first->GetConvexShape(event.FirstConvexObject).GetPoint(i)),
					event.first->ToGlobal(event.first->GetConvexShape(event.FirstConvexObject).GetPoint(0)) -
					event.first->ToGlobal(event.first->GetConvexShape(event.FirstConvexObject).GetPoint(i)));
		}
		else
		{
			line1 = sfp::FloatLine(event.first->ToGlobal(event.first->GetConvexShape(event.FirstConvexObject).GetPoint(i)),
					event.first->ToGlobal(event.first->GetConvexShape(event.FirstConvexObject).GetPoint(i+1)) -
					event.first->ToGlobal(event.first->GetConvexShape(event.FirstConvexObject).GetPoint(i)));
		}
		
		for(size_t j = 0; j < event.second->GetConvexShape(event.SecondConvexObject).GetPointCount(); ++j)
		{
			sfp::FloatLine line2;
			if(j == event.second->GetConvexShape(event.SecondConvexObject).GetPointCount() - 1)
			{
				line2 = sfp::FloatLine(event.second->ToGlobal(event.second->GetConvexShape(event.SecondConvexObject).GetPoint(j)),
						event.second->ToGlobal(event.second->GetConvexShape(event.SecondConvexObject).GetPoint(0)) -
						event.second->ToGlobal(event.second->GetConvexShape(event.SecondConvexObject).GetPoint(j)));
			}
			else
			{
				line2 = sfp::FloatLine(event.second->ToGlobal(event.second->GetConvexShape(event.SecondConvexObject).GetPoint(j)),
						event.second->ToGlobal(event.second->GetConvexShape(event.SecondConvexObject).GetPoint(j+1)) -
						event.second->ToGlobal(event.second->GetConvexShape(event.SecondConvexObject).GetPoint(j)));
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
		event.Collisionpoint = (p1 + p2) / 2.f;
		
		event.Collisionnormal = p2 - p1;
		event.Collisionnormal.Normalize();
		event.Collisionnormal.Rotate(90);
		if(DotProduct(event.Collisionnormal, event.second->ToGlobal(event.second->GetConvexShape(event.SecondConvexObject).GetShapeCenter()) -
						event.first->ToGlobal(event.first->GetConvexShape(event.FirstConvexObject).GetShapeCenter())) < 0)
			event.Collisionnormal *= -1.f;
		
	}
}


void sfp::Collision::ComputePlanePolygonContact(sfp::CollisionEvent& event)
{
	sfp::Vector2f p1; sfp::Vector2f p2;
	
	unsigned int points = 0;
	
	sfp::Vector2f direction(event.first->GetConvexShape(event.FirstConvexObject).GetPlaneNormal()); direction.Rotate(90);
	sfp::FloatLine planeline(event.first->ToGlobal(event.first->GetConvexShape(event.FirstConvexObject).GetShapeCenter()), direction);
	
	for(size_t i = 0; i < event.second->GetConvexShape(event.SecondConvexObject).GetPointCount(); ++i)
	{
		sfp::FloatLine line;
		if(i == event.second->GetConvexShape(event.SecondConvexObject).GetPointCount()-1)
		{
			line = sfp::FloatLine(event.second->ToGlobal(event.second->GetConvexShape(event.SecondConvexObject).GetPoint(i)),
					event.second->ToGlobal(event.second->GetConvexShape(event.SecondConvexObject).GetPoint(0)) -
					event.second->ToGlobal(event.second->GetConvexShape(event.SecondConvexObject).GetPoint(i)));
		}
		else
		{
			line = sfp::FloatLine(event.second->ToGlobal(event.second->GetConvexShape(event.SecondConvexObject).GetPoint(i)),
					event.second->ToGlobal(event.second->GetConvexShape(event.SecondConvexObject).GetPoint(i+1)) -
					event.second->ToGlobal(event.second->GetConvexShape(event.SecondConvexObject).GetPoint(i)));
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
		event.Collisionpoint = (p1 + p2) / 2.f;
		event.Collisionnormal = event.first->GetConvexShape(event.FirstConvexObject).GetPlaneNormal();
	}
}


