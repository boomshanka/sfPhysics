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


#ifndef SFPHYSICS_SPRING_HPP
#define SFPHYSICS_SPRING_HPP


#include <sfPhysics/System/Linkable.hpp>



namespace sfp
{
	class Spring : public Linkable
	{
		private:
			float myLength;
			float mySpringConstant;
			bool myIsQuadratic;
			
		public:
			Spring();
			Spring(sfp::Object* one, sfp::Object* two, const sfp::Vector2f& vone, const sfp::Vector2f& vtwo,
											float length, float springconstant = 10.f, bool quadratic = false);
			
			void SetSpringConstant(float constant) {mySpringConstant = constant;}
			float GetSpringConstant() {return mySpringConstant;}
			
			bool IsQuadratic() {return myIsQuadratic;}
			void SetQuadratic(bool quadratic) {myIsQuadratic = quadratic;}
			
			float RenderForces(sfp::Uint32 time);
	};
	
	
} // namespace sfp



#endif // SFPHYSICS_SPRING_HPP


