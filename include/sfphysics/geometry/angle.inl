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
: m_degree(0)
{

}

template<typename T>
sfp::angle<T>::angle(T degree)
: m_degree(degree)
{

}



template<typename T>
void sfp::angle<T>::radian(T val)
{
	m_degree = rad_to_deg<T>(val);
}

template<typename T>
void sfp::angle<T>::degree(T val)
{
	m_degree = val;
}


template<typename T>
T sfp::angle<T>::degree() const
{
	return m_degree;
}

template<typename T>
T sfp::angle<T>::radian() const
{
	return deg_to_rad<T>(m_degree);
}



template<typename T>
void sfp::angle<T>::normalize()
{
	m_degree -= static_cast<int>(m_degree / 360.f) * static_cast<T>(360);
}


template<typename T>
sfp::angle<T> sfp::angle<T>::from_radian(T radian)
{
	return angle<T>(rad_to_deg(radian));
}

template<typename T>
sfp::angle<T> sfp::angle<T>::from_degree(T degree)
{
	return angle<T>(degree);
}


// operatoren

template <typename T>
sfp::angle<T> operator -(const sfp::angle<T>& left)
{
	return sfp::angle<T>::from_degree(-left.degree());
}


template <typename T>
sfp::angle<T> operator +(const sfp::angle<T>& left, const sfp::angle<T>& right)
{
	return sfp::angle<T>::from_degree(left.degree() + right.degree());
}

template <typename T>
sfp::angle<T> operator -(const sfp::angle<T>& left, const sfp::angle<T>& right)
{
	return sfp::angle<T>::from_degree(left.degree() - right.degree());
}

template <typename T>
sfp::angle<T> operator *(const sfp::angle<T>& left, T right)
{
	return sfp::angle<T>::from_degree(left.degree() * right);
}

template <typename T>
sfp::angle<T> operator *(T left, const sfp::angle<T>& right)
{
	return sfp::angle<T>::from_degree(right.degree() * left);
}

template <typename T>
sfp::angle<T> operator /(const sfp::angle<T>& left, T right)
{
	return sfp::angle<T>::from_degree(left.degree() / right);
}

template <typename T>
sfp::angle<T> operator +=(sfp::angle<T>& left, const sfp::angle<T>& right)
{
	left.degree(left.degree() + right.degree());
}

template <typename T>
sfp::angle<T> operator -=(sfp::angle<T>& left, const sfp::angle<T>& right)
{
	left.degree(left.degree() - right.degree());
}

template <typename T>
sfp::angle<T> operator *=(const sfp::angle<T>& left, T right)
{
	left.degree(left.degree() * right);
}

template <typename T>
sfp::angle<T> operator /=(const sfp::angle<T>& left, T right)
{
	left.degree(left.degree() / right);
}


template <typename T>
sfp::angle<T> operator ==(const sfp::angle<T>& left, const sfp::angle<T>& right)
{
	return left.degree() == right.degree();
}

template <typename T>
sfp::angle<T> operator !=(const sfp::angle<T>& left, const sfp::angle<T>& right)
{
	return left.degree() != right.degree();
}

template <typename T>
sfp::angle<T> operator <(const sfp::angle<T>& left, const sfp::angle<T>& right)
{
	return left.degree() < right.degree();
}

template <typename T>
sfp::angle<T> operator >(const sfp::angle<T>& left, const sfp::angle<T>& right)
{
	return left.degree() > right.degree();
}


// konvertierungen


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

