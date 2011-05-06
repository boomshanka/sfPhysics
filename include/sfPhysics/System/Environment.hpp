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


#ifndef SFPHYSICS_ENVIRONMENT_HPP
#define SFPHYSICS_ENVIRONMENT_HPP


#include <sfPhysics/SFML_Graphics.hpp>
#include <sfPhysics/System/Objects.hpp>
#include <sfPhysics/System/ObjectList.hpp>



namespace sfp
{
	class Environment : virtual public ObjectList
	{
		private:
			sf::Vector2f myGravity;
			float myTimefactor;
			float myLengthfactor;
			
			float myFrameTime;
			
			bool myMoveDrawableEnabled;
		public:
			Environment();
			virtual ~Environment();
			
			void UpdateFrameTime(float time) {myFrameTime=time;}
			float GetFrameTime() const {return myFrameTime;}
			
			void SetTimeFactor(float timefactor) {myTimefactor=timefactor;}
			float GetTimeFactor() const {return myTimefactor;}
			
			void SetLengthFactor(float lengthfactor) {myLengthfactor=lengthfactor;}
			float GetLengthFactor() const {return myLengthfactor;}
			
			const sf::Vector2f& GetGravity() const {return myGravity;}
			void SetGravity(const sf::Vector2f& gravity) {myGravity=gravity;}
			
			void EnableMoveDrawable(bool enabled) {myMoveDrawableEnabled=enabled;}
			
			void RenderGravity();
			
			void MoveObjects();
			
			virtual void MoveDrawable();
			
	};
	
} // namespace sfp


#endif // SFPHYSICS_ENVIRONMENT_HPP


