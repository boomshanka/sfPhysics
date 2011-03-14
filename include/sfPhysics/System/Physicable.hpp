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
			sfp::Vector2f mySpeed;
			float myRotationSpeed;
			
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
			
			void SetSpeed(const sfp::Vector2f& speed) {mySpeed=speed;}
			void AddSpeed(const sfp::Vector2f& speed) {mySpeed+=speed;}
			
			void SetImpulse(const sfp::Vector2f& impulse) {mySpeed= impulse/myMass;}
			void AddImpulse(const sfp::Vector2f& impulse) {mySpeed+= impulse/myMass;}
			
			void SetRotationSpeed(float speed) {myRotationSpeed=speed;}
			void AddRotationSpeed(float speed) {myRotationSpeed+=speed;}
			
			void SetRotationImpulse(float impulse) {myRotationSpeed=impulse/myInertiaMoment;}
			void AddRotationImpulse(float impulse) {myRotationSpeed+=impulse/myInertiaMoment;}
			
			
			const sfp::Vector2f& GetSpeed() const {return mySpeed;}
			sfp::Vector2f GetImpulse() const {return mySpeed*myMass;}
			
			float GetRotationSpeed() const {return myRotationSpeed;}
			float GetRotationImpulse() const {return myRotationSpeed*myInertiaMoment;}
			
			void RemoveForces() {mySpeed=sfp::Vector2f(0,0); myRotationSpeed=0;}
			
			
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

} // Namespace

#endif // SFPHYSICS_PHYSICABLE_HPP


