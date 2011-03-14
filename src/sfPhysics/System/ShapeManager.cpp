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
{
	myConvexShapes.push_back(Shape());//FIXME
}



void sfp::ShapeManager::AddPoint(const sf::Vector2f& vec)
{
	Shape::AddPoint(vec);
	
	ComputeConvexShapes();
	ComputeArea();
}



void sfp::ShapeManager::SetPointPosition(unsigned int index, const sf::Vector2f& vec)
{
	Shape::SetPointPosition(index, vec);
	
	ComputeConvexShapes();
	ComputeArea();
}



void sfp::ShapeManager::SetShape(const Shape& shape) //FIXME zeigt this möglicherweise auf Shape?
{
	Shape* thisshape=this;
	*thisshape=shape;
	
	ComputeConvexShapes();
	ComputeArea();
}



void sfp::ShapeManager::ComputeConvexShapes() //FIXME!!! diese funktion stimmt noch nicht!
{//FIXME shapetypen prüfen und ggf gleich in liste pushen (plane, circle usw)
	myConvexShapes.clear();
	myConvexShapes.push_back(Shape(*this));
	
	/*
	if(Shape::GetPointCount()>0)
	{
		myConvexShapes[myConvexShapes.size()-1].AddPoint(Shape::GetPoint(0));
		
		
		for(unsigned int i=1;i<Shape::GetPointCount();++i)
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
	
	for(unsigned int i=0; i<myConvexShapes.size(); ++i)
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



