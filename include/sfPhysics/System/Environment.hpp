#ifndef SFPHYSICS_ENVIRONMENT_HPP
#define SFPHYSICS_ENVIRONMENT_HPP


#include <sfPhysics/System/Objects.hpp>

#include <list>

#ifdef SFML_ENABLED
#include <sfPhysics/SFML_Graphics.hpp>
#endif 



namespace sfp
{
	class Environment
	{
		private:
			std::list<sfp::Object*> myObjects; //list oder vector
			
			sf::Vector2f myGravity;
			float myTimefactor;
			float myLengthfactor;
			
			float myFrameTime;
		public:
			Environment();
			~Environment();
			
			void UpdateFrameTime(float time) {myFrameTime=time;}
			float GetFrameTime() const {return myFrameTime;}
			
			void SetTimeFactor(float timefactor) {myTimefactor=timefactor;}
			float GetTimeFactor() const {return myTimefactor;}
			
			void SetLengthFactor(float lengthfactor) {myLengthfactor=lengthfactor;}
			float GetLengthFactor() const {return myLengthfactor;}
			
			const sf::Vector2f& GetGravity() const {return myGravity;}
			void SetGravity(const sf::Vector2f& gravity) {myGravity=gravity;}
			
			void AddObject(sfp::Object& newobject) {myObjects.push_back(&newobject);}
			
			unsigned int GetObjectCount() const {return myObjects.size();}
			
			sfp::Object& GetObject(unsigned int index); //FIXME
			
			void RemoveObject(unsigned int index); // {myObjects.erase(index);}
			void RemoveObject(sfp::Object& object) {myObjects.remove(&object);}
			
			void RenderGravity();
			
			void MoveObjects(bool moovedrawables=true);
			
			#ifdef SFML_ENABLED
			void MoveDrawables();
			#endif
	};
	
} // namespace sfp


#endif // SFPHYSICS_ENVIRONMENT_HPP


