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

#include <sfPhysics/Geometry/shape.hpp>

#include <vector>
#include <cstddef>


namespace sfp
{
	
	class PolygonShape : public Shape
	{
		public:
			PolygonShape();
			~PolygonShape();
			
			void pointCount(std::size_t count);
			std::size_t pointCount() const;
			
			void point(std::size_t pos, const vector2f& point);
			const vector2f& point(std::size_t pos) const;
			
			void addPoint(const vector2f& point);
			void clear();
			
			float area() const;
			float inertiaMoment() const;
			vector2f center() const;
			
			boxf bounds() const;
			boxf bounds(const transformf&) const;
						
			minmaxf project(const vector2f& axis) const;
			minmaxf project(const vector2f& axis, const transformf& transform) const;
			
			shape_type type() const { return shape_type::Polygon; }
			std::unique_ptr<Shape> copy() const;
			void accept(ShapeDispatcher& dispatcher) const;
			
		private:
			std::vector<vector2f> m_points;
			
			float m_area;
			float m_inertiaMoment;
			vector2f m_center;
			
			void update();
			void add_triangle(std::size_t pos);
	};
	
}


