#include "Objects.hpp"

#include <cmath>


float sfp::Time::ElapsedTime=0;
sf::Clock sfp::Time::Frametime = sf::Clock();



sfp::Object::Object()
:mySeparatingAxis(NULL),
mySeparatingAxisEnabled(true)
{

}


sfp::Object::~Object()
{
	delete mySeparatingAxis;
}




void sfp::Object::ComputeSeparatingAxis()
{
	delete mySeparatingAxis;
	mySeparatingAxis=new sfp::SeparatingAxis(*this);
}





sf::Vector2f sfp::Object::ToGlobal(const sf::Vector2f& local)
{
	sf::Vector2f global;
	
	global.x = local.x - Physicable::myCenter.x;
	global.y = local.y - Physicable::myCenter.y;
	
	float line = sqrt(global.x*global.x + global.y*global.y);
	
	float angle;
	if(line!=0)
	{
		angle = asin(global.x/line);
		if(local.y<0) //oder 2. winkel für global.y=cos(winkel2)*line FIXME auch ToLocal
			angle=3.141592654f-angle;
	}
	else
	{
		angle = 0;
	}
	
	angle -= Physicable::myRotation;
	
	global.x = sin(angle)*line;
	global.y = cos(angle)*line;
	
	global += Physicable::myGlobalPosition;
	
	return global;
}


sf::Vector2f sfp::Object::ToLocal(const sf::Vector2f& global)
{
	sf::Vector2f local;
	
	local.x = global.x-Physicable::myGlobalPosition.x - Physicable::myCenter.x;
	local.y = global.y-Physicable::myGlobalPosition.y - Physicable::myCenter.y;
	
	float line = sqrt(local.x*local.x + local.y*local.y);
	
	float angle;
	if(line!=0)
	{
		angle = asin(local.x/line);
		if(local.y<0)
			angle=3.141592654f-angle;
	}
	else
	{
		angle=0;
	}
	
	angle += Physicable::myRotation;
	
	local.x = sin(angle)*line;
	local.y = cos(angle)*line;
	
	return local;
}




#ifdef SFML_GRAPHICS_ENABLED

sfp::Object::Object(sf::Shape& shape)
:myDrawable(&shape),
mySeparatingAxis(NULL),
mySeparatingAxisEnabled(true)
{
	for(unsigned int i=0; i<shape.GetPointsCount();++i)
	{
		Polygon::AddPoint(shape.GetPointPosition(i));
	}
	Physicable::ComputeArea(sfp::Polygon::myPoints);
	
	Physicable::myGlobalPosition=shape.GetPosition()-shape.GetOrigin();
}

#endif

