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


#ifndef SFPHYSICS_COLLISION_HPP
#define SFPHYSICS_COLLISION_HPP


#include <sfPhysics/System/Objects.hpp>
#include <sfPhysics/System/CollisionEvent.hpp>

#include <list>
#include <stack>



namespace sfp
{
	
	class Collision
	{
		private:
			std::list<sfp::Object*> myObjects;
			std::stack<CollisionEvent> myCollisionEvents;
			
			bool myNoCollisionEventEnabled; //FIXME Rename/Remove
		public:
			Collision();
			~Collision();
			
			void AddObject(sfp::Object& object) {myObjects.push_back(&object);}
			
			bool PollCollision(sfp::CollisionEvent&);
			
			
			bool CheckCollision(sfp::Object&, sfp::Object&);
			
			bool PolygonPolygon(sfp::Object&, sfp::Object&, unsigned int, unsigned int);
			bool PolygonPlane(sfp::Object&, sfp::Object&, unsigned int, unsigned int);
			bool PolygonCircle(sfp::Object&, sfp::Object&, unsigned int, unsigned int);
			bool PlaneCircle(sfp::Object&, sfp::Object&, unsigned int, unsigned int);
			bool CircleCircle(sfp::Object&, sfp::Object&, unsigned int, unsigned int);
			
			void Bounce(sfp::CollisionEvent&);
			
		private:
			void Bounce(sfp::Object& first, sfp::Object& second, const sfp::Vector2f& P, const sfp::Vector2f& n, const sfp::Vector2f& vr);
			void BounceFixed(sfp::Object& obj, const sfp::Vector2f& P, const sfp::Vector2f& n, const sfp::Vector2f& vr, float e);
			
			void UpdateCollisionEvents();
			
			bool ComputePolygonPolygon(sfp::Object& first, sfp::Object& second, unsigned int a, unsigned int b);
			void ComputePolygonPolygonCollision(sfp::Object& first, sfp::Object& second, unsigned int a, unsigned int b);
	};
}


#endif



