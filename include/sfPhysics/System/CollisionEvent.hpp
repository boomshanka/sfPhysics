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

#include <stack>
#include <utility>



namespace sfp
{
	enum CollisionEventType
	{
		NoCollision = 0,
		BoundingBox = 1,
		PreciseCollision = 2
	};

	class CollisionEvent
	{
		friend class Collision;
		
		private:
			sfp::Object* first;
			sfp::Object* second;
			
			std::stack<sf::Vector2f> collisionpoint;
			std::stack<sfp::Vector2f> collisionnormal;
			std::stack<sfp::Vector2f> intersection;
			std::stack<std::pair<unsigned int, unsigned int> > convexobjects;
		public:
			CollisionEvent() : CollisionTime(0) {}
			CollisionEvent(sfp::Object& one, sfp::Object& two) { first=&one; second=&two; }
			
			CollisionEventType CollisionType;
			
			float CollisionTime;
			
			
			sfp::Object& GetFirstObject() {return *first;}
			sfp::Object& GetSecondObject() {return *second;}
	};

}

#endif


