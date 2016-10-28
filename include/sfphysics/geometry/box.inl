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


template <typename T>
sfp::box<T>::box()
{

}

template <typename T>
sfp::box<T>::box(const sfp::vector2<T>& lower, const sfp::vector2<T>& upper) :
m_lowerPoint(lower),
m_upperPoint(upper)
{
// TODO: checking lower/upper, setter, maybe back to SFML design (because it's not safe to work like this) 
}

template <typename T>
sfp::box<T>::box(const sfp::box<T>& b) :
m_lowerPoint(b.m_lowerPoint),
m_upperPoint(b.m_upperPoint)
{

}

template <typename T>
template <typename U>
sfp::box<T>::box(const sfp::box<U>& b) :
m_lowerPoint(vector2<T>(b.m_lowerPoint)),
m_upperPoint(vector2<T>(b.m_upperPoint))
{

}


template <typename T>
bool sfp::box<T>::contains(const sfp::vector2<T>& point) const
{
	return	(point.x >= m_lowerPoint.x) && (point.x >= m_upperPoint.x) && 
			(point.y >= m_lowerPoint.y) && (point.y >= m_upperPoint.y);
}

template <typename T>
bool sfp::box<T>::intersects(const sfp::box<T>& b) const
{
	box<T> intersection;
	intersects(b, intersection);
}

template <typename T>
bool sfp::box<T>::intersects(const sfp::box<T>& b, sfp::box<T>& intersection) const
{
	// Compute the intersection boundaries
	T left   = std::max(m_lowerPoint.x, b.m_lowerPoint.x);
	T top    = std::max(m_lowerPoint.y, b.m_lowerPoint.y);
	T right  = std::min(m_upperPoint.x, b.m_upperPoint.x);
	T bottom = std::min(m_upperPoint.y, b.m_upperPoint.y);
	
	// If the intersection is valid (positive non zero area), then there is an intersection
	if ((left <= right) && (top <= bottom))
	{
		intersection = box<T>(vector2f(left, top), vector2f(right, bottom));
		return true;
	}
	else
	{
		intersection = box<T>();
		return false;
	}
}


template <typename T>
const sfp::vector2<T>& sfp::box<T>::lowerPoint() const
{
	return m_lowerPoint;
}

template <typename T>
const sfp::vector2<T>& sfp::box<T>::upperPoint() const
{
	return m_upperPoint;
}

