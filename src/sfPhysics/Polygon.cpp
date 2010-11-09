#include <sfPhysics/Polygon.hpp>

#include <cmath>



sfp::Polygon::Polygon()
:myPolygonType(Shape), myCircleRadius(0)
{

}



sfp::Polygon::Polygon(const Polygon& polygon)
:myPolygonType(polygon.myPolygonType),
myPoints(polygon.myPoints),
myCircleRadius(polygon.myCircleRadius),
myCenter(polygon.myCenter), myArea(polygon.myArea), myInertiaMoment(polygon.myInertiaMoment)
{
	
}




void sfp::Polygon::ComputeArea()
{
	myArea=0;
	myInertiaMoment=0;
	
	switch(myPolygonType)
	{
		case Shape:
			ComputeShapeArea();
			break;
		
		case 1:
			ComputeShapeArea();
			break;
		
		case 4:
			ComputeCircleArea();
			break;
		
		default:
			break;
	}
}


void sfp::Polygon::ComputeShapeArea()
{
	myCenter=sf::Vector2f(0,0);
	
	for(unsigned int i=2; i<myPoints.size();++i)
	{
		sfp::Vector2f line=myPoints[0]-myPoints[i-1];
		float a=line.GetForce();
		line=myPoints[i-1]-myPoints[i];
		float b=line.GetForce();
		line=myPoints[i]-myPoints[0];
		float c=line.GetForce();
		
		float area=0.25*std::sqrt((a+b+c)*(a+b-c)*(b+c-a)*(c+a-b));
		sf::Vector2f center((myPoints[0]+myPoints[i-1]+myPoints[i])/3.f);
		
		sfp::Vector2f diff(center-myCenter);
		diff*=(area/(area+myArea));
		myCenter+=diff;
		myArea+=area;
	}
}


void sfp::Polygon::ComputeCircleArea()
{
	myArea = M_PI * myCircleRadius*myCircleRadius;
	myInertiaMoment = 0.5 * myArea * myCircleRadius*myCircleRadius; //FIXME *myArea richtig??
}




sfp::Polygon sfp::Polygon::Rectangle()
{
	Polygon polygon;
	
	return polygon;
}//FIXME jeweils ein ComputeArea();


sfp::Polygon sfp::Polygon::Line()
{
	Polygon polygon;
	
	return polygon;
}


sfp::Polygon sfp::Polygon::Plane()
{
	Polygon polygon;
	
	return polygon;
}


sfp::Polygon sfp::Polygon::Circle(const sf::Vector2f& center, float radius)
{
	Polygon polygon;
	
	polygon.myPolygonType=sfp::Circle;
	polygon.myCenter=center;
	polygon.myCircleRadius=radius;
	
	polygon.ComputeArea();
	
	return polygon;
}




