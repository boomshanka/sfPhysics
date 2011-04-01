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


#include <sfPhysics/System/SAT.hpp>



void sfp::SeparatingAxis::ComputeSeperatingAxix(sfp::Object& object)
{
	//pop objects FIXME
	
	switch(object.GetShapeType())
	{
		case sfp::Shape::Type::Plane:
			
			break;
			
		case sfp::Shape::Type::Rectangle:
			AddAx(object.ToGlobal(object.GetPoint(0)), object.ToGlobal(object.GetPoint(1)));
			AddAx(object.ToGlobal(object.GetPoint(1)), object.ToGlobal(object.GetPoint(2)));
			break;
			
/*		case sfp::Shape::Type::Line:
			AddAx(object.ToGlobal(object.GetPoint(0)), object.ToGlobal(object.GetPoint(1)));
			break;*/
		
		case sfp::Shape::Type::Polygon:
			if(object.GetPointCount()>1)
				AddAx(object.ToGlobal(object.GetPoint(object.GetPointCount()-1)),object.ToGlobal(object.GetPoint(0)));
			for(int i=1;i<object.GetPointCount();++i)
			{
				AddAx(object.ToGlobal(object.GetPoint(i-1)), object.ToGlobal(object.GetPoint(i)));
			}
			break;
		
		default:
			break;
			
	}
}



void sfp::SeparatingAxis::AddAx(const sf::Vector2f& first, const sf::Vector2f& second)
{
	myAxis.push_back(sf::Vector2f(-(first.y-second.y),first.x-second.x));
	
	//normalize
//	float tmp=sqrt(myAxis.front().x * myAxis.front().x + myAxis.front().y * myAxis.front().y);
//	myAxis.front()/=tmp;
}




