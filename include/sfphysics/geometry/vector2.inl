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


//	0°		→	1,0
//	90°		↓	0,1
//	180°	←	-1,0
//	270°	↑	0,-1
//	360°	→	1,0



template <typename T>
inline sfp::vector2<T>::vector2()
{

}


template <typename T>
inline sfp::vector2<T>::vector2(T X, T Y) 
{
	this->x = X;
	this->y = Y;
}


template <typename T>
inline sfp::vector2<T>::vector2(const vector2<T>& vec)
{
	this->x = vec.x;
	this->y = vec.y;
}


template <typename T>
template <typename U>
inline sfp::vector2<T>::vector2(const vector2<U>& vec)
{
	this->x = static_cast<T>(vec.x);
	this->y = static_cast<T>(vec.y);
}


template <typename T>
inline sfp::vector2<T>::vector2(const sf::Vector2<T>& vec)
{
	this->x = vec.x;
	this->y = vec.y;
}



template <typename T>
inline T sfp::vector2<T>::length() const
{
	return std::sqrt(this->squaredLength());
}


template <typename T>
inline T sfp::vector2<T>::length(const angle<T>& direction) const
{//FIXME einfacher?
	sfp::vector2<T> vec;
	
	vec.x = trig<T>::cos(direction);
	vec.y = trig<T>::sin(direction);
	
	return dot_product(*this, vec);
}


template <typename T>
inline T sfp::vector2<T>::squaredLength() const
{
	return this->x*this->x + this->y*this->y;
}


template <typename T>
inline sfp::angle<T> sfp::vector2<T>::direction() const
{ // FIXME siehe trig form von Imaginären Zahlen (Mathe Skript)
	if(this->y < 0)
		return trig<T>::atan2(this->y, this->x) + angle<T>::from_degrees(360);
	
	return trig<T>::atan2(this->y, this->x);
}



template <typename T>
inline sfp::vector2<T>&  sfp::vector2<T>::length(T length)
{
	if(*this != sfp::vector2<T>(0, 0))
		*this *= length / this->length();
		
	return *this;
}


template <typename T>
inline sfp::vector2<T>& sfp::vector2<T>::length(T length, const angle<T>& direction)
{
	this->x = trig<T>::cos(direction) * length;
	this->y = trig<T>::sin(direction) * length;
	
	return *this;
}


template <typename T>
inline sfp::vector2<T>& sfp::vector2<T>::direction(const angle<T>& direction)
{
	this->set_length(this->length(), direction.degrees());
	return *this;
}


template <typename T>
inline sfp::vector2<T>& sfp::vector2<T>::rotate(const angle<T>& rotation)
{
	this->set_length(this->length(), rotation + this->direction());
	return *this;
}



template <typename T>
inline sfp::vector2<T>& sfp::vector2<T>::extend(T length)
{
	this->get_unit_vector();
	*this += (this->get_unit_vector() * length);
	
	return *this;
}


template <typename T>
inline sfp::vector2<T>& sfp::vector2<T>::extend(T length, const angle<T>& direction)
{
	this->x += trig<T>::cos(direction) * length;
	this->y += trig<T>::sin(direction) * length;
	
	return *this;
}


template <typename T>
inline sfp::vector2<T>& sfp::vector2<T>::normalize()
{
	if(*this != sfp::vector2<T>(0, 0))
		*this /= this->length();
		
	return *this;
}



template <typename T>
inline sfp::vector2<T> sfp::vector2<T>::normal() const
{
	return sfp::vector2<T>(-this->y, this->x);
}


template <typename T>
inline sfp::vector2<T> sfp::vector2<T>::unit() const
{
	if(*this != sfp::vector2<T>(0, 0))
		return *this / this->length();
}


template <typename T>
inline sfp::vector2<T> sfp::vector2<T>::rotated(const angle<T>& rotation) const
{
	sfp::vector2<T> vec(*this); vec.rotate(rotation);
	return vec;
}


// operator


template <typename T>
inline sfp::vector2<T> operator -(const sfp::vector2<T>& right)
{
	return vector2<T>(-right.x, -right.y);
}


template <typename T>
inline sfp::vector2<T>& operator +=(sfp::vector2<T>& left, const sfp::vector2<T>& right)
{
	left.x += right.x;
	left.y += right.y;
	
	return left;
}


template <typename T>
inline sfp::vector2<T>& operator -=(sfp::vector2<T>& left, const sfp::vector2<T>& right)
{
	left.x -= right.x;
	left.y -= right.y;
	
	return left;
}


template <typename T>
inline sfp::vector2<T> operator +(const sfp::vector2<T>& left, const sfp::vector2<T>& right)
{
	return vector2<T>(left.x + right.x, left.y + right.y);
}


template <typename T>
inline sfp::vector2<T> operator -(const sfp::vector2<T>& left, const sfp::vector2<T>& right)
{
	return vector2<T>(left.x - right.x, left.y - right.y);
}


template <typename T>
inline sfp::vector2<T> operator *(const sfp::vector2<T>& left, T right)
{
	return sfp::vector2<T>(left.x * right, left.y * right);
}


template <typename T>
inline sfp::vector2<T> operator *(T left, const sfp::vector2<T>& right)
{
	return sfp::vector2<T>(left * right.x, left * right.y);
}


template <typename T>
inline sfp::vector2<T>& operator *=(sfp::vector2<T>& left, T right)
{
	left.x *= right;
	left.y *= right;
	
	return left;
}


template <typename T>
inline sfp::vector2<T> operator /(const sfp::vector2<T>& left, T right)
{
	return sfp::vector2<T>(left.x / right, left.y / right);
}


template <typename T>
inline sfp::vector2<T>& operator /=(sfp::vector2<T>& left, T right)
{
	left.x /= right;
	left.y /= right;
	
	return left;
}


template <typename T>
inline bool operator ==(const sfp::vector2<T>& left, const sfp::vector2<T>& right)
{
	return left.x == right.x && left.y == right.y;
}


template <typename T>
inline bool operator !=(const vector2<T>& left, const vector2<T>& right)
{
	return left.x != right.x || left.y != right.y;
}


// new operator


template <typename T>
inline sfp::vector2<T> operator *(const sfp::vector2<T>& left, const sfp::vector2<T>& right)
{
	return sfp::vector2<T>(left.x * right.x, left.y * right.y);
}


template <typename T>
inline sfp::vector2<T>& operator *=(sfp::vector2<T>& left, const sfp::vector2<T>& right)
{
	left.x *= right.x;
	left.y *= right.y;
	
	return left;
}


template <typename T>
inline sfp::vector2<T> operator /(const sfp::vector2<T>& left, const sfp::vector2<T>& right)
{
	return sfp::vector2<T>(left.x / right.x, left.y / right.y);
}


template <typename T>
inline sfp::vector2<T>& operator /=(sfp::vector2<T>& left, const sfp::vector2<T>& right)
{
	left.x /= right.x;
	left.y /= right.y;
	
	return left;
}



template <typename T>
inline float cross_product(const sfp::vector2<T>& left, const sfp::vector2<T>& right)
{
	return left.x*right.y - left.y*right.x;
}


template <typename T>
inline float dot_product(const sfp::vector2<T>& left, const sfp::vector2<T>& right)
{
	return left.x*right.x + left.y*right.y;
}


template <typename T>
inline std::ostream& operator<<(std::ostream& os, const sf::Vector2<T>& vec)
{
	return os << "(" << vec.x << "," << vec.y << ")";
}



