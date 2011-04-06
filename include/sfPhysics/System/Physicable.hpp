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


#ifndef SFPHYSICS_PHYSICABLE_HPP
#define SFPHYSICS_PHYSICABLE_HPP


#include <sfPhysics/System/Vector2.hpp>
#include <sfPhysics/System/Shape.hpp>

#include <vector>
#include <utility>



namespace sfp
{
	
	class Physicable
	{
		friend class Object;
		
		private:
			sfp::Vector2f myVelocity;
			float myRotationVelocity;
			
			sf::Vector2f myCenter;		//Center of gravity/mass
			float myArea;				//Fläche
			float myInertiaMoment;		//Trägheitsmoment
			
			float myMass;				//Masse
			float myDensity;			//Dichte
			float myRestitution;		//Abprallkraft
			float myDynamicFriction;	//Dynamische Reibung
			float myStaticFriction;		//Statische Reibung
			
		public:
			Physicable();
			
			void SetVelocity(const sfp::Vector2f& velocity) {myVelocity=velocity;}
			void AddVelocity(const sfp::Vector2f& velocity) {myVelocity+=velocity;}
			
			void SetImpulse(const sfp::Vector2f& impulse) {myVelocity= impulse/myMass;}
			void AddImpulse(const sfp::Vector2f& impulse) {myVelocity+= impulse/myMass;}
			
			void SetRotationVelocity(float velocity) {myRotationVelocity=velocity;}
			void AddRotationVelocity(float velocity) {myRotationVelocity+=velocity;}
			
			void SetRotationImpulse(float impulse) {myRotationVelocity=impulse/myInertiaMoment;}
			void AddRotationImpulse(float impulse) {myRotationVelocity+=impulse/myInertiaMoment;}
			
			
			const sfp::Vector2f& GetVelocity() const {return myVelocity;}
			sfp::Vector2f GetImpulse() const {return myVelocity*myMass;}
			
			float GetRotationVelocity() const {return myRotationVelocity;}
			float GetRotationImpulse() const {return myRotationVelocity*myInertiaMoment;}
			
			void RemoveForces() {myVelocity=sfp::Vector2f(0,0); myRotationVelocity=0;}
			
			
			bool SetMass(float);
			bool SetDensity(float);
			bool SetArea(float);
			bool SetRestitution(float);
			bool SetFriction(float);
			bool SetDynamicFriction(float);
			bool SetStaticFriction(float);
			bool SetInertiaMoment(float);
			
			float GetMass() const {return myMass;}
			float GetDensity() const {return myDensity;}
			float GetArea() const {return myArea;}
			float GetRestitution() const {return myRestitution;}
			float GetDynamicFriction() const {return myDynamicFriction;}
			float GetStaticFriction() const {return myStaticFriction;}
			float GetInertiaMoment() const {return myInertiaMoment;}
			
	};
	
} // namespace


#endif // SFPHYSICS_PHYSICABLE_HPP


