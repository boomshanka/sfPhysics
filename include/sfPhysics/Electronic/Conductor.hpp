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


#ifndef SFPHYSICS_CONDUCTOR_HPP
#define SFPHYSICS_CONDUCTOR_HPP

#include <sfPhysics/Electronic/ElectronicComponent.hpp>
#include <sfPhysics/Electronic/Electricity.hpp>

#include <vector>
#include <cstddef>


namespace sfp
{
	class ElectronicComponent;
	
	class Conductor
	{
		private:
			std::vector<ElectronicComponent*> myOutputComponents;
			
		public:
			Conductor();
			~Conductor();
			
			void AddOutputComponent(ElectronicComponent& component);
			void AddElectricity(const Electricity& electricitiy);
			
			std::size_t GetOutputComponentsCount() {return myOutputComponents.size();}
			ElectronicComponent& GetOutputComponent(std::size_t component) {return *myOutputComponents[component];}
			
			
	};
	
	
} // namespace sfp



#endif // SFPHYSICS_CONDUCTOR_HPP


