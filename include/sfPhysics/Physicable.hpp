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
			
			sf::Vector2f myCenter;	//Center of gravity
			
			//	Properties	//
			float myArea;
			float myMass;
			float myDensity;
			float myRestitution;	//Abprallkraft
			float myFriction;		//Reibung
			
		public:
			Physicable();
			
			void SetSpeed(sfp::Vector2f speed) {mySpeed=speed;}
			void SetImpulse(sfp::Vector2f impulse) {mySpeed=impulse/myMass;}
			
			void SetRotationSpeed(float speed) {myRotationSpeed=speed;}
			void SetRotationForce(float force); //FIXME
			
			
			sfp::Vector2f GetSpeed() {return mySpeed;}
			sfp::Vector2f GetImpulse() {return mySpeed*myMass;}
			
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
			
			
			void Force(sf::Vector2f position, float direction, float force);
			void Force(sf::Vector2f position, sfp::Vector2f force); //FIXME
			
		protected:
			sf::Vector2f ComputeArea(const std::vector<Polygon>&);
			std::pair<sf::Vector2f, float> ComputeArea(const std::vector<sf::Vector2f>&);
			
	};

} // Namespace

#endif // PHYSICABLE_HPP


