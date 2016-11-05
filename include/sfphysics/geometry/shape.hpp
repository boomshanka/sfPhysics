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

#include <sfphysics/geometry/minmax.hpp>
#include <sfphysics/geometry/vector2.hpp>
#include <sfphysics/geometry/box.hpp>
#include <sfphysics/geometry/transformation.hpp>

#include <memory>


namespace sfp
{
	class ShapeDispatcher;
	
	enum class shape_type {
		Circle,
		Polygon,
		Rectangle,
		Plane
	};
	
	
	class Shape
	{
		public:
			virtual ~Shape() {}
			
			virtual float area() const = 0;
			virtual float inertia_moment() const = 0;
			virtual vector2f center() const = 0;
			
			virtual boxf bounds() const = 0;
			virtual boxf bounds(const transformf&) const = 0;
						
			virtual minmaxf project(const vector2f& axis) const = 0;
			virtual minmaxf project(const vector2f& axis, const transformf& transform) const = 0;
			
			virtual shape_type type() const = 0;
			virtual std::unique_ptr<Shape> copy() const = 0;
			virtual void accept(ShapeDispatcher& dispatcher) const = 0;
	};
	
	// Forward declaration of shape types
	class CircleShape;
	class PolygonShape;
	class RectangleShape;
	class PlaneShape;
	
	class ShapeDispatcher
	{
	public:
		virtual void dispatch(const CircleShape& shape) = 0;
		virtual void dispatch(const PolygonShape& shape) = 0;
		virtual void dispatch(const RectangleShape& shape) = 0;
		virtual void dispatch(const PlaneShape& shape) = 0;
	};
}


