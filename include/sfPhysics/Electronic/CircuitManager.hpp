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


#ifndef SFPHYSICS_CIRCUITMANAGER_HPP
#define SFPHYSICS_CIRCUITMANAGER_HPP

#include <sfPhysics/Electronic/ElectronicComponent.hpp>

#include <list>
#include <cstddef>


namespace sfp
{
	class CircuitManager
	{
		private:
			std::list<sfp::ElectronicComponent*> myComponents;
			std::list<std::list<sfp::ElectronicComponent*>::iterator> mySources;
			
		public:
			CircuitManager();
			~CircuitManager();
			
			void Update();
			void FindVoltageSources();
			
			// list functions
			void AddComponent(sfp::ElectronicComponent* object);
			
			void EraseComponent(std::list<sfp::ElectronicComponent*>::iterator& it);
			void RemoveComponent(sfp::ElectronicComponent* object);
			
			std::size_t GetComponentCount() const;
			
			//FIXME iterator
			
	};
	
	
} // namespace sfp



#endif // SFPHYSICS_CIRCUITMANAGER_HPP


