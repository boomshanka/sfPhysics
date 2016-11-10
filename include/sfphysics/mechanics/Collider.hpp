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

#include <sfphysics/mechanics/Body.hpp>
#include <sfphysics/mechanics/Contact.hpp>

#include <sfphysics/geometry/circle.hpp>
#include <sfphysics/geometry/polygon.hpp>
#include <sfphysics/geometry/rectangle.hpp>
#include <sfphysics/geometry/plane.hpp>

#include <list>


namespace sfp
{
	// TODO: Possible singleton
	class Collider : public ShapeDispatcher
	{
		public:
			Collider() {}
			
			bool collision(Body& b1, Body& b2, Contact& contact);
			
			void dispatch(const CircleShape& shape);
			void dispatch(const PolygonShape& shape);
			void dispatch(const RectangleShape& shape);
			void dispatch(const PlaneShape& shape);
			
		protected:
			bool planePolygon(Body& b1, Body& b2, Contact& contact);
			bool planeCircle(Body& b1, Body& b2, Contact& contact);
			bool polygonPolygon(Body& b1, Body& b2, Contact& contact);
			bool polygonCircle(Body& b1, Body& b2, Contact& contact);
			bool circleCircle(Body& b1, Body& b2, Contact& contact);
			
			
			bool		project(Body& b1, Body& b2, const std::list<vector2f>& axes);
			
			float		circleRadius(Body& circle);
			vector2f	planeNormal(Body& plane);
			
			void		findPolygonSeparatingAxes(Body& polygon);
			vector2f	closestPolygonPoint(Body& polygon, const vector2f& reference);
			template <typename F>
			vector2f	closestPolygonPoint(vector2f referencePoint, unsigned int pointCount, F globalPointPosition);
			
		private:
			enum class PolygonTask {closestPoint, separatingAxis} m_polygonTask;
			
			transformf m_transform;
			vector2f m_point;
			std::list<vector2f> m_axes;
			
			vector2f m_normal;
			
			float m_radius;
	};

}


