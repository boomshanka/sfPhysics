#include <sfPhysics/Objects.hpp>

#include <cmath>


float sfp::Time::ElapsedTime=0;
sf::Clock sfp::Time::Frametime = sf::Clock();



sfp::Object::Object()
:mySeparatingAxis(NULL),
mySeparatingAxisEnabled(true)
{
	#ifdef SFML_GRAPHICS_ENABLED
	myDrawable=NULL;
	#endif
}


sfp::Object::Object(const Polygon& polygon)
:mySeparatingAxis(NULL),
mySeparatingAxisEnabled(true)
{
	#ifdef SFML_GRAPHICS_ENABLED
	myDrawable=NULL;
	#endif
	
	PolygonManager::SetPolygon(polygon);
	ComputeArea();
}




sfp::Object::~Object()
{
	delete mySeparatingAxis;
}




void sfp::Object::ComputeSeparatingAxis()
{
	if(mySatRotation!=myRotation || mySeparatingAxis==NULL)
	{
		delete mySeparatingAxis;
		mySeparatingAxis=new sfp::SeparatingAxis(*this);
		mySatRotation=myRotation;
	}
}



void sfp::Object::SetCenter(const sf::Vector2f& center)
{
	Physicable::myCenter=center;
//	PolygonManager::SetPolygonCenter(center);
	myCenter=center;
	
	delete mySeparatingAxis;
	mySeparatingAxis=NULL;
	
	#ifdef SFML_GRAPHICS_ENABLED
	if(myDrawable!=NULL)
		myDrawable->SetOrigin(center);
	#endif
}





sf::Vector2f sfp::Object::ToGlobal(const sf::Vector2f& local) const
{
	sf::Vector2f global=myPosition;
	
	sfp::Vector2f position=local-myCenter;
	
	position.SetDirection(position.GetDirection()-myRotation); //
	
	global+=position;
	
	return global;
}


sf::Vector2f sfp::Object::ToLocal(const sf::Vector2f& global) const
{
	sf::Vector2f local;
	
	local.x = global.x-myPosition.x - myCenter.x;
	local.y = global.y-myPosition.y - myCenter.y;
	
	float line = sqrt(local.x*local.x + local.y*local.y);
	
	float angle;
	if(line!=0)
	{
		angle = asin(local.x/line);
		if(local.y<0)
			angle=3.141592654f-angle; //FIXME ist - wirklich richtig (nicht *)? Funktion überprüfen!!!
	}
	else
	{
		angle=0;
	}
	
	angle += myRotation;
	
	local.x = sin(angle)*line;
	local.y = cos(angle)*line;
	
	return local;
}



//------------------------------------------------------------------------------------------//
									/*SFML_Graphics*/
//------------------------------------------------------------------------------------------//



#ifdef SFML_GRAPHICS_ENABLED

sfp::Object::Object(sf::Shape& shape)
:mySeparatingAxis(NULL),
mySeparatingAxisEnabled(true)
{
	SetShape(shape);
}



sfp::Object::Object(sf::Sprite& sprite)
:mySeparatingAxis(NULL),
mySeparatingAxisEnabled(true)
{
	SetSprite(sprite);
}



sfp::Object::Object(sf::Drawable& drawable)
:mySeparatingAxis(NULL),
mySeparatingAxisEnabled(true)
{
	SetDrawable(drawable);
}



sfp::Object::Object(sf::Drawable& drawable, const Polygon& polygon)
:mySeparatingAxis(NULL),
mySeparatingAxisEnabled(true)
{
	myDrawable=&drawable;
	
	PolygonManager::SetPolygon(polygon);
	ComputeArea();
	myPosition=drawable.GetPosition();
	myRotation=drawable.GetRotation();
}





sfp::Object::Object(sf::Shape& shape, const sf::Vector2f& center)
:mySeparatingAxis(NULL),
mySeparatingAxisEnabled(true)
{
	SetShape(shape, center);
}



sfp::Object::Object(sf::Sprite& sprite, const sf::Vector2f& center)
:mySeparatingAxis(NULL),
mySeparatingAxisEnabled(true)
{
	SetSprite(sprite, center);
}



sfp::Object::Object(sf::Drawable& drawable, const sf::Vector2f& center)
:mySeparatingAxis(NULL),
mySeparatingAxisEnabled(true)
{
	SetDrawable(drawable, center);
}




// ------------------------- End of constructor ------------------------- //



void sfp::Object::SetShape(sf::Shape& shape)
{
	myDrawable=&shape;
	
	Polygon polygon;
	for(unsigned int i=0; i<shape.GetPointsCount();++i)
	{
		polygon.AddPoint(shape.GetPointPosition(i));
	}
	PolygonManager::SetPolygon(polygon);
	
	ComputeArea();
	
	myPosition=shape.GetPosition();
	myRotation=shape.GetRotation();
}



void sfp::Object::SetSprite(sf::Sprite& sprite)
{
	myDrawable=&sprite;
	//FIXME
}



void sfp::Object::SetDrawable(sf::Drawable& drawable)
{
	myDrawable=&drawable;
	
	SetCenter(drawable.GetOrigin());
	
	myPosition=drawable.GetPosition();
	myRotation=drawable.GetRotation();
}



#endif // SFML_GRAPHICS_ENABLED

