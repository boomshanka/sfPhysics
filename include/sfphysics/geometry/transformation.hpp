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

#include <sfphysics/geometry/angle.hpp>
#include <sfphysics/geometry/vector2.hpp>
#include <sfphysics/geometry/trigonometry.hpp>

#include <array>

#ifdef SFML_ENABLED
#include <SFML/Graphics/Transform.hpp>
#endif


namespace sfp
{
	
	template <typename T>
	class transformation
	{
		public:
			transformation();
			transformation(T a00, T a01, T a02, T a10, T a11, T a12, T a20, T a21, T a22);
			transformation(const transformation<T>&);
			
			transformation<T>& translate(const vector2<T>& offset);
			transformation<T>& rotate(const angle<T>& angle);
			transformation<T>& rotate(const angle<T>& angle, const vector2<T>& center);
			transformation<T>& scale(const vector2<T>& scale);
			
			transformation<T> get_inverse() const;
			transformation<T>& invert();
			transformation<T>& clear();
			
			transformation<T>& combine(const transformation<T>& right);
			
			vector2<T> transform(const vector2<T>&) const;
			// more transform functions
			
			transformation<T>&	operator =(const transformation& right);
			bool operator ==(const transformation& right) const;
			
			#ifdef SFML_ENABLED
			operator sf::Transform() const;
			#endif
			
		private:
			std::array<std::array<T, 3>, 3> m_matrix;
	};
	
	
	template <typename T>
	vector2<T>			operator *(const transformation<T>& left, const vector2<T>& right);
	
	template <typename T>
	transformation<T>	operator *(const transformation<T>& left, const transformation<T>& right);
	
	template <typename T>
	transformation<T>&	operator *=(transformation<T>& left, const transformation<T>& right);
	
	
	#include <sfphysics/geometry/transformation.inl>
	
	
	// Define the most common types
	typedef transformation<int>		transformi;
	typedef transformation<float>	transformf;
	typedef transformation<double>	transformd;
	
	
} // namespace


