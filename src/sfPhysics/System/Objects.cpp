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
:myIsFixed(false)
{
	#ifdef SFML_ENABLED
	myDrawable=NULL;
	myLengthfactor=1;
	#endif
}



sfp::Object::Object(const Shape& shape)
:myIsFixed(false)
{
	#ifdef SFML_ENABLED
	myDrawable=NULL;
	myLengthfactor=1;
	#endif
	
	SetShape(shape);
}



sfp::Object::~Object()
{
	
}




void sfp::Object::SetShape(const Shape& shape)
{
	ShapeManager::SetShape(shape);
	if(ShapeManager::type.myShapeType==sfp::Shape::Type::Plane)
	{
		myIsFixed=true;
	}
	
	SetCenter(ShapeManager::myCenter);
	Physicable::SetArea(ShapeManager::myArea);
	Physicable::myInertiaMoment=ShapeManager::myInertiaMoment*Physicable::myDensity;
	
	myLocalBox=ShapeManager::GetShapeBox();
	myLocalBox.Left -= myCenter.x;
	myLocalBox.Top -= myCenter.y;
}




void sfp::Object::SetCenter(const sf::Vector2f& center)
{//FIXME InertiaMoment neu berechnen
	if(!ShapeManager::IsUpdated())
		Update();
	
	myCenter=Physicable::myCenter=center;
	
	#ifdef SFML_ENABLED
	if(myDrawable!=NULL)
		myDrawable->SetOrigin(center*myLengthfactor);
	#endif
}



sf::Vector2f sfp::Object::ToGlobal(const sf::Vector2f& local) const
{
	sfp::Vector2f global(local-myCenter);
	
	global.Rotate(myRotation);
	global+=myPosition;
	
	return global;
}


sf::Vector2f sfp::Object::ToLocal(const sf::Vector2f& global) const
{
	sfp::Vector2f local(global);
	
	local-=myPosition;
	local.Rotate(-myRotation);
	
	return local+myCenter;
}



const sfp::FloatBox& sfp::Object::GetLocalBox()
{
	if(!ShapeManager::IsUpdated())
		Update();
	
	return myLocalBox;
}


sfp::FloatBox sfp::Object::GetBoundingBox()
{
	sf::Vector2f vec(ToGlobal(sf::Vector2f(GetLocalBox().Left,myLocalBox.Top)));
	
	sfp::FloatBox back;
	
	back.Left=vec.x;
	back.Width=vec.x;
	back.Top=vec.y;
	back.Height=vec.y;
	
	vec = ToGlobal(ToGlobal(sf::Vector2f(myLocalBox.Left+myLocalBox.Width,myLocalBox.Top)));
	if(back.Left>vec.x)
		back.Left=vec.x;
	else if(back.Width<vec.x)
		back.Width=vec.x;
	if(back.Top>vec.y)
		back.Top=vec.y;
	else if(back.Height<vec.y)
		back.Height=vec.y;
	
	vec = ToGlobal(ToGlobal(sf::Vector2f(myLocalBox.Left+myLocalBox.Width,myLocalBox.Top+myLocalBox.Height)));
	if(back.Left>vec.x)
		back.Left=vec.x;
	else if(back.Width<vec.x)
		back.Width=vec.x;
	if(back.Top>vec.y)
		back.Top=vec.y;
	else if(back.Height<vec.y)
		back.Height=vec.y;
	
	vec = ToGlobal(ToGlobal(sf::Vector2f(myLocalBox.Left,myLocalBox.Top+myLocalBox.Height)));
	if(back.Left>vec.x)
		back.Left=vec.x;
	else if(back.Width<vec.x)
		back.Width=vec.x;
	if(back.Top>vec.y)
		back.Top=vec.y;
	else if(back.Height<vec.y)
		back.Height=vec.y;
	
	
	back.Width-=back.Left;
	back.Height-=back.Top;
	
	return back;
}




void sfp::Object::Impulse(sfp::Vector2f position, sfp::Vector2f normal, float impulse)
{
	position-=myCenter;
	position.Rotate(myRotation);
	
	AddVelocity((impulse/Physicable::myMass) * normal);
	AddRotationVelocity(impulse/Physicable::myInertiaMoment * CrossProduct(position, normal) * 180.f/static_cast<float>(M_PI));
}



sfp::Vector2f sfp::Object::GetMovement(sfp::Vector2f position) const
{
	position-=myCenter;
	position.Rotate(myRotation + 90.f);
	
	return sfp::Vector2f(position * (Physicable::myRotationVelocity*static_cast<float>(M_PI)/180.f) + Physicable::myVelocity);
}


sfp::Vector2f sfp::Object::GetMovement(sfp::Vector2f position, const sfp::Vector2f& normal) const
{
	position-=myCenter;
	position.Rotate(myRotation);
	
	sfp::Vector2f movement(normal * (Physicable::myRotationVelocity*static_cast<float>(M_PI)/180.f));
	
	movement*=CrossProduct(position, normal);
	movement+=Physicable::myVelocity;
	
	return movement;
}



void sfp::Object::Update()
{
	ShapeManager::Update();
	
	SetCenter(ShapeManager::myCenter);
	Physicable::SetArea(ShapeManager::myArea);
	Physicable::myInertiaMoment=ShapeManager::myInertiaMoment*Physicable::myDensity;
	
	myLocalBox=ShapeManager::GetShapeBox();
	myLocalBox.Left -= myCenter.x;
	myLocalBox.Top -= myCenter.y;
}


/******************************************************************************
 **                              SFML_Graphics                               **
 ******************************************************************************/


#ifdef SFML_ENABLED


sfp::Object::Object(sf::Shape& shape, float lengthfactor)
:myIsFixed(false),
myLengthfactor(lengthfactor)
{
	SetShape(shape);
}



sfp::Object::Object(sf::Sprite& sprite, float lengthfactor)
:myIsFixed(false),
myLengthfactor(lengthfactor)
{
	SetSprite(sprite);
}



sfp::Object::Object(sf::Drawable& drawable, float lengthfactor)
:myIsFixed(false),
myLengthfactor(lengthfactor)
{
	SetDrawable(drawable);
}



sfp::Object::Object(sf::Drawable& drawable, const Shape& shape, float lengthfactor)
:myIsFixed(false),
myLengthfactor(lengthfactor)
{
	myDrawable=&drawable;
	
	SetShape(shape);
	if(ShapeManager::type.myShapeType==sfp::Shape::Type::Plane)
	{
		myIsFixed=true;
		
	}//FIXME was ist mit Lengthfactor?
	
	myPosition=drawable.GetPosition()/myLengthfactor;
	myRotation=drawable.GetRotation();
}



sfp::Object::Object(sf::Shape& shape, const sf::Vector2f& center, float lengthfactor)
:myIsFixed(false),
myLengthfactor(lengthfactor)
{
	SetShape(shape, center);
}



sfp::Object::Object(sf::Sprite& sprite, const sf::Vector2f& center, float lengthfactor)
:myIsFixed(false),
myLengthfactor(lengthfactor)
{
	SetSprite(sprite, center);
}



sfp::Object::Object(sf::Drawable& drawable, const sf::Vector2f& center, float lengthfactor)
:myIsFixed(false),
myLengthfactor(lengthfactor)
{
	SetDrawable(drawable, center);
}





void sfp::Object::SetShape(sf::Shape& sfShape)
{
	myDrawable=&sfShape;
	
	sfp::Shape shape;
	for(unsigned int i=0; i<sfShape.GetPointsCount();++i)
	{
		shape.AddPoint(sfShape.GetPointPosition(i)/myLengthfactor);
	}
	shape.SetShapeType(Shape::Type::Polygon);
	SetShape(shape);
	
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


