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
			float myArea;
			float myInertiaMoment;	//Trägheitsmoment
			
			float myMass;
			float myDensity;
			float myRestitution;	//Abprallkraft
			float myFriction;		//Reibung
			
		public:
			Physicable();
			
			void SetSpeed(sfp::Vector2f speed) {mySpeed=speed;}
			void SetImpulse(sfp::Vector2f impulse) {mySpeed=impulse/myMass;}
			
			void SetRotationSpeed(float speed) {myRotationSpeed=speed;}
			void SetRotationForce(float force) {myRotationSpeed=2*force/myInertiaMoment;}
			
			
			sfp::Vector2f GetSpeed() const {return mySpeed;}
			sfp::Vector2f GetImpulse() const {return mySpeed*myMass;}
			
			float GetRotationSpeed() const {return myRotationSpeed;}
			float GetRotationForce() const {return 0.5*myRotationSpeed*myInertiaMoment;}
			
			
			
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
			
			
			void Force(const sf::Vector2f& position, float direction, float force);
			void Force(const sf::Vector2f& position, const sfp::Vector2f& force); //FIXME
			
		protected:
			sf::Vector2f ComputeArea(std::vector<sfp::Polygon>&);
			std::pair<sf::Vector2f, float> ComputeArea(const std::vector<sf::Vector2f>&);
			std::pair<sf::Vector2f, float> ComputeArea(const sf::Vector2f&, float);
			
	};

} // Namespace

#endif // PHYSICABLE_HPP


