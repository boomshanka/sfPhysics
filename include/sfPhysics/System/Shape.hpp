#ifndef SFPHYSICS_SHAPE_HPP
#define SFPHYSICS_SHAPE_HPP


#include <sfPhysics/System/Vector2.hpp>

#include <vector>



namespace sfp
{
	enum ShapeType
	{
		Polygon = 0,
		Rectangle = 1,
//		Line,
		Plane = 3,
		Circle = 4,
		NegCircle = 5
	};
	
	
	class Shape
	{
		friend class ShapeManager;
		friend class Object;
		
		private:
			ShapeType myShapeType;
			std::vector<sf::Vector2f> myPoints;
			
			float myCircleRadius;
			sfp::Vector2f myPlaneNormal;
			
			sf::Vector2f myCenter;
			float myArea;
			float myInertiaMoment; // Ist unabhängig von der Masse
		public:
			Shape();
			Shape(const Shape&);
			virtual ~Shape() {}
			
			virtual void AddPoint(float x, float y) {AddPoint(sf::Vector2f(x,y));}
			virtual void AddPoint(const sf::Vector2f& vec) {myPoints.push_back(vec); ComputeArea();}
			
			virtual void SetPointPosition(unsigned int index, float x, float y) {SetPointPosition(index,sf::Vector2f(x,y));}//FIXME rename SetPoint
			virtual void SetPointPosition(unsigned int index, const sf::Vector2f& vec) {myPoints[index]=vec; ComputeArea(); ComputeArea();}// oder überall Position
			
			virtual int GetPointCount() const {return myPoints.size();}
			virtual const sf::Vector2f& GetPoint(unsigned int index) const {return myPoints[index];}
			
			virtual float GetCircleRadius() const {return myCircleRadius;}
			virtual void SetCircleRadius(float radius) {myCircleRadius=radius;}
			
			virtual const sfp::Vector2f& GetPlaneNormal() const {return myPlaneNormal;}
			virtual void SetPlaneNormal(const sfp::Vector2f& normal) {myPlaneNormal=normal; myPlaneNormal.Normalize();}
			
			virtual ShapeType GetShapeType() const {return myShapeType;}
			virtual void SetShapeType(ShapeType type) {myShapeType=type;}
			
			
			virtual const sf::Vector2f& GetShapeCenter() const {return myCenter;}
			virtual float GetShapeArea() const {return myArea;}
			virtual float GetShapeInertiaMoment() const {return myInertiaMoment;}
			
			
			
			static Shape Rectangle();
			static Shape Line();
			static Shape Plane(const sf::Vector2f&, float);
			static Shape Plane(const sf::Vector2f&, sfp::Vector2f);
			static Shape Circle(const sf::Vector2f&, float);
			
		protected:
			virtual void ComputeArea();
			
			void ComputePolygonArea();
			void ComputeCircleArea();
			
			float ComputeTriangleMoment(const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&, float);
	};

} // namespace

#endif // SFPHYSICS_SHAPE_HPP


