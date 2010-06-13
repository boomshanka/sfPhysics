#ifndef COLLISIONEVENT_HPP
#define COLLISIONEVENT_HPP


#include "Objects.hpp"


namespace sfp
{

	class CollisionEvent
	{
		friend class Collision;
		
		private:
			sfp::Object* firstobject;
			sfp::Object* secondobject;
		public:
			sfp::Object& GetFirstObject() {return *firstobject;}
			sfp::Object& GetSecondObject() {return *secondobject;}
	};

}

#endif


