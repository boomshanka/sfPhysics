#ifndef SFPHYSICS_COLLISION_HPP
#define SFPHYSICS_COLLISION_HPP


#include <sfPhysics/System/Objects.hpp>
#include <sfPhysics/Collision/CollisionEvent.hpp>

#include <list>
#include <stack>



namespace sfp
{
	
	class Collision
	{
		private:
			std::list<sfp::Object*> myObjects;
			std::stack<CollisionEvent> myCollisionEvents;
			
			bool myNoCollisionEventEnabled;
		public:
			Collision();
			~Collision();
			
			void AddObject(sfp::Object& object) {myObjects.push_back(&object);}
			
			bool GetCollision(sfp::CollisionEvent&);
			
			void Bounce(sfp::CollisionEvent&);
			
		protected:
			void UpdateCollisionEvents();
			bool CheckCollision(sfp::Object&, sfp::Object&);
			
			bool PolygonPolygon(sfp::Object&, sfp::Object&);
			bool PolygonPlane(sfp::Object&, sfp::Object&);
			bool PolygonCircle(sfp::Object&, sfp::Object&);
			bool PlaneCircle(sfp::Object&, sfp::Object&, unsigned int, unsigned int);
			bool CircleCircle(sfp::Object&, sfp::Object&, unsigned int, unsigned int);
	};
}


#endif



