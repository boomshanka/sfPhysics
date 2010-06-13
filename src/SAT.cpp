#include "SAT.hpp"

#include <cmath>


void sfp::SeparatingAxis::ComputeSeperatingAxix(sfp::Object& object)
{
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
			for(int i=1;i<object.GetPointCount();++i)
			{
				AddAx(object.ToGlobal(object.GetPoint(i-1)), object.ToGlobal(object.GetPoint(i)));
			}
			break;
		
	}
}




