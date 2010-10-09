#ifndef COLLISION_HPP
#define COLLISION_HPP


#include <sfPhysics/Objects.hpp>
#include <sfPhysics/CollisionEvent.hpp>

#include <SFML/Graphics.hpp>

#include <list>
#include <queue>



namespace sfp
{
	
	class Collision
	{
		private:
			std::list<sfp::Object*> myObjects;
			std::queue<CollisionEvent> myCollisionEvents;
			
			bool myNoCollisionEventEnabled;
		public:
			Collision();
			~Collision();
			
			void AddObject(sfp::Object& object) {myObjects.push_back(&object);}
			
			bool GetCollision(sfp::CollisionEvent&);
			
			void Bounce(sfp::Object&, sfp::Object&);
			
		protected:
			void UpdateCollisionEvents();
			bool CheckCollision(sfp::Object&, sfp::Object&);
			
	};
}


#endif



