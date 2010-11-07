#include <sfPhysics/PolygonManager.hpp>
#include <sfPhysics/Vector2.hpp>


sfp::PolygonManager::PolygonManager()
{
	myConvexPolygons.push_back(Polygon());
}



void sfp::PolygonManager::AddPoint(const sf::Vector2f& vec)
{
	Polygon::AddPoint(vec);
	
	ComputeConvexPolygons();
}



void sfp::PolygonManager::SetPointPosition(unsigned int index, const sf::Vector2f& vec)
{
	Polygon::SetPointPosition(index, vec);
	
	ComputeConvexPolygons();
}



void sfp::PolygonManager::SetPolygon(const Polygon& polygon) //FIXME zeigt this möglicherweise auf polygon?
{
	Polygon* thispolygon=this;
	*thispolygon=polygon;
	
	ComputeConvexPolygons();
}



void sfp::PolygonManager::ComputeConvexPolygons() //FIXME!!! diese funktion stimmt noch nicht!
{
	myConvexPolygons.clear();
	myConvexPolygons.push_back(Polygon(*this));
	
	/*
	if(Polygon::GetPointCount()>0)
	{
		myConvexPolygons[myConvexPolygons.size()-1].AddPoint(Polygon::GetPoint(0));
		
		
		for(unsigned int i=1;i<Polygon::GetPointCount();++i)
		{
			if(myConvexPolygons[myConvexPolygons.size()-1].GetPointCount()>2)
			{
				float firstangle=sfp::Vector2f(myConvexPolygons[myConvexPolygons.size()-1].GetPoint(i-2)-myConvexPolygons[myConvexPolygons.size()-1].GetPoint(i-3)).GetDirection();
				float secondangle=sfp::Vector2f(myConvexPolygons[myConvexPolygons.size()-1].GetPoint(i-1)-myConvexPolygons[myConvexPolygons.size()-1].GetPoint(i-2)).GetDirection();
				
				
				bool direction=firstangle-secondangle>0 ? true : false;
				
				firstangle=sfp::Vector2f(myConvexPolygons[myConvexPolygons.size()-1].GetPoint(i)-myConvexPolygons[myConvexPolygons.size()-1].GetPoint(i-1)).GetDirection();
				while(firstangle<0)firstangle+=360; //ja(?)
				while(firstangle>360)firstangle-=360; //nein?
				
				if(direction) //Hier stimmt es nicht
				{
					if(secondangle-firstangle>0)
					{
						myConvexPolygons.push_back(Polygon());
						myConvexPolygons[myConvexPolygons.size()-1].AddPoint(Polygon::GetPoint(0));
					}
				}
				else
				{
					if(secondangle-firstangle>0)
					{
						myConvexPolygons.push_back(Polygon());
						myConvexPolygons[myConvexPolygons.size()-1].AddPoint(Polygon::GetPoint(0));
					}
				}
			}
			
			myConvexPolygons[myConvexPolygons.size()-1].AddPoint(Polygon::GetPoint(i));
		}
	}
	std::cerr<<myConvexPolygons.size()<<"\n";*/
}



void sfp::PolygonManager::ComputeArea()
{
	
}



