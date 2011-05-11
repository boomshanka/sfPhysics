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


#ifndef SFPHYSICS_SHAPE_HPP
#define SFPHYSICS_SHAPE_HPP


#include <sfPhysics/System/Vector2.hpp>
#include <sfPhysics/System/SeparatingAxis.hpp>

#include <vector>



namespace sfp
{

	class Shape
	{
		friend class ShapeManager;
		friend class Object;
		
		public:
			struct Type
			{
			enum ShapeType
			{
				Nothing = 0,
				Polygon = 1,
				Rectangle = 2,
//				Line,
				Plane = 4,
				Circle = 5,
				NegCircle = 6,
				Unknown = 9
			};
			};
			
		private:
			Type::ShapeType myShapeType;
		
			std::vector<sf::Vector2f> myPoints;
			
			SeparatingAxis mySeparatingAxis;
			
			float myCircleRadius;
			sfp::Vector2f myPlaneNormal;
			
			sf::Vector2f myCenter;
			float myArea;			
			float myInertiaMoment;	// Ist unabhängig von der Masse
		public:
			Shape();
			Shape(const Shape&);
			virtual ~Shape() {}
			
			virtual void AddPoint(float x, float y) {AddPoint(sf::Vector2f(x,y));}
			virtual void AddPoint(const sf::Vector2f& vec) {myPoints.push_back(vec); Update();} //FIXME Update aufrufen?
			
			virtual void SetPoint(size_t index, float x, float y) {SetPoint(index,sf::Vector2f(x,y));}
			virtual void SetPoint(size_t index, const sf::Vector2f& vec) {myPoints[index]=vec; Update();} //FIXME s.o.
			
			virtual size_t GetPointCount() const {return myPoints.size();}
			virtual const sf::Vector2f& GetPoint(size_t index) const {return myPoints[index];}
			
			virtual float GetCircleRadius() const {return myCircleRadius;}
			virtual void SetCircleRadius(float radius) {myCircleRadius=radius;}
			
			virtual const sfp::Vector2f& GetPlaneNormal() const {return myPlaneNormal;}
			virtual void SetPlaneNormal(const sfp::Vector2f& normal) {myPlaneNormal=normal; myPlaneNormal.Normalize();}
			
			virtual Type::ShapeType GetShapeType() const {return myShapeType;}
			virtual void SetShapeType(Type::ShapeType newtype) {myShapeType=newtype;}
			
			
			virtual const sf::Vector2f& GetShapeCenter() const {return myCenter;}
			virtual float GetShapeArea() const {return myArea;}
			virtual float GetShapeInertiaMoment() const {return myInertiaMoment;}
			
			const SeparatingAxis& GetSeparatingAxis() const {return mySeparatingAxis;}
			
			
			static Shape Rectangle();
			static Shape Line();
			static Shape Plane(const sf::Vector2f&, float);
			static Shape Plane(const sf::Vector2f&, sfp::Vector2f);
			static Shape Circle(const sf::Vector2f&, float);
			
		protected:
			void Update();
			
		private:
			void ComputePolygonArea();
			void ComputeCircleArea();
			
			float ComputeTriangleMoment(const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&, float);
	};

} // namespace


#endif // SFPHYSICS_SHAPE_HPP


