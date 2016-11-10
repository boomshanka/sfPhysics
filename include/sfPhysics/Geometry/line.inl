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
inline sfp::line<T>::line(bool inf) :
infinite(inf)
{

}


template <typename T>
inline sfp::line<T>::line(const sfp::vector2<T>& first, const sfp::vector2<T>& second, bool inf) :
first_point(first), second_point(second), infinite(inf)
{

}


// TODO
template <typename T>
inline bool sfp::line<T>::contains(const sfp::vector2<T>& point, float& relative_position)
{
//	if(cross_product(direction, p - point) == 0)
	{
		
		return true;
	}
	
	return false;
}


/*
template <typename T>
inline bool sfp::line<T>::intersects(const sfp::line<T>& line, float& relative_position)
{
	float cross = cross_product(direction, line.direction);
	
	if(cross == 0)
		return false;
	
	relative_position = cross_product(line.direction, point - line.point) / cross;
	
	return true;
}
*/



