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

#include <sfphysics/mechanics/body.hpp>
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
			
			bool collision(body& b1, body& b2, Contact& contact);
			
			void dispatch(const CircleShape& shape);
			void dispatch(const PolygonShape& shape);
			void dispatch(const RectangleShape& shape);
			void dispatch(const PlaneShape& shape);
			
		protected:
			bool planePolygon(body& b1, body& b2, Contact& contact) const;
			bool planeCircle(body& b1, body& b2, Contact& contact) const;
			bool polygonPolygon(body& b1, body& b2, Contact& contact);
			bool polygonCircle(body& b1, body& b2, Contact& contact);
			bool circleCircle(body& b1, body& b2, Contact& contact) const;
			
			bool project(body& b1, body& b2, const std::list<sfp::vector2f>& axes) const;
			
			
		private:
			mutable bool m_nearestPoint;
			mutable transformf m_transform;
			mutable std::list<sfp::vector2f> m_axes;
			mutable vector2f m_point;
	};

}


