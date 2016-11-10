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



template<typename T>
sfp::angle<T>::angle()
: m_degrees(0)
{

}

template<typename T>
sfp::angle<T>::angle(T degrees)
: m_degrees(degrees)
{

}



template<typename T>
void sfp::angle<T>::radians(T val)
{
	m_degrees = rad_to_deg<T>(val);
}

template<typename T>
void sfp::angle<T>::degrees(T val)
{
	m_degrees = val;
}


template<typename T>
T sfp::angle<T>::degrees() const
{
	return m_degrees;
}

template<typename T>
T sfp::angle<T>::radians() const
{
	return deg_to_rad<T>(m_degrees);
}


template<typename T>
sfp::angle<T> sfp::angle<T>::from_radians(T radians)
{
	return angle<T>(rad_to_deg(radians));
}

template<typename T>
sfp::angle<T> sfp::angle<T>::from_degrees(T degrees)
{
	return angle<T>(degrees);
}


// operatoren

template <typename T>
sfp::angle<T> operator -(const sfp::angle<T>& left)
{
	return sfp::angle<T>::from_degrees(-left.degrees());
}


template <typename T>
sfp::angle<T> operator +(const sfp::angle<T>& left, const sfp::angle<T>& right)
{
	return sfp::angle<T>::from_degrees(left.degrees() + right.degrees());
}

template <typename T>
sfp::angle<T> operator -(const sfp::angle<T>& left, const sfp::angle<T>& right)
{
	return sfp::angle<T>::from_degrees(left.degrees() - right.degrees());
}

template <typename T>
sfp::angle<T> operator *(const sfp::angle<T>& left, T right)
{
	return sfp::angle<T>::from_degrees(left.degrees() * right);
}

template <typename T>
sfp::angle<T> operator *(T left, const sfp::angle<T>& right)
{
	return sfp::angle<T>::from_degrees(right.degrees() * left);
}

template <typename T>
sfp::angle<T> operator /(const sfp::angle<T>& left, T right)
{
	return sfp::angle<T>::from_degrees(left.degrees() / right);
}

template <typename T>
sfp::angle<T> operator +=(sfp::angle<T>& left, const sfp::angle<T>& right)
{
	left.degrees(left.degrees() + right.degrees());
}

template <typename T>
sfp::angle<T> operator -=(sfp::angle<T>& left, const sfp::angle<T>& right)
{
	left.degrees(left.degrees() - right.degrees());
}

template <typename T>
sfp::angle<T> operator *=(const sfp::angle<T>& left, T right)
{
	left.degrees(left.degrees() * right);
}

template <typename T>
sfp::angle<T> operator /=(const sfp::angle<T>& left, T right)
{
	left.degrees(left.degrees() / right);
}


template <typename T>
sfp::angle<T> operator ==(const sfp::angle<T>& left, const sfp::angle<T>& right)
{
	return left.degrees() == right.degrees();
}

template <typename T>
sfp::angle<T> operator !=(const sfp::angle<T>& left, const sfp::angle<T>& right)
{
	return left.degrees() != right.degrees();
}

template <typename T>
sfp::angle<T> operator <(const sfp::angle<T>& left, const sfp::angle<T>& right)
{
	return left.degrees() < right.degrees();
}

template <typename T>
sfp::angle<T> operator >(const sfp::angle<T>& left, const sfp::angle<T>& right)
{
	return left.degrees() > right.degrees();
}



// Convertions

template<typename T>
T deg_to_rad(T deg)
{
	return static_cast<T>(deg / 57.295779513);
}


template<typename T>
T rad_to_deg(T rad)
{
	return rad * static_cast<T>(57.295779513);
}

