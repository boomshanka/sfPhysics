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


#include <sfPhysics/Electronic/CircuitManager.hpp>



sfp::CircuitManager::CircuitManager()
{

}


sfp::CircuitManager::~CircuitManager()
{

}



void sfp::CircuitManager::Update()
{

}



void sfp::CircuitManager::FindVoltageSources()
{
	mySources.clear();
	
	for(std::list<ElectronicComponent*>::iterator it = myComponents.begin(); it != myComponents.end(); ++it)
	{
		if((*it)->GetType() == sfp::ElectronicComponent::Source)
		{
			mySources.push_back(it);
		}
	}
}



void sfp::CircuitManager::AddComponent(sfp::ElectronicComponent* object)
{
	myComponents.push_back(object);
	FindVoltageSources();
}


void sfp::CircuitManager::EraseComponent(std::list<sfp::ElectronicComponent*>::iterator& it)
{
	myComponents.erase(it);
	FindVoltageSources();
}


void sfp::CircuitManager::RemoveComponent(sfp::ElectronicComponent* object)
{
	myComponents.remove(object);
	FindVoltageSources();
}


std::size_t sfp::CircuitManager::GetComponentCount() const
{
	return myComponents.size();
}


