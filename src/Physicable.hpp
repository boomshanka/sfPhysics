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
			float myRotation;
			
			sf::Vector2f myCenter;	//Center of gravity
			
			//	Properties	//
			float myMass;
			float myDensity;
			float myArea;
			float myRestitution;	//Abprallkraft
			float myFriction;		//Reibung
			
			void ComputeArea(const std::vector<sf::Vector2f>&);
		public:
			Physicable();
			
			
			//	Getter & Setter	//
			bool SetMass(float);
			bool SetDensity(float);
			bool SetArea(float);//
			bool SetRestitution(float);
			bool SetFriction(float);

			void SetCenter(const sf::Vector2f& center) {myCenter=center;}
			void SetSpeed(sfp::Vector2f speed) {mySpeed=speed;}
			void SetImpulse(sfp::Vector2f impulse) {mySpeed=impulse/myMass;}
			
			sf::Vector2f GetCenter() {return myCenter;}
			sfp::Vector2f GetSpeed() {return mySpeed;}
			sfp::Vector2f GetImpulse() {return mySpeed*myMass;}
			
			float GetMass() {return myMass;}
			float GetDensity() {return myDensity;}
			float GetArea() {return myArea;}
			float GetRestitution() {return myRestitution;}
			float GetFriction() {return myFriction;}
		
	};

} // Namespace

#endif // PHYSICABLE_HPP


