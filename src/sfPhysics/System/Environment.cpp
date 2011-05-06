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


#include <sfPhysics/System/Environment.hpp>


#define myObjects ObjectList::myObjectList



sfp::Environment::Environment()
: myGravity(sf::Vector2f(0,10)), myTimefactor(1), myLengthfactor(1), myFrameTime(0), myMoveDrawableEnabled(true)
{
	
}


sfp::Environment::~Environment()
{

}



//--------------------------------------------------------------------------------//



void sfp::Environment::RenderGravity()
{
	for(std::list<sfp::Object*>::iterator it=myObjects.begin(); it!=myObjects.end(); ++it)
	{
		if(!(*it)->IsFixed())
			(*it)->AddVelocity(myGravity*myFrameTime*myTimefactor);
	}
}



void sfp::Environment::MoveObjects()
{
	for(std::list<sfp::Object*>::iterator it=myObjects.begin(); it!=myObjects.end(); ++it)
	{
		if((*it)->IsFixed())
		{
			(*it)->RemoveForces();
		}
		else
		{
			//Move Intersection
			while((*it)->GetIntersection().size()>0)
			{
				(*it)->Move((*it)->GetIntersection().top().first);
				(*it)->GetIntersection().pop();
			}
			
			(*it)->Rotate((*it)->GetRotationVelocity()*myFrameTime*myTimefactor);
			(*it)->Move((*it)->GetVelocity()*myFrameTime*myTimefactor);
		}
	}
	
	if(myMoveDrawableEnabled)
		MoveDrawable();
	
}



#ifdef SFML_ENABLED

void sfp::Environment::MoveDrawable()
{
	for(std::list<sfp::Object*>::iterator it=myObjects.begin(); it!=myObjects.end(); ++it)
	{
		if((*it)->GetDrawable()!=NULL)
		{
			(*it)->GetDrawable()->SetPosition((*it)->GetPosition()*myLengthfactor);
			(*it)->GetDrawable()->SetRotation((*it)->GetRotation());
		}
	}
}

#endif


