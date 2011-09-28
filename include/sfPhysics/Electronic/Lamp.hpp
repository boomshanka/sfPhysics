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


#ifndef SFPHYSICS_LAMP_HPP
#define SFPHYSICS_LAMP_HPP

#include <sfPhysics/Electronic/ElectronicComponent.hpp>


namespace sfp
{
	class Lamp : virtual public ElectronicComponent
	{
		private:
			float myVoltage;
			
			float myBrightness;
			
		public:
			Lamp(float voltage, float resistance);
			~Lamp();
			
			bool SetPortInput(std::size_t port, const Electricity& electricity);
			void DeactivatePortInput(std::size_t port);
			
			Electricity GetPortOutput(std::size_t port);
			void Update();
			
	};
	
	
} // namespace sfp



#endif // SFPHYSICS_LAMP_HPP


