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


namespace sfp
{

	template <typename T>
	class box
	{
		public:
			box();
			box(const vector2<T>& lower, const vector2<T>& upper);
			box(const box<T>& b);
			template <typename U>
			box(const box<U>& b);
			
			bool contains(const vector2<T>& point) const;
			bool intersects(const box<T>& bx) const;
			bool intersects(const box<T>& bx, box<T>& intersection) const;
			
			const vector2<T>& lowerPoint() const;
			const vector2<T>& upperPoint() const;
			
		private:
			vector2<T> m_lowerPoint;
			vector2<T> m_upperPoint;
		
	};	
	
	
	#include <sfPhysics/Geometry/box.inl>
	
	
	typedef box<int>	boxi;
	typedef box<float>	boxf;
	typedef box<double>	boxd;
	
	
}

