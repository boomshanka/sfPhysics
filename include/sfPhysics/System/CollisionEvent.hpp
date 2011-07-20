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


#ifndef SFPHYSICS_COLLISIONEVENT_HPP
#define SFPHYSICS_COLLISIONEVENT_HPP

#include <sfPhysics/System/Objects.hpp>


namespace sfp
{
	enum CollisionEventType
	{
		NoCollision = 0,
		BoundingBoxCollision = 1,
		PreciseCollision = 2
	};

	class CollisionEvent
	{
		friend class Collision;
		friend class CollisionManager;
		friend class ContactManager;
		
		private:
			sfp::Object* first;
			sfp::Object* second;
			
		public:
			CollisionEventType CollisionType;
			
			sfp::Vector2f Collisionpoint;
			sfp::Vector2f Collisionnormal;
			sfp::Vector2f Intersection;
			std::size_t FirstConvexObject;
			std::size_t SecondConvexObject;
			
			sfp::Vector2f R1;
			sfp::Vector2f R2;
			sfp::Vector2f Movement;
			float Impulse;
			
		public:
			CollisionEvent() : CollisionType(NoCollision) {}
			CollisionEvent(sfp::Object& one, sfp::Object& two) : CollisionType(NoCollision) {first=&one; second=&two;}
			CollisionEvent(sfp::Object* one, sfp::Object* two) : CollisionType(NoCollision) {first = one; second = two;}		
			
			sfp::Object& GetFirstObject() {return *first;}
			sfp::Object& GetSecondObject() {return *second;}
	};

}

#endif



