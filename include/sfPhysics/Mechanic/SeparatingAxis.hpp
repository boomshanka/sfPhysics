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


#ifndef SFPHYSICS_SEPARATINGAXIS_HPP
#define SFPHYSICS_SEPARATINGAXIS_HPP

#include <vector>

#include <sfPhysics/System/Vector2.hpp>

#include <cstddef>



namespace sfp
{
	class SeparatingAxis
	{
		private:
			mutable std::vector<sfp::Vector2f> myAxis;
			
			mutable float myRotation;
			
		public:
			SeparatingAxis();
			SeparatingAxis(const std::vector<sf::Vector2f>&);
			
			~SeparatingAxis() {}
			
			void Clear() {myAxis.clear();}
			
			void ComputeSeparatingAxis(const std::vector<sf::Vector2f>&);
			void AddAx(const sfp::Vector2f& ax) {myAxis.push_back(ax);}
			
			void UpdateRotation(float) const;
			float GetRotation() const {return myRotation;}
			
			size_t GetAxisCount() const {return myAxis.size();}
			const sfp::Vector2f& GetAx(size_t i) const {return myAxis[i];}
			
	};
	
} // namespace


#endif // SFPHYSICS_SEPARATINGAXIS_HPP



