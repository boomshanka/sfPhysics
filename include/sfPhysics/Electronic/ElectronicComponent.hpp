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


#ifndef SFPHYSICS_ELECTRONICCOMPONENT_HPP
#define SFPHYSICS_ELECTRONICCOMPONENT_HPP

#include <sfPhysics/Electronic/Electricity.hpp>
#include <sfPhysics/Electronic/Conductor.hpp>
#include <sfPhysics/Settings.hpp>

#include <vector>
#include <cstddef>
#include <utility>


namespace sfp
{
	class Conductor;
	
	class ElectronicComponent
	{
		public:
			enum Type
			{
				Component = 0,
				Source = 1,
				Ground = 2
			};
			
		protected:
			std::vector<Electricity> myInputPorts;
			std::vector<std::pair<Electricity, Conductor*> > myOutputPorts;
			
			float myResistance;
			Type myType;
			
		public:
			ElectronicComponent() {myType = Component;}
			virtual ~ElectronicComponent() {}
			
			virtual bool SetPortInput(std::size_t port, const Electricity& electricity);
			virtual void DeactivatePortInput(std::size_t port);
			
			virtual Electricity GetPortOutput(std::size_t port);
			virtual void Update();
			
			//virtual std::queue<std::pair<std::size_t, Electricity> > GetReaction(std::size_t port, const Electricity& electricity);
			
			std::size_t GetInputPortCount() {return myInputPorts.size();}
			std::size_t GetOutputPortCount() {return myOutputPorts.size();}
			
			float GetResistance() {return myResistance;}
			Type GetType() {return myType;}
	};


} // namespace sfp



#endif // SFPHYSICS_ELECTRONICCOMPONENT_HPP


