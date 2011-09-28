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


#ifndef SFPHYSICS_ELECTRICITY_HPP
#define SFPHYSICS_ELECTRICITY_HPP


namespace sfp
{
	class Electricity
	{
		private:
			float myVoltage;
			float myAmperage;
			
		public:
			Electricity(float voltage = 0, float amperage = 0) : myVoltage(voltage), myAmperage(amperage) {}
			~Electricity() {}
			
			float GetVoltage() {return myVoltage;}
			float GetAmperage() {return myAmperage;}
			
			void SetVoltage(float voltage) {myVoltage = voltage;}
			void SetAmperage(float amperage) {myAmperage = amperage;}
	};
	
	
} // namespace sfp



#endif // SFPHYSICS_ELECTIRCITY_HPP


