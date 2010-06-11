#ifndef COLLISION_HPP
#define COLLISION_HPP


#include <SFML/Graphics.hpp>

#include "Objects.hpp"
#include "CollisionEvent.hpp"


#include <iostream>
#include <list>
#include <queue>
#include <cmath>

#define _USE_MATH_DEFINES


namespace sfp
{
	
	class Collision
	{
		private:
			std::list<sfp::Object*> myObjects;
			std::queue<CollisionEvent> myCollisionEvents;
		public:
			Collision();
			~Collision();
			
			void AddObject(sfp::Object& object) {myObjects.push_back(&object);}
			
			bool GetCollision(sfp::CollisionEvent&);
			
			void Bounce(sfp::Object&, sfp::Object&);
			
		protected:
			void UpdateCollisionEvents();
			
	};
}


#endif



