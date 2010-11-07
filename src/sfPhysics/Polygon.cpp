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
	
}




sfp::Polygon sfp::Polygon::Rectangle()
{
	Polygon polygon;
	
	return polygon;
}


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
	
	return polygon;
}




