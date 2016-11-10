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


#ifndef SFPHYSICS_ANGLE
#define SFPHYSICS_ANGLE


namespace sfp
{
	template <typename T>
	class angle
	{
		public:
			angle();
			
			void radians(T val);
			void degrees(T val);
			
			T radians() const;
			T degrees() const;
			
			static angle<T> from_radians(T radians);
			static angle<T> from_degrees(T degrees);
			
		private:
			angle(T degrees);
			
			T m_degrees;
	};
	
	template <typename T>
	angle<T> operator -(const angle<T>& left);
	
	
	template <typename T>
	angle<T> operator +(const angle<T>& left, const angle<T>& right);
	
	template <typename T>
	angle<T> operator -(const angle<T>& left, const angle<T>& right);
	
	template <typename T>
	angle<T> operator *(const angle<T>& left, T right);
	
	template <typename T>
	angle<T> operator *(T left, const angle<T>& right);
	
	template <typename T>
	angle<T> operator /(const angle<T>& left, T right);
	
	template <typename T>
	angle<T> operator +=(angle<T>& left, const angle<T>& right);
	
	template <typename T>
	angle<T> operator -=(angle<T>& left, const angle<T>& right);
	
	template <typename T>
	angle<T> operator *=(const angle<T>& left, T right);
	
	template <typename T>
	angle<T> operator /=(const angle<T>& left, T right);
	
	
	template <typename T>
	angle<T> operator ==(const angle<T>& left, const angle<T>& right);
	
	template <typename T>
	angle<T> operator !=(const angle<T>& left, const angle<T>& right);
	
	template <typename T>
	angle<T> operator <(const angle<T>& left, const angle<T>& right);
	
	template <typename T>
	angle<T> operator >(const angle<T>& left, const angle<T>& right);
	
	
	template <typename T>
	T deg_to_rad(T deg);
	
	template <typename T>
	T rad_to_deg(T rad);
	
	
	#include <sfPhysics/Geometry/angle.inl>
	
	typedef angle<float> anglef;
	typedef angle<double> angled;
	
	
}


#endif // SFPHYSICS_ANGLE


