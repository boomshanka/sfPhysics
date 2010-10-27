#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <sfPhysics/Objects.hpp>
#include <sfPhysics/Collision.hpp>

#include <SFML/Graphics.hpp>

#include <iostream>
#include <list>



namespace sfp
{
	class Environment
	{
		private:
			std::list<sfp::Object*> myObjects; //list oder vector
			
			sf::Vector2f myGravity;
			float myTimefactor;
		public:
			Environment();
			~Environment();
			
			void ReceiveFrameTime();
			float GetFrameTime();
			
			void SetTimeFactor(float timefactor) {myTimefactor=timefactor;}
			float GetTimeFactor() {return myTimefactor;}
			
			const sf::Vector2f& GetGravity() {return myGravity;}
			void SetGravity(const sf::Vector2f& gravity) {myGravity=gravity;}
			
			void AddObject(sfp::Object&);
			
			unsigned int GetObjectCount() {return myObjects.size();}
			
			sfp::Object& GetObject(unsigned int index);
			sfp::Object& GetObject(sfp::Object&);
			
			void RemoveObject(unsigned int index);// {myObjects.erase(index);}
			void RemoveObject(sfp::Object& object) {myObjects.remove(&object);}
			
			void RenderGravity();
			
			void MoveObjects(bool moovedrawables=true);
			
			#ifdef SFML_GRAPHICS_ENABLED
			void MoveDrawables();
			#endif
	};
	
} //Namespace sfp


#endif


