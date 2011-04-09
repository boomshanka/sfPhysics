/******************************************************************************
 **	sfPhysics - A simple 2D physics engine
 ** Copyright (C) 2011  Olaf Vogt aka Boomshanka
 ** 
 ** This program is free software; you can redistribute it and/or modify it
 ** under the terms of the GNU General Public License as published by the Free
 ** Software Foundation; either version 3 of the License, or (at your option)
 ** any later version. 
 ** 
 ** This program is distributed in the hope that it will be useful, but WITHOUT
 ** ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 ** FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 ** more details. 
 ** 
 ** You should have received a copy of the GNU General Public License along
 ** with this program; if not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************/


#ifndef SFPHYSICS_OBJECTS_HPP
#define SFPHYSICS_OBJECTS_HPP


#include <sfPhysics/SFML_Graphics.hpp>

#include <sfPhysics/System/ShapeManager.hpp>
#include <sfPhysics/System/Physicable.hpp>

#include <sfPhysics/System/Box.hpp>


#include <vector>
#include <stack>
#include <utility>



namespace sfp
{
	class Object : public ShapeManager, public Physicable
	{
		private:
			sf::Vector2f myPosition;
			sf::Vector2f myCenter;
			float myRotation;
			
			sfp::FloatBox myLocalBox;
			
			bool myIsFixed;
			
			std::stack<std::pair<sf::Vector2f, sf::Vector2f> > myIntersection;
		public:
			Object();
			Object(const Shape&);
			~Object();
			
			void SetShape(const Shape&);
			
			// //
			void SetPosition(const sf::Vector2f& position) {myPosition=position;}
			void Move(const sf::Vector2f& move) {myPosition+=move;}
			
			void SetRotation(float rotation) {myRotation=rotation;}
			void Rotate(float rotation) {myRotation+=rotation;}
			
			void SetCenter(const sf::Vector2f&);
			
			const sf::Vector2f& GetPosition() const {return myPosition;}
			float GetRotation() const {return myRotation;}
			const sf::Vector2f& GetCenter() const {return myCenter;}
			
			sf::Vector2f ToGlobal(const sf::Vector2f&) const;
			sf::Vector2f ToLocal(const sf::Vector2f&) const;
			
			const sfp::FloatBox& GetLocalBox();
			sfp::FloatBox GetBoundingBox();
			
			
			void Impulse(const sfp::Vector2f& position, sfp::Vector2f impulse) {Impulse(position, impulse, impulse.GetForce());}
			void Impulse(sfp::Vector2f position, sfp::Vector2f normal, float impulse);
			//Ist getimpulse möglich?
			
			sfp::Vector2f GetMovement(sfp::Vector2f position, const sfp::Vector2f& normal) const;
			
			bool IsFixed() {return myIsFixed;}
			void Fix(bool fix) {myIsFixed=fix;}
			
			void AddIntersection(const sf::Vector2f& first, const sf::Vector2f& second) {myIntersection.push(std::make_pair(first, second));}
			std::stack<std::pair<sf::Vector2f, sf::Vector2f> >& GetIntersection() {return myIntersection;}
			
			void Update();
			
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


