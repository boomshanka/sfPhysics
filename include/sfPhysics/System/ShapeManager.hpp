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


#ifndef SFPHYSICS_SHAPEMANAGER_HPP
#define SFPHYSICS_SHAPEMANAGER_HPP


#include <sfPhysics/System/Shape.hpp>

#include <vector>



namespace sfp
{

	class ShapeManager : public Shape
	{	
		private:
			std::vector<Shape> myConvexShapes;
			
		public:
			ShapeManager();
			//copyconstructor
			
			// Funktionen von Shape
			
			inline void AddPoint(float x, float y) {AddPoint(sf::Vector2f(x,y));}
			void AddPoint(const sf::Vector2f&);
			
			inline void SetPointPosition(unsigned int index, float x, float y) {SetPointPosition(index,sf::Vector2f(x,y));}
			void SetPointPosition(unsigned int, const sf::Vector2f&); //FIXME auch Poisition weg
			
			inline int GetPointCount() const {return Shape::GetPointCount();}
			inline const sf::Vector2f& GetPoint(unsigned int index) const {return Shape::GetPoint(index);}
			
			inline float GetCircleRadius() const {return Shape::GetCircleRadius();}
			inline void SetCircleRadius(float radius) {Shape::SetCircleRadius(radius);}
			
			const sfp::Vector2f& GetPlaneNormal() const {return Shape::GetPlaneNormal();}
			void SetPlaneNormal(const sfp::Vector2f& normal) {Shape::SetPlaneNormal(normal);}
			
			inline ShapeType GetShapeType() const {return Shape::GetShapeType();}
			inline void SetShapeType(ShapeType type) {Shape::SetShapeType(type);}
			
			
			inline const sf::Vector2f& GetShapeCenter() const {return Shape::GetShapeCenter();}
			inline float GetShapeArea() const {return Shape::GetShapeArea();}
			inline float GetShapeInertiaMoment() const {return Shape::GetShapeInertiaMoment();}
			
			// Funktionen von PolManager
			
			unsigned int GetConvexShapeCount() const {return myConvexShapes.size();}
			const Shape& GetConvexShape(unsigned int index) const {return myConvexShapes[index];}
			
			void AddConvexShape(const Shape& pol) {myConvexShapes.push_back(pol); ComputeArea();}
			void SetConvexShape(unsigned int index, const Shape& Shape) {myConvexShapes[index]=Shape; ComputeArea();}
			void RemoveConvexShape(unsigned int index) {myConvexShapes.erase(myConvexShapes.begin()+index); ComputeArea();}
			
			const sf::Vector2f& GetPoint(unsigned int shape, unsigned int index) const {return myConvexShapes[shape].GetPoint(index);}
			
			void SetShape(const Shape&);
			
		protected:
			void ComputeConvexShapes();
			void ComputeArea();
	};

} // namespace


#endif	// SFPHYSICS_SHAPEMANAGER_HPP


