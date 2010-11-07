#include <sfPhysics/Physicable.hpp>

#include <queue>
#include <cmath>



sfp::Physicable::Physicable()
:myRotationSpeed(0), myArea(10), myInertiaMoment(10),
myMass(10), myDensity(1), myRestitution(0), myFriction(0)
{

}



//   -----   Getter & Setter   -----   //
bool sfp::Physicable::SetMass(float mass)
{
	if(mass<=0)
		return false;
	
	myMass=mass;
	myDensity=myMass/myArea;
	return true;
}


bool sfp::Physicable::SetDensity(float density)
{
	if(density<=0)
		return false;
	
	myDensity=density;
	myMass=myDensity*myArea;
	return true;
}


bool sfp::Physicable::SetArea(float area)
{
	if(area<=0)
		return false;
	
	myArea=area;
	myMass=myDensity*myArea;
	return true;
}


bool sfp::Physicable::SetRestitution(float restitution)
{
	if(restitution<0 || restitution>1) //FIXME größere werte zulassen?
		return false;
	
	myRestitution=restitution;
	return true;
}


bool sfp::Physicable::SetFriction(float friction)
{
	if(friction<0 || friction>1) //FIXME größere werte zulassen?
		return false;
	
	myFriction=friction;
	return true;
}




sf::Vector2f sfp::Physicable::ComputeArea(std::vector<sfp::Polygon>& polygons) //FIXME nicht getestet. Diese Funktionen müssen teils nach Polygon & PolygonManager
{
	myArea=0;
	myInertiaMoment=10; //Falls nicht berechnet werden kann.
	
	if(polygons.size()==0) return sf::Vector2f(0,0);
	
	std::pair<sf::Vector2f, float> pair;
//	float pairMoment;
	
	switch(polygons[0].GetPolygonType())
	{
		case Shape:
			pair=ComputeArea(polygons[0].myPoints);
//			polygons[0].SetPolygonCenter(pair.first);
//			pairMoment=10; //FIXME
			break;
		
		case Circle:
			pair=ComputeArea(polygons[0].GetPolygonCenter(),polygons[0].GetCircleRadius());
//			pairMoment=0.5*myMass*polygons[0].GetCircleRadius();
			break;
		
		default:
			return sf::Vector2f(0,0);
			break;
	}
	
	for(unsigned int i=1; i<polygons.size(); ++i)
	{
		std::pair<sf::Vector2f, float> temp;
//		float tempMoment;
		
		switch(polygons[i].GetPolygonType())
		{
			case Shape:
			case Rectangle:
				temp=ComputeArea(polygons[i].myPoints);
//				polygons[i].SetPolygonCenter(pair.first);
//				tempMoment=10; //FIXME
				break;
			
			case Circle:
				temp=ComputeArea(polygons[i].GetPolygonCenter(),polygons[i].GetCircleRadius());
				//Berechne den Trägheitsmoment
//				tempMoment=0.5*myMass*polygons[i].GetCircleRadius();
				break;
			
			default:
				return sf::Vector2f(0,0);
				break;
		}
		
		//Schwerpunkte addieren
		sfp::Vector2f diff(temp.first-pair.first);
		diff*=(temp.second/(temp.second+pair.second));
		//Trägheitsmoment Verschieben
//		pairMoment=pairMoment+pair.second*(diff.GetForce()*diff.GetForce())
		//
		pair.first+=diff;
		pair.second+=temp.second;
		//Trägheitsmoment Verschieben & addieren
//		sfp::Vector2f centerdiff(temp.first-pair.first);
//		pairMoment
		//
	}
	
//	myInertiaMoment=pairMoment;
	
	return pair.first;
}



std::pair<sf::Vector2f, float> sfp::Physicable::ComputeArea(const std::vector<sf::Vector2f>& points)
{
	std::queue<std::pair<sf::Vector2f, float> > center;
	for(unsigned int i=2;i<points.size();++i)
	{
		sfp::Vector2f line=points[0]-points[i-1];
		float a=line.GetForce();
		line=points[i-1]-points[i];
		float b=line.GetForce();
		line=points[i]-points[0];
		float c=line.GetForce();
		
		float area=0.25*std::sqrt((a+b+c)*(a+b-c)*(b+c-a)*(c+a-b));
		center.push(std::make_pair(sf::Vector2f((points[0]+points[i-1]+points[i])/3.f),area));
		myArea+=area;
	}
	
	std::pair<sf::Vector2f, float> pair=center.front();
	center.pop();
	while(0<center.size())
	{
		sf::Vector2f diff(center.front().first-pair.first);
		diff*=(center.front().second/(center.front().second+pair.second));
		pair.first+=diff;
		pair.second+=center.front().second;
		center.pop();
	}
	
	return pair; // return the center of gravity
}



std::pair<sf::Vector2f, float> sfp::Physicable::ComputeArea(const sf::Vector2f& center, float radius)
{
	float area= M_PI * radius*radius;
	
	myArea+=area;
	return std::make_pair(center, area);
}




void sfp::Physicable::Force(const sf::Vector2f& position, float direction, float force)
{

}


void sfp::Physicable::Force(const sf::Vector2f& position, const sfp::Vector2f& force)
{
	
}




