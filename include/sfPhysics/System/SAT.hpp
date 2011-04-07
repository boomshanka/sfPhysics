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


#ifndef SFPHYSICS_SAT_HPP
#define SFPHYSICS_SAT_HPP


#include <sfPhysics/System/Objects.hpp>

#include <queue>



namespace sfp
{
	class Object;

	class SAT
	{
		private:
			std::vector<sf::Vector2f> myAxis;
		public:
			SAT() {}
			SAT(sfp::Object& object) {ComputeSeperatingAxix(object);}
			
			~SAT() {}
			
			void ComputeSeperatingAxix(sfp::Object&);
			
			int GetAxisCount() {return myAxis.size();}
			sf::Vector2f GetAx(int index) {return myAxis[index];}
			
		protected:
			void AddAx(const sf::Vector2f&, const sf::Vector2f&);
	};

}


#endif // SFPHYSICS_SAT_HPP


