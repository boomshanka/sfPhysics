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
	
	class CircleShape : public Shape
	{
		public:
			CircleShape(float radius, const vector2f& center = vector2f(0, 0));
			~CircleShape();
			
			vector2f center() const;
			void center(const vector2f& center);
			
			float radius() const;
			void radius(float radius);
			
			float area() const;
			float inertia_moment() const;
			
			boxf bounds() const;
			boxf bounds(const transformf&) const;
			
			unsigned int separatingAxisCount() const { return 0; }
			vector2f separatingAxis(unsigned int index) const { return vector2f(1,0); }
			vector2f separatingAxis(unsigned int index, const transformf& transform) const { return vector2f(1,0); }
			
			minmaxf project(const vector2f& axis) const;
			minmaxf project(const vector2f& axis, const transformf& transform) const;
			
			shape_type type() const { return shape_type::Circle; }
			std::unique_ptr<Shape> copy() const;
			void accept(ShapeDispatcher& dispatcher) const;
			
		private:
			float m_radius;
			vector2f m_center;
			
	};
	
}


