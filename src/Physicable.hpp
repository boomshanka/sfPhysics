#ifndef PHYSICABLE_HPP
#define PHYSICABLE_HPP


#include "SFML_Graphics.hpp"
#include "Vector2.hpp"

#include <vector>


namespace sfp
{
	class Physicable
	{
		friend class Object;
		
		private:
			sf::Vector2f myGlobalPosition;
			
			sfp::Vector2f mySpeed;
			float myRotationSpeed;
			float myRotation;
			
			float myOldRotation;
			
			sf::Vector2f myCenter;	//Center of gravity
			
			//	Properties	//
			float myMass;
			float myDensity;
			float myArea;
			float myRestitution;	//Abprallkraft
			float myFriction;		//Reibung
			
			sf::Vector2f ComputeArea(const std::vector<sf::Vector2f>&);
		public:
			Physicable();
			
			void SetSpeed(sfp::Vector2f speed) {mySpeed=speed;}
			void SetImpulse(sfp::Vector2f impulse) {mySpeed=impulse/myMass;}
			void Move(const sf::Vector2f& move) {myGlobalPosition+=move;}
			void SetPosition(const sf::Vector2f pos) {myGlobalPosition=pos;}
			
			void SetCenter(const sf::Vector2f& center) {myCenter=center;}
			
			void Rotate(float angle) {myRotation+=angle;}
			void SetRotation(float angle) {myRotation=angle;}
			void SetRotationSpeed(float speed) {myRotationSpeed=speed;}
			void SetRotationForce(float force); //FIXME
			
			
			sfp::Vector2f GetSpeed() {return mySpeed;}
			sfp::Vector2f GetImpulse() {return mySpeed*myMass;}
			sf::Vector2f GetPosition() {return myGlobalPosition;}
			
			sf::Vector2f GetCenter() {return myCenter;}
			
			float GetRotation() {return myRotation;}
			float GetRotationSpeed() {return myRotationSpeed;}
			float GetRotationForce(); //FIXME
			
			
			
			bool SetMass(float);
			bool SetDensity(float);
			bool SetArea(float);//
			bool SetRestitution(float);
			bool SetFriction(float);
			
			float GetMass() {return myMass;}
			float GetDensity() {return myDensity;}
			float GetArea() {return myArea;}
			float GetRestitution() {return myRestitution;}
			float GetFriction() {return myFriction;}
			
			
			
			void Force(); //FIXME
	};

} // Namespace

#endif // PHYSICABLE_HPP


