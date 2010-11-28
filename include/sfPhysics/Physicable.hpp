#ifndef PHYSICABLE_HPP
#define PHYSICABLE_HPP


#include <sfPhysics/SFML_Graphics.hpp>
#include <sfPhysics/Vector2.hpp>
#include <sfPhysics/Polygon.hpp>

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
			
			sf::Vector2f myCenter;	//Center of gravity/mass
			float myArea;
			float myInertiaMoment;	//Trägheitsmoment
			
			float myMass;
			float myDensity;
			float myRestitution;	//Abprallkraft
			float myFriction;		//Reibung
			
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
			
			
			
			bool SetMass(float);
			bool SetDensity(float);
			bool SetArea(float);//
			bool SetRestitution(float);
			bool SetFriction(float);
			
			float GetMass() const {return myMass;}
			float GetDensity() const {return myDensity;}
			float GetArea() const {return myArea;}
			float GetRestitution() const {return myRestitution;}
			float GetFriction() const {return myFriction;}
			
	};

} // Namespace

#endif // PHYSICABLE_HPP


