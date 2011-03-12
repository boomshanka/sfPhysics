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


