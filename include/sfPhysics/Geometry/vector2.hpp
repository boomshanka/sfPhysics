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


#ifdef SFML_ENABLED
#include <SFML/System/Vector2.hpp>
#else
#include <sfphysics/SFML_System/Vector2.hpp>
#endif

#include <sfPhysics/Geometry/trigonometry.hpp>
#include <sfPhysics/Geometry/angle.hpp>

#include <ostream>


namespace sfp
{

	template <typename T>
	class vector2 : public sf::Vector2<T>
	{
		public:
			vector2();
			vector2(T x, T y);
			vector2(const vector2<T>& vec);
			vector2(const sf::Vector2<T>& vec);
			template <typename U>
			vector2(const vector2<U>& vec);
			
			T length() const;
			T length(const angle<T>& direction) const;
			T squaredLength() const;
			angle<T> direction() const;
			
			vector2<T>& length(T length);
			vector2<T>& length(T length, const angle<T>& direction);
			vector2<T>& direction(const angle<T>& direction);
			vector2<T>& rotate(const angle<T>&);
			
			vector2<T>& extend(T length);
			vector2<T>& extend(T length, const angle<T>& direction);
			vector2<T>& normalize();
			
			vector2<T> normal() const;
			vector2<T> unit() const;
			vector2<T> rotated(const angle<T>& rotation) const;
	};
	
	// TODO: Why don't use the operators from the base class? should be fine
	template <typename T>
	vector2<T> operator -(const vector2<T>& right);

	template <typename T>
	vector2<T>& operator +=(vector2<T>& left, const vector2<T>& right);
	
	template <typename T>
	vector2<T>& operator -=(vector2<T>& left, const vector2<T>& right);
	
	template <typename T>
	vector2<T> operator +(const vector2<T>& left, const vector2<T>& right);
	
	template <typename T>
	vector2<T> operator -(const vector2<T>& left, const vector2<T>& right);
	
	template <typename T>
	vector2<T> operator *(const vector2<T>& left, T right);
	
	template <typename T>
	vector2<T> operator *(T left, const vector2<T>& right);
	
	template <typename T>
	vector2<T>& operator *=(vector2<T>& left, T right);
	
	template <typename T>
	vector2<T> operator /(const vector2<T>& left, T right);
	
	template <typename T>
	vector2<T>& operator /=(vector2<T>& left, T right);
	
	template <typename T>
	bool operator ==(const vector2<T>& left, const vector2<T>& right);
	
	template <typename T>
	bool operator !=(const vector2<T>& left, const vector2<T>& right);
	
	// new operator
	
	template <typename T>
	vector2<T> operator *(const vector2<T>& left, const vector2<T>& right);
	
	template <typename T>
	vector2<T>& operator *=(vector2<T>& left, const vector2<T>& right);
	
	template <typename T>
	vector2<T> operator /(const vector2<T>& left, const vector2<T>& right);
	
	template <typename T>
	vector2<T>& operator /=(vector2<T>& left, const vector2<T>& right);
	
	
	template <typename T>
	float cross_product(const vector2<T>& left, const vector2<T>& right);
	
	template <typename T>
	float dot_product(const vector2<T>& left, const vector2<T>& right);
	
	// ostream operator for output
	template <typename T>
	std::ostream& operator<<(std::ostream& os, const sf::Vector2<T>& vec); 
	
	
	
	#include <sfPhysics/Geometry/vector2.inl>
	
	
	// Define the most common types
	typedef vector2<int>	vector2i;
	typedef vector2<float>	vector2f;
	typedef vector2<double>	vector2d;
	
	
} // namespace


