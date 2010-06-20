#ifndef OBJECTS_HPP
#define OBJECTS_HPP


#include "SFML_Graphics.hpp"
#include "Polygon.hpp"
#include "Physicable.hpp"

#include "SAT.hpp"

#include <vector>
#include <iostream>//
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
			bool mySeparatingAxisEnabled;
			sfp::SeparatingAxis* mySeparatingAxis;
		public:
			Object();
			~Object();
			
			void ComputeArea() {sfp::Physicable::ComputeArea(sfp::Polygon::myPoints);}
			
			void EnableSeparatingAxis(bool enabled) {mySeparatingAxisEnabled=enabled;}
			bool IsSeparatingAxisEnabled() {return mySeparatingAxisEnabled;}
			
			void ComputeSeparatingAxis();
			sfp::SeparatingAxis& GetSeparatingAxis() {return *mySeparatingAxis;}
			
			sf::Vector2f ToGlobal(const sf::Vector2f&);
			sf::Vector2f ToLocal(const sf::Vector2f&);
			
			#ifdef SFML_GRAPHICS_ENABLED
		private:
			sf::Drawable* myDrawable;
		public:
			Object(sf::Shape&);
			
			
			sf::Drawable* GetDrawable() {return myDrawable;}
			void RemoveDrawable() {myDrawable=NULL;}
			#endif
	};
		
} // Namespace


#endif


