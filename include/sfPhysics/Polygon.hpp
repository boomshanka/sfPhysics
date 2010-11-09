#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <sfPhysics/SFML_Graphics.hpp>

#ifdef SFML_GRAPHICS_ENABLED
#include <SFML/Graphics.hpp> //FIXME brauch ich das hier?
#endif

#include <sfPhysics/Vector2.hpp>

#include <vector>


namespace sfp
{
	enum PolygonType
	{
		Shape = 0,
		Rectangle = 1,
//		Line,
		Plane = 3,
		Circle = 4,
		NegCircle =5
	};
	
	
	class Polygon
	{
		friend class Physicable;//FIXME ?
		friend class PolygonManager;
		friend class Object;
		
		private:
			PolygonType myPolygonType;
			std::vector<sf::Vector2f> myPoints;
			
			float myCircleRadius;
			
			sf::Vector2f myCenter;
			float myArea;
			float myInertiaMoment; // Ist unabhängig von der Masse
		public:
			Polygon();
			Polygon(const Polygon&);
			virtual ~Polygon() {}
			
			virtual void AddPoint(float x, float y) {AddPoint(sf::Vector2f(x,y));}
			virtual void AddPoint(const sf::Vector2f& vec) {myPoints.push_back(vec); ComputeArea();}
			
			virtual void SetPointPosition(unsigned int index, float x, float y) {SetPointPosition(index,sf::Vector2f(x,y));}
			virtual void SetPointPosition(unsigned int index, const sf::Vector2f& vec) {myPoints[index]=vec; ComputeArea(); ComputeArea();}
			
			virtual int GetPointCount() const {return myPoints.size();}
			virtual const sf::Vector2f& GetPoint(unsigned int index) const {return myPoints[index];}
			
			virtual PolygonType GetPolygonType() const {return myPolygonType;}
			
			virtual float GetCircleRadius() const {return myCircleRadius;}
			//SetCircleRadius?
			
			
			virtual const sf::Vector2f& GetPolygonCenter() const {return myCenter;}
			virtual float GetPolygonArea() const {return myArea;}
			virtual float GetPolygonInertiaMoment() const {return myInertiaMoment;}
			
			
			
			static Polygon Rectangle();
			static Polygon Line();
			static Polygon Plane();
			static Polygon Circle(const sf::Vector2f&, float);
			
		protected:
			virtual void ComputeArea();
			
			void ComputeShapeArea();
			void ComputeCircleArea();
	};

} // namespace

#endif


