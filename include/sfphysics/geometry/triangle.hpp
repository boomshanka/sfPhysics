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


#ifndef SFPHYSICS_TRIANGLE
#define SFPHYSICS_TRIANGLE


namespace sfp
{

	template <typename T>
	class triangle
	{
		public:
			vector2<T> p1;
			vector2<T> p2;
			vector2<T> p3;
			
		public:
			triangle(const vector2<T>& p_1, const vector2<T>& p_2, const vector2<T>& p_3);
			~triangle();
			
			T area() const;
			T perimeter() const;
			
			T inertiaMoment() const;
			vector2<T> center() const;
			
	};
	
	
	#include <sfphysics/geometry/triangle.inl>
	
	
	
} // namespace


#endif // SFPHYSICS_TRIANGLE


