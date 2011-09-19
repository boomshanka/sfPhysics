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


#ifndef SFPHYSICS_COLLISION_HPP
#define SFPHYSICS_COLLISION_HPP


#include <sfPhysics/Mechanic/Objects.hpp>
#include <sfPhysics/Mechanic/CollisionEvent.hpp>
#include <sfPhysics/Mechanic/Contact.hpp>
#include <sfPhysics/Mechanic/ObjectList.hpp>

#include <cstddef>



namespace sfp
{
	
	class Collision
	{
		private:
			sfp::Object* myFirstObject;
			sfp::Object* mySecondObject;
			
			std::size_t myFirstConvexShapes;
			std::size_t mySecondConvexShapes;
			
		public:
			Collision();
			~Collision();
			
			bool PollCollisions(sfp::CollisionEvent& event);
			void SeparateObjects(sfp::CollisionEvent& event);
			void ComputeCollisionProperties(sfp::CollisionEvent& event);
			
			bool CheckBoundingBoxCollision(sfp::CollisionEvent& event);
			bool CheckCollision(sfp::CollisionEvent& event); //FIXME preciese collision
			
			void PolygonPolygon(sfp::CollisionEvent& event);
			void PolygonCircle(sfp::CollisionEvent& event);
			void PlanePolygon(sfp::CollisionEvent& event);
			void PlaneCircle(sfp::CollisionEvent& event);
			void CircleCircle(sfp::CollisionEvent& event);
			
		private:
			void SwapEventObjects(sfp::CollisionEvent& event);
			
			bool ComputeSAT(sfp::CollisionEvent& event, sfp::Vector2f& vec);
			void ComputePolygonPolygonContact(sfp::CollisionEvent& event);
			void ComputePlanePolygonContact(sfp::CollisionEvent& event);
	};
}


#endif


