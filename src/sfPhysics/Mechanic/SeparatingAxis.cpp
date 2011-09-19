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


#include <sfPhysics/Mechanic/SeparatingAxis.hpp>



sfp::SeparatingAxis::SeparatingAxis()
:myRotation(0)
{

}


sfp::SeparatingAxis::SeparatingAxis(const std::vector<sf::Vector2f>& points)
:myRotation(0)
{
	ComputeSeparatingAxis(points);
}



void sfp::SeparatingAxis::ComputeSeparatingAxis(const std::vector<sf::Vector2f>& points)
{
	if(points.size()>2)
	{
		myAxis.push_back(sfp::Vector2f(-(points[0].y-points[points.size()-1].y),points[0].x-points[points.size()-1].x));
		myAxis.back().Normalize();
	}
	
	for(size_t i = 1; i < points.size(); ++i)
	{
		myAxis.push_back(sfp::Vector2f(-(points[i].y-points[i-1].y),points[i].x-points[i-1].x));
		myAxis.back().Normalize();
	}
}



void sfp::SeparatingAxis::UpdateRotation(float rotation) const
{
	if(myRotation!=rotation)
	{
		for(size_t i = 0; i < myAxis.size(); ++i)
		{
			myAxis[i].Rotate(rotation-myRotation);
		}
		
		myRotation = rotation;
	
	}
}



