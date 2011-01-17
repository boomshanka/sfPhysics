#include <sfPhysics/System/Objects.hpp>



sfp::Object::Object()
:mySeparatingAxis(NULL),
mySeparatingAxisEnabled(true)
{
	#ifdef SFML_ENABLED
	myDrawable=NULL;
	myLengthfactor=0;
	#endif
}


sfp::Object::Object(const Shape& shape)
:mySeparatingAxis(NULL),
mySeparatingAxisEnabled(true)
{
	#ifdef SFML_ENABLED
	myDrawable=NULL;
	myLengthfactor=0;
	#endif
	
	ShapeManager::SetShape(shape);
	ComputeArea();
}




sfp::Object::~Object()
{
	delete mySeparatingAxis;
}



void sfp::Object::ComputeArea()
{
	ShapeManager::ComputeArea();
	
	SetCenter(ShapeManager::myCenter);
	Physicable::SetArea(ShapeManager::myArea);
	Physicable::myInertiaMoment=ShapeManager::myInertiaMoment*Physicable::myDensity; //FIXME fläche muss rausgekürzt werden (bzw mit Dichte multiplizieren)
	//std::cerr<<Physicable::myInertiaMoment<<std::endl; //FIXME
	//in Physicable muss myInertiaMoment bei masse/dichteveränderungen angepasst werden!
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
	myCenter=Physicable::myCenter=center;
	
	delete mySeparatingAxis; //FIXME wirklich nötig?
	mySeparatingAxis=NULL;
	
	#ifdef SFML_ENABLED
	if(myDrawable!=NULL)
		myDrawable->SetOrigin(center*myLengthfactor);
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


void sfp::Object::Force(const sf::Vector2f& position, const sfp::Vector2f& force)
{
	sfp::Vector2f hebelarm=position;
	hebelarm.SetDirection(hebelarm.GetDirection()-myRotation);
	//momentarm/=5.f;//FIXME
	float moment=hebelarm.CrossProduct(force);
	Physicable::AddRotationImpulse(-moment);
	Physicable::AddImpulse(force);
}


const sfp::Vector2f& sfp::Object::GetForce(const sf::Vector2f& position) const
{
/*	sfp::Vector2f force;
	force.x=
	
	
	//=Physicable::GetImpulse();
	
	
	return force;*/
}



sfp::Vector2f sfp::Object::GetMovement(const sfp::Vector2f& position) const
{
	sfp::Vector2f movement;
	movement.x=(2*M_PI*position.GetForce())*(Physicable::myRotationSpeed/360.f);
	float direction=position.GetDirection();
	if(Physicable::myRotationSpeed<0) {direction+=90;} else {direction-=90;}
	movement.SetDirection(direction);
	
	movement+=Physicable::mySpeed;
	
	return movement;
}



//------------------------------------------------------------------------------------------//
									/*SFML_Graphics*/
//------------------------------------------------------------------------------------------//



#ifdef SFML_ENABLED

sfp::Object::Object(sf::Shape& shape, float lengthfactor)
:mySeparatingAxis(NULL),
mySeparatingAxisEnabled(true),
myLengthfactor(lengthfactor)
{
	SetShape(shape);
}



sfp::Object::Object(sf::Sprite& sprite, float lengthfactor)
:mySeparatingAxis(NULL),
mySeparatingAxisEnabled(true),
myLengthfactor(lengthfactor)
{
	SetSprite(sprite);
}



sfp::Object::Object(sf::Drawable& drawable, float lengthfactor)
:mySeparatingAxis(NULL),
mySeparatingAxisEnabled(true),
myLengthfactor(lengthfactor)
{
	SetDrawable(drawable);
}



sfp::Object::Object(sf::Drawable& drawable, const Shape& shape, float lengthfactor)
:mySeparatingAxis(NULL),
mySeparatingAxisEnabled(true),
myLengthfactor(lengthfactor)
{
	myDrawable=&drawable;
	
	ShapeManager::SetShape(shape);//FIXME was ist mit Lengthfactor?
	ComputeArea();
	myPosition=drawable.GetPosition()/myLengthfactor;
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



void sfp::Object::SetShape(sf::Shape& sfShape)
{
	myDrawable=&sfShape;
	
	Shape shape;
	for(unsigned int i=0; i<sfShape.GetPointsCount();++i)
	{
		shape.AddPoint(sfShape.GetPointPosition(i)/myLengthfactor);
	}
	ShapeManager::SetShape(shape);
	
	ComputeArea();
	
	myPosition=sfShape.GetPosition()/myLengthfactor;
	myRotation=sfShape.GetRotation();
}



void sfp::Object::SetSprite(sf::Sprite& sprite)
{
	myDrawable=&sprite;
	//FIXME
}



void sfp::Object::SetDrawable(sf::Drawable& drawable)
{
	myDrawable=&drawable;
	
	SetCenter(drawable.GetOrigin()/myLengthfactor);
	
	myPosition=drawable.GetPosition()/myLengthfactor;
	myRotation=drawable.GetRotation();
}



void sfp::Object::SetLengthFactor(float factor)
{/*FIXME
	factor=
	myLengthfactor=factor;
	
	myPosition=myDrawable->GetPosition()/myLengthfactor;
	Shape shape;
	for(unsigned int i=0; i<ShapeManager::GetPointsCount();++i)
	{
		shape.AddPoint(ShapeManager::GetPointPosition(i)/myLengthfactor);
	}
	ShapeManager::SetShape(shape);*/
}



#endif // SFML_ENABLED

