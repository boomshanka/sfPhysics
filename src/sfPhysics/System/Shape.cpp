#include <sfPhysics/System/Shape.hpp>



sfp::Shape::Shape()
:myShapeType(Polygon), myCircleRadius(0)
{

}



sfp::Shape::Shape(const Shape& shape)
:myShapeType(shape.myShapeType),
myPoints(shape.myPoints),
myCircleRadius(shape.myCircleRadius),
myCenter(shape.myCenter), myArea(shape.myArea), myInertiaMoment(shape.myInertiaMoment)
{
	
}




void sfp::Shape::ComputeArea() //FIXME warum zahlen?
{
	myArea=0;
	myInertiaMoment=0;
	
	switch(myShapeType)
	{
		case Polygon:
			ComputePolygonArea();
			break;
		
		case 1:
			ComputePolygonArea();
			break;
		
		case 4:
			ComputeCircleArea();
			break;
		
		default:
			break;
	}
}


void sfp::Shape::ComputePolygonArea()
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


void sfp::Shape::ComputeCircleArea()
{
	myArea = M_PI * myCircleRadius*myCircleRadius;
	myInertiaMoment = 0.5 * myArea * myCircleRadius*myCircleRadius; //Später wird Dichte dazu multipliziert (Fläche*Dichte=Gewicht)
	//std::cerr<<myInertiaMoment<<";\n"; FIXME
}




sfp::Shape sfp::Shape::Rectangle()
{
	Shape shape;
	
	return shape;
}//FIXME jeweils ein ComputeArea();


sfp::Shape sfp::Shape::Line()
{
	Shape shape;
	
	return shape;
}


sfp::Shape sfp::Shape::Plane(const sf::Vector2f& center, float angle)
{
	Shape shape;
	
	shape.myShapeType=sfp::Plane;
	shape.myCenter=center;
	shape.myCircleRadius=angle;
	
	shape.myArea=1;
	
	return shape;
}


sfp::Shape sfp::Shape::Circle(const sf::Vector2f& center, float radius)
{
	Shape shape;
	
	shape.myShapeType=sfp::Circle;
	shape.myCenter=center;
	shape.myCircleRadius=radius;
	
	shape.ComputeArea();
	
	return shape;
}




