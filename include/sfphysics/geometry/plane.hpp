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

#include <sfphysics/geometry/shape.hpp>
#include <sfphysics/geometry/vector2.hpp>


namespace sfp
{
	
	class PlaneShape : public Shape
	{
		public:
			PlaneShape(const vector2f& normal, const vector2f& center = vector2f(0, 0));
			~PlaneShape();
			
			vector2f center() const;
			void center(const vector2f& center);
			
			const vector2f& normal() const;
			vector2f normal(const transformf& transform) const;
			void normal(const vector2f& normal);
			
			float area() const;
			float inertia_moment() const;
			
			boxf bounds() const;
			boxf bounds(const transformf&) const;
						
			minmaxf project(const vector2f& axis) const;
			minmaxf project(const vector2f& axis, const transformf& transform) const;
			
			shape_type type() const { return shape_type::Plane; }
			std::unique_ptr<Shape> copy() const;
			void accept(ShapeDispatcher& dispatcher) const;
			
		private:
			vector2f m_normal;
			vector2f m_center;
			
	};
	
}


