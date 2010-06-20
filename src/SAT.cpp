#include "SAT.hpp"

#include <cmath>


void sfp::SeparatingAxis::ComputeSeperatingAxix(sfp::Object& object)
{
	//pop objects FIXME
	
	switch(object.GetPolygonType())
	{
		case sfp::Circle:
			
			break;
			
		case sfp::Rectangle:
			AddAx(object.ToGlobal(object.GetPoint(0)), object.ToGlobal(object.GetPoint(1)));
			AddAx(object.ToGlobal(object.GetPoint(1)), object.ToGlobal(object.GetPoint(2)));
			break;
			
		case sfp::Line:
			AddAx(object.ToGlobal(object.GetPoint(0)), object.ToGlobal(object.GetPoint(1)));
			break;
		
		default:
			if(object.GetPointCount()>1)
				AddAx(object.ToGlobal(object.GetPoint(object.GetPointCount()-1)),object.ToGlobal(object.GetPoint(0)));
			for(int i=1;i<object.GetPointCount();++i)
			{
				AddAx(object.ToGlobal(object.GetPoint(i-1)), object.ToGlobal(object.GetPoint(i)));
			}
			break;
		
	}
}



void sfp::SeparatingAxis::AddAx(const sf::Vector2f& first, const sf::Vector2f& second)
{
	myAxis.push_back(sf::Vector2f(-(first.y-second.y),first.x-second.x));
	
	//normalize
	float tmp=sqrt(myAxis.front().x * myAxis.front().x + myAxis.front().y * myAxis.front().y);
	myAxis.front()/=tmp;
}




