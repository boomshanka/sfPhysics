#ifndef COLLISIONEVENT_HPP
#define COLLISIONEVENT_HPP


#include <sfPhysics/Objects.hpp>


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
			sfp::Object* firstobject;
			sfp::Object* secondobject;
		public:
			CollisionEvent() : CollisionTime(0) {}
			CollisionEvent(sfp::Object& first, sfp::Object& second) { firstobject=&first; secondobject=&second; }
			
			CollisionEventType CollisionType;
			
			float CollisionTime;
			
			
			sfp::Object& GetFirstObject() {return *firstobject;}
			sfp::Object& GetSecondObject() {return *secondobject;}
	};

}

#endif

