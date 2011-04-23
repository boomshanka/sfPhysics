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
#include <sfPhysics/System/Contact.hpp>

#include <list>
#include <stack>



namespace sfp
{
	
	class Collision
	{
		private:
			std::list<sfp::Object*> myObjects;
			std::stack<CollisionEvent> myCollisionEvents;
			
			sfp::ContactManager myContactManager;
			
			bool myNoCollisionEventEnabled; //FIXME Rename/Remove
			
		public:
			Collision();
			~Collision();
			
			void AddObject(sfp::Object& object) {myObjects.push_back(&object);}
			
			bool PollCollision(sfp::CollisionEvent&);
			
			
			bool CheckCollision(sfp::Object&, sfp::Object&);
			
			bool PolygonPolygon(sfp::Object&, sfp::Object&, size_t, size_t);
			bool PolygonCircle(sfp::Object&, sfp::Object&, size_t, size_t);
			bool PlanePolygon(sfp::Object&, sfp::Object&, size_t, size_t);
			bool PlaneCircle(sfp::Object&, sfp::Object&, size_t, size_t);
			bool CircleCircle(sfp::Object&, sfp::Object&, size_t, size_t);
			
			
			void CollisionResponse(sfp::CollisionEvent&);
			
		private:
			void ComputeContact(sfp::CollisionEvent&);
			sfp::Vector2f Friction(sfp::Object*, sfp::Object*);
			void Bounce(sfp::Object*, sfp::Object*);
			
			void Bounce(sfp::Object& first, sfp::Object& second, const sfp::Vector2f& P, const sfp::Vector2f& n, const sfp::Vector2f& vr);
			void BounceFixed(sfp::Object& obj, const sfp::Vector2f& P, const sfp::Vector2f& n, const sfp::Vector2f& vr, float e);
			
			void UpdateCollisionEvents();
			
			bool ComputeSAT(sfp::Object& first, sfp::Object& second, size_t a, size_t b, sfp::Vector2f&);
			void ComputePolygonPolygon(sfp::Object& first, sfp::Object& second, size_t a, size_t b);
			void ComputePlanePolygon(sfp::Object& first, sfp::Object& second, size_t a, size_t b);
			
			
			sfp::Vector2f Movement;
			sfp::Vector2f Movement2;
			sfp::Vector2f* Collisionpoint;
			sfp::Vector2f* Normal;
			sfp::Vector2f* Intersection;
			float Restitution;
			size_t A;
			size_t B;
	};
}


#endif



