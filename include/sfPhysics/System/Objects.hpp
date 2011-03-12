#ifndef SFPHYSICS_OBJECTS_HPP
#define SFPHYSICS_OBJECTS_HPP


#include <sfPhysics/SFML_Graphics.hpp>

#include <sfPhysics/System/ShapeManager.hpp>
#include <sfPhysics/System/Physicable.hpp>
#include <sfPhysics/System/SAT.hpp>


#include <vector>



namespace sfp
{
	class SeparatingAxis;
	
	
	class Object : public ShapeManager, public Physicable
	{
		private:
			sf::Vector2f myPosition;
			sf::Vector2f myCenter;
			float myRotation;
			
			sfp::SeparatingAxis* mySeparatingAxis;
			bool mySeparatingAxisEnabled;
			
			float mySatRotation;
			
			bool myIsFixed;
		public:
			Object();
			Object(const Shape&);
			~Object();
			
			// //
			void ComputeArea();//FIXME überlegen, wann sie aufgerufen wird und schauen, ob man bei Shape & ShapeManager aufrufen von ComputeArea sparen kann. Überschreiben prüfen
			void SetShape(const Shape&);
			
			void EnableSeparatingAxis(bool enabled) {mySeparatingAxisEnabled=enabled;}
			bool IsSeparatingAxisEnabled() const {return mySeparatingAxisEnabled;}
			
			void ComputeSeparatingAxis();
			sfp::SeparatingAxis& GetSeparatingAxis() {return *mySeparatingAxis;}
			
			// //
			void SetPosition(const sf::Vector2f& position) {myPosition=position;}
			void Move(const sf::Vector2f& move) {myPosition+=move;}
			
			void SetRotation(float rotation) {myRotation=rotation;}
			void Rotate(float rotation) {myRotation+=rotation;}
			
			void SetCenter(const sf::Vector2f&);
			
			const sf::Vector2f& GetPosition() const {return myPosition;}
			float GetRotation() const {return myRotation;}
			const sf::Vector2f& GetCenter() const {return myCenter;}
			
			sf::Vector2f GetLocalPoint(unsigned int index) const;
			sf::Vector2f GetLocalPoint(unsigned int shape, unsigned int index) const;
			sf::Vector2f GetLocalShapeCenter(unsigned int shape) const;
			
			
			sf::Vector2f ToGlobal(const sf::Vector2f&) const;
			sf::Vector2f ToLocal(const sf::Vector2f&) const;
			
			void Impulse(const sfp::Vector2f& position, sfp::Vector2f impulse) {Impulse(position, impulse, impulse.GetForce());}
			void Impulse(sfp::Vector2f position, sfp::Vector2f normal, float impulse);
			//Ist getimpulse möglich?
			
			sfp::Vector2f GetMovement(const sfp::Vector2f& position) const;
			
			bool IsFixed() {return myIsFixed;}
			void Fix(bool fix) {myIsFixed=fix;}
			
			
			#ifdef SFML_ENABLED //FIXME lengthfactor darf nie null sein!!
		private:
			sf::Drawable* myDrawable;
			float myLengthfactor;
			
		public:
			Object(sf::Shape&, float lengthfactor=1);
			Object(sf::Sprite&, float lengthfactor=1);
			Object(sf::Drawable&, float lengthfactor=1);
			Object(sf::Drawable&, const Shape& shape, float lengthfactor=1);
			
			Object(sf::Shape&, const sf::Vector2f&, float lengthfactor=1);
			Object(sf::Sprite&, const sf::Vector2f&, float lengthfactor=1);
			Object(sf::Drawable&, const sf::Vector2f&, float lengthfactor=1);
			
			void SetShape(sf::Shape&); //FIXME!!
			void SetSprite(sf::Sprite&);
			void SetDrawable(sf::Drawable&);
			
			void SetShape(sf::Shape&, const sf::Vector2f&){} //FIXME!!
			void SetSprite(sf::Sprite&, const sf::Vector2f&){}
			void SetDrawable(sf::Drawable&, const sf::Vector2f&){}
			
			sf::Drawable* GetDrawable() {return myDrawable;}
			void RemoveDrawable() {myDrawable=NULL;}
			
			void SetLengthFactor(float);
			float GetLengthFactor() const {return myLengthfactor;}
			#endif
	};
		
} // Namespace


#endif // SFPHYSICS_OBJECTS_HPP


