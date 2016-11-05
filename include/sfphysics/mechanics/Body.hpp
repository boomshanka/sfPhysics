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

#include <sfphysics/geometry/vector2.hpp>
#include <sfphysics/geometry/angle.hpp>
#include <sfphysics/geometry/transformation.hpp>
#include <sfphysics/geometry/shape.hpp>

#include <sfphysics/mechanics/MaterialDef.hpp>

#include <memory>


namespace sfp
{

	class Body
	{
		public:
			Body(const Shape& shape, const MaterialDef& material = MaterialDef());
			~Body();
			
			// material
			const MaterialDef& material() const;
			void material(const MaterialDef&);
			
			// shape
			const sfp::Shape& bodyshape() const;
			void bodyshape(sfp::Shape& shape);
			
			// position and rotation
			const vector2f& position() const;
			void position(const vector2f& pos);
			
			const anglef& rotation() const;
			void rotation(const anglef& rotation);
			
			// movement and rotation speed
			const vector2f& velocity() const;
			void velocity(const vector2f& vel);
						
			const anglef& angularVelocity() const;
			void angularVelocity(const anglef& vel);
			
			// mass (just getter - determinated by density and area)
			float mass() const;
			
			// transformation functions
			vector2f toGlobal(const vector2f&) const;
			vector2f toLocal(const vector2f&) const;
			const transformf& transformation() const;
			const transformf& inverseTransformation() const;
			
			// bounding box
			boxf bounds() const;
						
			// axis projection
			minmaxf project(const sfp::vector2f& axis) const;
			
			// functions for center of gravity (setter overrides calculated center)
			const vector2f& center() const;
			void center(const vector2f&);
			
		private:
			MaterialDef m_material;
			std::unique_ptr<Shape> m_shape;
			
			vector2f m_center;
			vector2f m_position;
			anglef m_rotation;
			
			vector2f m_velocity;
			anglef m_angularVelocity;
			
			float m_mass;
			float m_angularMass;
			
			mutable transformf m_toGlobal;
			mutable transformf m_toLocal;
			
			mutable enum class transformstate {
				None, ToGlobal, Both
			} m_transformstate;
			
			void updateShape();
			void updateTransformation() const;
	};

}


