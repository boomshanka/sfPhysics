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


#include <sfPhysics/Mechanic/Shape.hpp>



sfp::Shape::Shape()
:myShapeType(Shape::Type::Nothing), myCircleRadius(0)
{
	
}



sfp::Shape::Shape(const Shape& shape)
:myShapeType(shape.myShapeType),
myPoints(shape.myPoints),
myCircleRadius(shape.myCircleRadius), myPlaneNormal(shape.myPlaneNormal),
myCenter(shape.myCenter)
{
	Update();
}




void sfp::Shape::Update()
{
	myArea=1;
	myInertiaMoment=1;
	
	mySeparatingAxis.Clear();
	
	switch(myShapeType)
	{
		case Shape::Type::Polygon:
		case Shape::Type::Rectangle: //FIXME
			ComputePolygonArea();
			mySeparatingAxis.ComputeSeparatingAxis(myPoints);
			break;
		
		case Shape::Type::Circle:
			ComputeCircleArea();
			break;
		
		case Shape::Type::Plane:
			mySeparatingAxis.AddAx(myPlaneNormal);
			break;
		
		default:
			break;
	}
}


void sfp::Shape::ComputePolygonArea()
{
	myCenter = sf::Vector2f(0,0);
	myInertiaMoment = 0;
	myArea = 0;
	
	for(std::size_t i = 2; i < myPoints.size(); ++i)
	{
		sfp::Vector2f line = myPoints[0] - myPoints[i-1];
		float a = line.GetForce();
		line = myPoints[i-1] - myPoints[i];
		float b = line.GetForce();
		line = myPoints[i] - myPoints[0];
		float c = line.GetForce();
		
		float area = 0.25 * std::sqrt((a+b+c) * (a+b-c) * (b+c-a) * (c+a-b));
		sf::Vector2f center((myPoints[0] + myPoints[i-1] + myPoints[i]) / 3.f);
		
		//Schwerpunkte addieren
		sfp::Vector2f diff(center - myCenter);
		diff *= (area / (area+myArea));
		myCenter += diff;
		
		//Trägheitsmoment verschieben
		myInertiaMoment += myArea * std::pow(diff.GetForce(),2);
		//Trägheitsmoment von Dreieck verschieben & addieren
		diff = (center - (myCenter-diff)) - diff;
		myInertiaMoment += ComputeTriangleMoment(myPoints[0], myPoints[i-1], myPoints[i], area) + area * std::pow(diff.GetForce(), 2);
		
		myArea += area;
	}
}


float sfp::Shape::ComputeTriangleMoment(const sf::Vector2f& A, const sf::Vector2f& B, const sf::Vector2f& C, float area)
{
	sfp::Vector2f a(C-B);
	sfp::Vector2f b(A-C);
	sfp::Vector2f c(B-A);
	
	return (1.f/36.f * area * (std::pow(a.GetForce(), 2) + std::pow(b.GetForce(), 2) + std::pow(c.GetForce(), 2)));
}



void sfp::Shape::ComputeCircleArea()
{
	myArea = M_PI * myCircleRadius*myCircleRadius;
	myInertiaMoment = 0.5 * myArea * myCircleRadius*myCircleRadius; //Später wird Dichte dazu multipliziert (Fläche*Dichte=Gewicht)
}




sfp::Shape sfp::Shape::Rectangle()
{
	Shape shape;
	
	return shape;
}//FIXME jeweils ein Update();


sfp::Shape sfp::Shape::Line()
{
	Shape shape;
	
	return shape;
}


sfp::Shape sfp::Shape::Plane(const sf::Vector2f& center, float angle)
{
	sfp::Vector2f normal(1,0);
	normal.SetDirection(angle);
	return Plane(center, normal);
}


sfp::Shape sfp::Shape::Plane(const sf::Vector2f& center, sfp::Vector2f normal)
{
	Shape shape;
	
	shape.myShapeType=sfp::Shape::Type::Plane;
	shape.myCenter=center;
	shape.myPlaneNormal=normal;
	
	shape.myPoints.push_back(center);
	
	shape.myArea=1;
	shape.myInertiaMoment=1;
	
	shape.Update();
	
	return shape;
}


sfp::Shape sfp::Shape::Circle(const sf::Vector2f& center, float radius)
{
	Shape shape;
	
	shape.myShapeType=sfp::Shape::Type::Circle;
	shape.myCenter=center;
	shape.myCircleRadius=radius;
	
	shape.Update();
	
	return shape;
}




