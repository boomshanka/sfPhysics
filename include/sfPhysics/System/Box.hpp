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


#ifndef SFPHYSICS_RECT_HPP
#define SFPHYSICS_RECT_HPP


#ifdef SFML_ENABLED
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#else
#include <sfPhysics/SFML_System/Vector2.hpp>
#include <sfPhysics/SFML_System/Rect.hpp>
#endif



namespace sfp
{
	
	template <typename T>
	class Box : public sf::Rect<T>
	{
		public:
			Box();
			Box(T left, T top, T width, T height);
			Box(const Vector2<T>& position, const Vector2<T>& size);
			Box(const sf::Rect<T>& rect);
			
			
	};
	
	

	#include <sfPhysics/System/Box.inl>


	// Create typedefs for the most common types
	typedef Box<int>   IntBox;
	typedef Box<float> FloatBox;
	
	
	
} // namespace


#endif // SFPHYSICS_RECT_HPP


