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


#ifndef SFPHYSICS_LINKABLE_HPP
#define SFPHYSICS_LINKABLE_HPP


#include <sfPhysics/Settings.hpp>
#include <sfPhysics/System/Objects.hpp>



namespace sfp
{
	class Linkable
	{
		protected:
			sfp::Object* first;
			sfp::Object* second;
			
			sfp::Vector2f firstlink;
			sfp::Vector2f secondlink;
			
		public:
			Linkable() : first(NULL), second(NULL) {}
			Linkable(sfp::Object* one, sfp::Object* two, const sfp::Vector2f& vone, const sfp::Vector2f& vtwo)
			: first(one), second(two), firstlink(vone), secondlink(vtwo) {}
			virtual ~Linkable() {}
			
			void LinkObjects(sfp::Object* one, sfp::Object* two, const sfp::Vector2f& vone, const sfp::Vector2f& vtwo)
			{
				first = one; second = two; firstlink = vone; secondlink = vtwo;
			}
			void SetFirstObject(sfp::Object* object, const sfp::Vector2f& vec) {first = object; firstlink = vec;}
			void SetSecondObject(sfp::Object* object, const sfp::Vector2f& vec) {second = object; secondlink = vec;}
			
			void RemoveFirstObject() {first = NULL;}
			void RemoveSecondObject() {second = NULL;}
			
			sfp::Object* GetFirstObject() {return first;}
			sfp::Object* GetSecondObject() {return second;}
			
			virtual float RenderForces(sfp::Uint32 time) = 0;
			
	};
	
	
} // namespace sfp



#endif // SFPHYSICS_LINKABLE_HPP


