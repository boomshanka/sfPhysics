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
		BoundingBox,
		PreciseCollision
	};

	class CollisionEvent
	{
		friend class Collision;
		
		private:
			sfp::Object* first;
			sfp::Object* second;
			
			std::stack<sf::Vector2f> collisionpoint;
			std::stack<sfp::Vector2f> collisionnormal;
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


