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



sfp::Environment::Environment()
: myGravity(sf::Vector2f(0,10)), myTimefactor(1), myLengthfactor(1), myFrameTime(0)
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
			(*it)->AddSpeed(myGravity*myFrameTime);
	}
}



void sfp::Environment::MoveObjects(bool moovedrawables)
{
	for(std::list<sfp::Object*>::iterator it=myObjects.begin(); it!=myObjects.end(); ++it)
	{
		if((*it)->IsFixed())
		{
			(*it)->RemoveForces();
		}
		else
		{
			(*it)->Rotate((*it)->GetRotationSpeed()*myFrameTime*myTimefactor);
			(*it)->Move((*it)->GetSpeed()*myFrameTime*myTimefactor);
		}
	}
	
	if(moovedrawables)
		MoveDrawables();
	
}



#ifdef SFML_ENABLED

void sfp::Environment::MoveDrawables()
{
	for(std::list<sfp::Object*>::iterator it=myObjects.begin(); it!=myObjects.end(); ++it)
	{
		if((*it)->GetDrawable()!=NULL)
		{
			(*it)->GetDrawable()->SetPosition((*it)->GetPosition()*myLengthfactor);
			(*it)->GetDrawable()->SetRotation(-(*it)->GetRotation());
		}
	}
}

#endif


