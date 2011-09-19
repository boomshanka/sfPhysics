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


#ifndef SFPHYSICS_MATH_HPP
#define SFPHYSICS_MATH_HPP


#define _USE_MATH_DEFINES
#include <cmath>



namespace sfp
{

	template <typename T>
	class Math
	{
		public:
			
	};
	
//	template <typename T>
//	Vector2<T> operator *(const Vector2<T>& left, const Vector2<T>& right);
	
	
	#include <sfPhysics/System/Math.inl>
	
} // namespace sfp


#endif // SFPHYSICS_MATH_HPP


