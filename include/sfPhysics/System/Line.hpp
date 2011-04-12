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


#ifndef SFPHYSICS_LINE_HPP
#define SFPHYSICS_LINE_HPP

#include <sfPhysics/System/Vector2.hpp>

#define _USE_MATH_DEFINES
#include <cmath>



namespace sfp
{

	template <typename T>
	class Line
	{
		public:
			Line();
			Line(const sfp::Vector2<T>&, const sfp::Vector2<T>&);
			
			bool Contains(const sfp::Vector2<T>&);
			bool Intersects(const sfp::Line<T>&);
			bool Intersects(const sfp::Line<T>&, float&);
			
			sfp::Vector2<T> Point;
			sfp::Vector2<T> Direction;
	};
	
	
	
	#include <sfPhysics/System/Line.inl>
	
	
	// Define the most common types
	typedef Line<int>   IntLine;
	typedef Line<float> FloatLine;
	
	
} // namespace


#endif // SFPHYSICS_LINE_HPP


