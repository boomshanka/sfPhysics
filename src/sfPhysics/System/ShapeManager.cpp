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


#include <sfPhysics/System/ShapeManager.hpp>
#include <sfPhysics/System/Vector2.hpp>



sfp::ShapeManager::ShapeManager()
:myIsUpdated(true)
{
	myConvexShapes.push_back(Shape());//FIXME
}



void sfp::ShapeManager::AddPoint(const sf::Vector2f& vec)
{
	Shape::AddPoint(vec);
	
	myIsUpdated = false;
}



void sfp::ShapeManager::SetPoint(size_t index, const sf::Vector2f& vec)
{
	Shape::SetPoint(index, vec);
	
	myIsUpdated = false;
}



void sfp::ShapeManager::SetShape(const Shape& shape)
{
	Shape* thisshape = this;
	*thisshape = shape;
	
	myConvexShapes.clear();
	myConvexShapes.push_back(Shape(*this));
	
	Update();
}




void sfp::ShapeManager::Update()
{
	ComputeConvexShapes();
	ComputeArea();
	ComputeBox();
	
	myIsUpdated = true;
}



void sfp::ShapeManager::ComputeConvexShapes() //FIXME Shape::Update bei jedem Shapetype aufrufen. Polygone testen, ob sie konvex/konkav sind und zerlegen.
{
	Shape::type.myShapeType = Shape::Type::Nothing;
	Shape::myPoints.clear();
	
	for(size_t i = 0; i < myConvexShapes.size(); ++i)
	{
		switch(myConvexShapes[i].GetShapeType())
		{
			case Shape::Type::Polygon:
				if(Shape::type.myShapeType==Shape::Type::Nothing || Shape::type.myShapeType==Shape::Type::Rectangle)
					Shape::type.myShapeType = Shape::Type::Polygon;
				else if(Shape::type.myShapeType!=Shape::Type::Polygon)
					Shape::type.myShapeType = Shape::Type::Unknown;
				
				//FIXME in konvexe trennen und alle shapes updaten!
				myConvexShapes[i].Update();
				break;
			
			case Shape::Type::Rectangle:
				if(Shape::type.myShapeType==Shape::Type::Nothing)
					Shape::type.myShapeType = Shape::Type::Rectangle;
				else if(Shape::type.myShapeType!=Shape::Type::Rectangle && Shape::type.myShapeType!=Shape::Type::Polygon)
					Shape::type.myShapeType = Shape::Type::Unknown;
				
				myConvexShapes[i].Update();
				break;
			
			case Shape::Type::Circle:
				if(Shape::type.myShapeType==Shape::Type::Nothing)
					Shape::type.myShapeType = Shape::Type::Circle;
				else if(Shape::type.myShapeType!=Shape::Type::Circle)
					Shape::type.myShapeType = Shape::Type::Unknown;
				
				myConvexShapes[i].Update();
				break;
			
			case Shape::Type::Plane:
				if(Shape::type.myShapeType==Shape::Type::Nothing)
					Shape::type.myShapeType = Shape::Type::Plane;
				else if(Shape::type.myShapeType!=Shape::Type::Plane)
					Shape::type.myShapeType = Shape::Type::Unknown;
				
				myConvexShapes[i].Update();
				break;
				
			default:
				myConvexShapes.erase(myConvexShapes.begin()+i);
				--i;
				break;
				
		}
	}
	
	
	
	/*
	if(Shape::GetPointCount()>0)
	{
		myConvexShapes[myConvexShapes.size()-1].AddPoint(Shape::GetPoint(0));
		
		
		for(size_t i=1;i<Shape::GetPointCount();++i)
		{
			if(myConvexShapes[myConvexShapes.size()-1].GetPointCount()>2)
			{
				float firstangle=sfp::Vector2f(myConvexShapes[myConvexShapes.size()-1].GetPoint(i-2)-myConvexShapes[myConvexShapes.size()-1].GetPoint(i-3)).GetDirection();
				float secondangle=sfp::Vector2f(myConvexShapes[myConvexShapes.size()-1].GetPoint(i-1)-myConvexShapes[myConvexShapes.size()-1].GetPoint(i-2)).GetDirection();
				
				
				bool direction=firstangle-secondangle>0 ? true : false;
				
				firstangle=sfp::Vector2f(myConvexShapes[myConvexShapes.size()-1].GetPoint(i)-myConvexShapes[myConvexShapes.size()-1].GetPoint(i-1)).GetDirection();
				while(firstangle<0)firstangle+=360; //ja(?)
				while(firstangle>360)firstangle-=360; //nein?
				
				if(direction) //Hier stimmt es nicht
				{
					if(secondangle-firstangle>0)
					{
						myConvexShapes.push_back(Shape());
						myConvexShapes[myConvexShapes.size()-1].AddPoint(Shape::GetPoint(0));
					}
				}
				else
				{
					if(secondangle-firstangle>0)
					{
						myConvexShapes.push_back(Shape());
						myConvexShapes[myConvexShapes.size()-1].AddPoint(Shape::GetPoint(0));
					}
				}
			}
			
			myConvexShapes[myConvexShapes.size()-1].AddPoint(Shape::GetPoint(i));
		}
	}
	std::cerr<<myConvexShapes.size()<<"\n";*/
}


void sfp::ShapeManager::ComputeArea()
{
	Shape::myCenter=sf::Vector2f(0,0);
	Shape::myArea=0;
	Shape::myInertiaMoment=0;
	
	for(size_t i = 0; i < myConvexShapes.size(); ++i)
	{
		if(myConvexShapes[i].GetShapeType()!=Shape::Type::Plane)
		{
			//Schwerpunkte addieren
			sfp::Vector2f diff(myConvexShapes[i].GetShapeCenter()-myCenter);
			diff*=(myConvexShapes[i].GetShapeArea()/(myConvexShapes[i].GetShapeArea()+myArea));
			myCenter+=diff;
		
			//Trägheitsmoment verschieben
			myInertiaMoment += myArea * std::pow(diff.GetForce(),2);
			//Trägheitsmoment von Objekt verschieben & addieren
			diff=(myConvexShapes[i].GetShapeCenter()-(myCenter-diff))-diff;
			myInertiaMoment += myConvexShapes[i].GetShapeInertiaMoment() + myConvexShapes[i].GetShapeArea() * std::pow(diff.GetForce(),2);
		
			//Fläche addieren
			myArea+=myConvexShapes[i].GetShapeArea();
		}
	}
}


void sfp::ShapeManager::ComputeBox()
{
	if(Shape::type.myShapeType==sfp::Shape::Type::Polygon && Shape::myPoints.size()!=0) //FIXME switch
	{
		myBox.Left=myBox.Width=Shape::myPoints[0].x;
		myBox.Top=myBox.Height=Shape::myPoints[0].y;
		
		for(size_t i=1; i<Shape::myPoints.size(); ++i)
		{
			if(myBox.Left>Shape::myPoints[i].x)
				myBox.Left=Shape::myPoints[i].x;
			else if(myBox.Width<Shape::myPoints[i].x)
				myBox.Width=Shape::myPoints[i].x;
			
			if(myBox.Top>Shape::myPoints[i].y)
				myBox.Top=Shape::myPoints[i].y;
			else if(myBox.Height<Shape::myPoints[i].y)
				myBox.Height=Shape::myPoints[i].y;
			
		}
	}
	else if(Shape::type.myShapeType==sfp::Shape::Type::Circle)
	{
		myBox.Left = Shape::myCenter.x - Shape::myCircleRadius;
		myBox.Top = Shape::myCenter.y - Shape::myCircleRadius;
		myBox.Width = myBox.Height = Shape::myCircleRadius * 2.f;
	}
	else if(Shape::type.myShapeType==sfp::Shape::Type::Rectangle)
	{
	
	}
	switch(Shape::type.myShapeType)
	{
		default:
		break;
	}
}



