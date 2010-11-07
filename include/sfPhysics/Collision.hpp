#ifndef COLLISION_HPP
#define COLLISION_HPP


#include <sfPhysics/Objects.hpp>
#include <sfPhysics/CollisionEvent.hpp>

#include <SFML/Graphics.hpp>

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
			
			bool ShapeShape(sfp::Object&, sfp::Object&);
			bool ShapePlane(sfp::Object&, sfp::Object&);
			bool ShapeCircle(sfp::Object&, sfp::Object&);
			bool PlaneCircle(sfp::Object&, sfp::Object&);
			bool CircleCircle(sfp::Object&, sfp::Object&, unsigned int, unsigned int);
	};
}


#endif



