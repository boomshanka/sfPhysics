#include "Objects.hpp"


float sfp::Time::ElapsedTime=0;
sf::Clock sfp::Time::Frametime = sf::Clock();



sfp::Object::Object()
{

}



#ifdef SFML_GRAPHICS_ENABLED

sfp::Object::Object(sf::Shape& shape)
:myDrawable(&shape)
{
	for(unsigned int i=0; i<shape.GetPointsCount();++i)
	{
		Polygon::AddPoint(shape.GetPointPosition(i));
	}
	sfp::Physicable::ComputeArea(sfp::Polygon::myPoints);
}

#endif

