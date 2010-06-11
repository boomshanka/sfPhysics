#ifndef OBJECTS_HPP
#define OBJECTS_HPP


#include "SFML_Graphics.hpp"
#include "Polygon.hpp"
#include "Physicable.hpp"

#include <vector>
#include <cmath> // noch nicht

#include <SFML/System.hpp>
#ifdef SFML_GRAPHICS_ENABLED
#include <SFML/Graphics.hpp>
#endif


#define _USE_MATH_DEFINES


namespace sfp
{
	class Time //FIXME übderdenken
	{
		public:
			static sf::Clock Frametime;	
			static float ElapsedTime;
	};
	


	enum VectorUpdate
	{
		Done=0,
		Speed,
		Impulse
	};
	
	
	
	
	class Object : public Polygon, public Physicable
	{
		private:
			
		public:
			Object();
			
			void ComputeArea() {sfp::Physicable::ComputeArea(sfp::Polygon::myPoints);}
			
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


