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


#ifndef SFPHYSICS_COLLISIONMANAGER_HPP
#define SFPHYSICS_COLLISIONMANAGER_HPP


#include <sfPhysics/System/Objects.hpp>
#include <sfPhysics/System/Collision.hpp>
#include <sfPhysics/System/CollisionEvent.hpp>
#include <sfPhysics/System/Contact.hpp>
#include <sfPhysics/System/ObjectList.hpp>



namespace sfp
{
	
	class CollisionManager : virtual public ObjectList
	{
		private:
			sfp::Collision myCollision;
			sfp::ContactManager myContactManager;
			
		public:
			CollisionManager();
			virtual ~CollisionManager();
			
			void UpdateCollisions();
			
			//bool CheckCollision(sfp::Object&, sfp::Object&);
			
			void CollisionResponse(sfp::CollisionEvent& event);
			
		protected:
			virtual void OnPreciseCollision(sfp::CollisionEvent& event);
			virtual void OnBoundingBoxCollision(sfp::CollisionEvent& event) = 0;
			virtual void OnNoCollision(sfp::CollisionEvent& event) = 0;
			
	};

} // namespace


#endif // COLLISIONMANAGER_HPP



