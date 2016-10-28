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


#pragma once

#include <ostream>


namespace sfp
{
	template <typename T>
	class minmax
	{
		public:
			minmax();
			minmax(T value);
			
			minmax<T>& apply(T value);
			minmax<T>& apply(const minmax<T>& values);
			
			T min() const;
			T max() const;
			
			bool contains(T value) const;
			bool intersects(const minmax<T>& mm) const;
			
			bool valid() const;
			
		private:
			T m_min;
			T m_max;
			
			bool m_init;
	};
	
	// ostream operator for output
	template <typename T>
	std::ostream& operator<<(std::ostream& os, const sfp::minmax<T>& mm); 
	
	#include <sfphysics/geometry/minmax.inl>
	
	typedef minmax<unsigned int> minmaxu;
	typedef minmax<int> minmaxi;
	typedef minmax<float> minmaxf;
	typedef minmax<double> minmaxd;
	
	
}

