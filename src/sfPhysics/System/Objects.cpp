/******************************************************************************
 **	sfPhysics - A simple 2D physics engine
 ** Copyright (C) 2011  Olaf Vogt aka Boomshanka
 ** 
 ** This program is free software; you can redistribute it and/or modify it
 ** under the terms of the GNU General Public License as published by the Free
 ** Software Foundation; either version 3 of the License, or (at your option)
 ** any later version. 
 ** 
 ** This program is distributed in the hope that it will be useful, but WITHOUT
 ** ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 ** FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 ** more details. 
 ** 
 ** You should have received a copy of the GNU General Public License along
 ** with this program; if not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************/


#include <sfPhysics/System/Objects.hpp>



sfp::Object::Object()
:mySeparatingAxis(NULL),
mySeparatingAxisEnabled(true),
myIsFixed(false)
{
	#ifdef SFML_ENABLED
	myDrawable=NULL;
	myLengthfactor=1;
	#endif
}



sfp::Object::Object(const Shape& shape)
:mySeparatingAxis(NULL),
mySeparatingAxisEnabled(true),
myIsFixed(false)
{
	#ifdef SFML_ENABLED
	myDrawable=NULL;
	myLengthfactor=1;
	#endif
	
	ShapeManager::SetShape(shape);
	
	if(ShapeManager::myShapeType==sfp::Plane)
	{
		myIsFixed=true;
	}
	
	SetCenter(ShapeManager::myCenter);
	Physicable::SetArea(ShapeManager::myArea);
	Physicable::myInertiaMoment=ShapeManager::myInertiaMoment*Physicable::myDensity;
}



sfp::Object::~Object()
{
	delete mySeparatingAxis;
}




void sfp::Object::SetShape(const Shape& shape)
{
	ShapeManager::SetShape(shape);
	if(ShapeManager::myShapeType==sfp::Plane)
	{
		myIsFixed=true;
	}
	
	SetCenter(ShapeManager::myCenter);
	Physicable::SetArea(ShapeManager::myArea);
	Physicable::myInertiaMoment=ShapeManager::myInertiaMoment*Physicable::myDensity;
}




void sfp::Object::ComputeArea()
{
	ShapeManager::ComputeArea();
	
	SetCenter(ShapeManager::myCenter);
	Physicable::SetArea(ShapeManager::myArea);
	Physicable::myInertiaMoment=ShapeManager::myInertiaMoment*Physicable::myDensity;
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
	
	delete mySeparatingAxis;
	mySeparatingAxis=NULL;
	
	#ifdef SFML_ENABLED
	if(myDrawable!=NULL)
		myDrawable->SetOrigin(center*myLengthfactor);
	#endif
}




sf::Vector2f sfp::Object::GetLocalPoint(unsigned int index) const
{
	return GetPoint(index)-myCenter;
}



sf::Vector2f sfp::Object::GetLocalPoint(unsigned int shape, unsigned int index) const
{
	return GetConvexShape(shape).GetPoint(index)-myCenter;
}




sf::Vector2f sfp::Object::GetLocalShapeCenter(unsigned int shape) const
{
	return GetConvexShape(shape).GetShapeCenter()-myCenter;
}




sf::Vector2f sfp::Object::ToGlobal(const sf::Vector2f& local) const
{
	sfp::Vector2f global(local);
	
	global.Rotate(myRotation);
	global+=myPosition;
	
	return global;
}



sf::Vector2f sfp::Object::ToLocal(const sf::Vector2f& global) const
{
	sfp::Vector2f local(global);
	
	local-=myPosition;
	local.Rotate(-myRotation);
	
	return local;
}




void sfp::Object::Impulse(sfp::Vector2f position, sfp::Vector2f normal, float impulse)
{
	normal.Normalize();
	position.Rotate(myRotation);
	
	AddVelocity((impulse/Physicable::myMass) * normal);
	AddRotationVelocity(impulse/Physicable::myInertiaMoment * position.CrossProduct(normal));
}



sfp::Vector2f sfp::Object::GetMovement(const sfp::Vector2f& position) const
{
	sfp::Vector2f movement(Physicable::myRotationVelocity * position);
	movement.Rotate(myRotation);
	
	movement+=Physicable::myVelocity;
	
	return movement;
}



/******************************************************************************
 **                              SFML_Graphics                               **
 ******************************************************************************/


#ifdef SFML_ENABLED


sfp::Object::Object(sf::Shape& shape, float lengthfactor)
:mySeparatingAxis(NULL),
mySeparatingAxisEnabled(true),
myIsFixed(false),
myLengthfactor(lengthfactor)
{
	SetShape(shape);
}



sfp::Object::Object(sf::Sprite& sprite, float lengthfactor)
:mySeparatingAxis(NULL),
mySeparatingAxisEnabled(true),
myIsFixed(false),
myLengthfactor(lengthfactor)
{
	SetSprite(sprite);
}



sfp::Object::Object(sf::Drawable& drawable, float lengthfactor)
:mySeparatingAxis(NULL),
mySeparatingAxisEnabled(true),
myIsFixed(false),
myLengthfactor(lengthfactor)
{
	SetDrawable(drawable);
}



sfp::Object::Object(sf::Drawable& drawable, const Shape& shape, float lengthfactor)
:mySeparatingAxis(NULL),
mySeparatingAxisEnabled(true),
myIsFixed(false),
myLengthfactor(lengthfactor)
{
	myDrawable=&drawable;
	
	ShapeManager::SetShape(shape);
	if(ShapeManager::myShapeType==sfp::Plane)
	{
		myIsFixed=true;
		
	}//FIXME was ist mit Lengthfactor?
	
	SetCenter(ShapeManager::myCenter);
	Physicable::SetArea(ShapeManager::myArea);
	Physicable::myInertiaMoment=ShapeManager::myInertiaMoment*Physicable::myDensity;
	
	myPosition=drawable.GetPosition()/myLengthfactor;
	myRotation=drawable.GetRotation();
}



sfp::Object::Object(sf::Shape& shape, const sf::Vector2f& center, float lengthfactor)
:mySeparatingAxis(NULL),
mySeparatingAxisEnabled(true),
myIsFixed(false),
myLengthfactor(lengthfactor)
{
	SetShape(shape, center);
}



sfp::Object::Object(sf::Sprite& sprite, const sf::Vector2f& center, float lengthfactor)
:mySeparatingAxis(NULL),
mySeparatingAxisEnabled(true),
myIsFixed(false),
myLengthfactor(lengthfactor)
{
	SetSprite(sprite, center);
}



sfp::Object::Object(sf::Drawable& drawable, const sf::Vector2f& center, float lengthfactor)
:mySeparatingAxis(NULL),
mySeparatingAxisEnabled(true),
myIsFixed(false),
myLengthfactor(lengthfactor)
{
	SetDrawable(drawable, center);
}


/******************************************************************************
 **                           End of constructor                             **
 ******************************************************************************/



void sfp::Object::SetShape(sf::Shape& sfShape)
{
	myDrawable=&sfShape;
	
	sfp::Shape shape;
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


