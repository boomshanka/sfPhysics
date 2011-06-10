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


#include <sfPhysics/System/CollisionManager.hpp>


#define myObjects ObjectList::myObjectList



sfp::CollisionManager::CollisionManager()
{

}


sfp::CollisionManager::~CollisionManager()
{

}



void sfp::CollisionManager::UpdateCollisions()
{
	for(std::list<sfp::Object*>::iterator it = myObjects.begin(); it != myObjects.end(); ++it)
	{
		std::list<sfp::Object*>::iterator it2 = it;
		for(++it2; it2 != myObjects.end(); ++it2)
		{
			sfp::CollisionEvent event(*it, *it2);
			while(myCollision.GetCollisions(event))
			{
				switch(event.CollisionType)
				{
					case sfp::NoCollision:
						OnNoCollision(event);
					break;
				
					case sfp::BoundingBoxCollision:
						OnBoundingBoxCollision(event);
					break;
				
					case sfp::PreciseCollision:
						OnPreciseCollision(event);
					break;
				}
			}
		}
	}
}



void sfp::CollisionManager::CollisionResponse(sfp::CollisionEvent& event)
{

}



void sfp::CollisionManager::OnPreciseCollision(sfp::CollisionEvent& event)
{
	
	CollisionResponse(event);
}



