#include <sfPhysics/Physicable.hpp>

#include <queue>



sfp::Physicable::Physicable()
:myRotationSpeed(0), myArea(10),
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
	if(restitution<0 || restitution>1)
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




sf::Vector2f sfp::Physicable::ComputeArea(const std::vector<Polygon>& polygons) //FIXME UNBEDiNGT TESTEN!
{
	myArea=0;
	
	std::pair<sf::Vector2f, float> pair=ComputeArea(polygons[0].myPoints);
	
	for(unsigned int i=1; i<polygons.size(); ++i)
	{
		std::pair<sf::Vector2f, float> temp=ComputeArea(polygons[i].myPoints);
		
		sf::Vector2f diff(temp.first-pair.first);
		diff*=(temp.second/(temp.second+pair.second));
		pair.first+=diff;
		pair.second+=temp.second;
	}
	
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




void sfp::Physicable::Force(sf::Vector2f position, float direction, float force)
{

}


void sfp::Physicable::Force(sf::Vector2f position, sfp::Vector2f force)
{
	
}




