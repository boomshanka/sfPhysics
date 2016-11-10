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

#include <sfPhysics/Geometry/vector2.hpp>


namespace sfp
{

	template <typename T>
	class line
	{
		public:
			line(bool inf = false);
			line(const sfp::vector2<T>& first, const sfp::vector2<T>& second, bool inf = false);
			
			bool contains(const sfp::vector2<T>& point, float& relative_position = 0);
			bool intersects(const sfp::line<T>& line, float& relative_position = 0);
			
			sfp::vector2<T> first_point;
			sfp::vector2<T> second_point;
			
			bool infinite;
	};
	
	
	#include <sfPhysics/Geometry/line.inl>
	
	
	// Define the most common types
	typedef line<int>   	linei;
	typedef line<float> 	linef;
	typedef line<double>	lined;
	
	
} // namespace


