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
 
 
 #include <cmath>
 
 
template <typename T>
inline sfp::triangle<T>::triangle(const sfp::vector2<T>& p_1, const sfp::vector2<T>& p_2, const sfp::vector2<T>& p_3) :
p1(p_1), p2(p_2), p3(p_3)
{

}


template <typename T>
inline sfp::triangle<T>::~triangle()
{

}


template <typename T>
inline T sfp::triangle<T>::area() const
{
	return std::abs(cross_product(p2 - p1, p3 - p1) / static_cast<T>(2));
}


template <typename T>
inline T sfp::triangle<T>::perimeter() const
{
	return (p2 - p1).length()  + (p3 - p2).get_length() + (p1 - p3).length();
}



template <typename T>
inline T sfp::triangle<T>::inertiaMoment() const
{
	sfp::vector2<T> a(p2 - p1);
	sfp::vector2<T> b(p3 - p2);
	
	return (std::abs(cross_product(a, b) / static_cast<T>(2)) * // area
			(a.squaredLength() + b.squaredLength() + sfp::vector2<T>(p1 - p3).squaredLength())) / // squared sides
			static_cast<T>(36); // factor 1/36
}


template <typename T>
inline sfp::vector2<T> sfp::triangle<T>::center() const
{
	return (p1 + p2 + p3) / static_cast<T>(3);
}

