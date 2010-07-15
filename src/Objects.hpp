#ifndef OBJECTS_HPP
#define OBJECTS_HPP


#include "SFML_Graphics.hpp"
#include "Polygon.hpp"
#include "Physicable.hpp"

#include "SAT.hpp"

#include <vector>
#include <SFML/System.hpp>
#ifdef SFML_GRAPHICS_ENABLED
#include <SFML/Graphics.hpp>
#endif


#define _USE_MATH_DEFINES


namespace sfp
{
	class SeparatingAxis;
	
	
	class Time //FIXME übderdenken
	{
		public:
			static sf::Clock Frametime;	
			static float ElapsedTime;
	};
	

	
	
	class Object : public Polygon, public Physicable
	{
		private:
			sf::Vector2f myPosition;
			sf::Vector2f myCenter;
			float myRotation;
			
			bool mySeparatingAxisEnabled;
			sfp::SeparatingAxis* mySeparatingAxis;
			
			float mySatRotation;
		public:
			Object();
			~Object();
			
			// //
			void ComputeArea() {SetCenter(Physicable::ComputeArea(sfp::Polygon::myPoints));}
			
			void EnableSeparatingAxis(bool enabled) {mySeparatingAxisEnabled=enabled;}
			bool IsSeparatingAxisEnabled() {return mySeparatingAxisEnabled;}
			
			void ComputeSeparatingAxis();
			sfp::SeparatingAxis& GetSeparatingAxis() {return *mySeparatingAxis;}
			
			// //
			void SetPosition(const sf::Vector2f& position) {myPosition=position;}
			void Move(const sf::Vector2f& move) {myPosition+=move;}
			
			void SetRotation(float rotation) {myRotation=rotation;}
			void Rotate(float rotation) {myRotation+=rotation;}
			
			void SetCenter(const sf::Vector2f&);
			
			const sf::Vector2f& GetPosition() {return myPosition;}
			float GetRotation() {return myRotation;}
			const sf::Vector2f& GetCenter() {return myCenter;}
			
			
			sf::Vector2f ToGlobal(const sf::Vector2f&);
			sf::Vector2f ToLocal(const sf::Vector2f&);
			
			#ifdef SFML_GRAPHICS_ENABLED
		private:
			sf::Drawable* myDrawable;
		public:
			Object(sf::Shape&);
			Object(sf::Sprite&);
			Object(sf::Drawable&);
			
			Object(sf::Shape&, const sf::Vector2f&);
			Object(sf::Sprite&, const sf::Vector2f&);
			Object(sf::Drawable&, const sf::Vector2f&);
			
			void SetShape(sf::Shape&);
			void SetSprite(sf::Sprite&);
			void SetDrawable(sf::Drawable&);
			
			void SetShape(sf::Shape&, const sf::Vector2f&){} //FIXME!!
			void SetSprite(sf::Sprite&, const sf::Vector2f&){}
			void SetDrawable(sf::Drawable&, const sf::Vector2f&){}
			
			sf::Drawable* GetDrawable() {return myDrawable;}
			void RemoveDrawable() {myDrawable=NULL;}
			#endif
	};
		
} // Namespace


#endif


