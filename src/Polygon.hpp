#ifndef POLYGON_HPP
#define POLYGON_HPP


#include "SFML_Graphics.hpp"
#ifdef SFML_GRAPHICS_ENABLED
#include <SFML/Graphics.hpp>
#endif

#include <SFML/System/Vector2.hpp>

#include <vector>


namespace sfp
{
	enum PolygonType
	{
		Shape = 0,
		Rectangle,
		Line,
		Circle
	};
	
	
	class Polygon
	{
		friend class Object;
		
		private:
			PolygonType myPolygonType;
			std::vector<sf::Vector2f> myPoints;
			
			float myRadius;
		public:
			Polygon();
			
			void AddPoint(float x, float y) {AddPoint(sf::Vector2f(x,y));}
			void AddPoint(const sf::Vector2f& vec) {myPoints.push_back(vec);}
			
			void SetPointPosition(int index, float x, float y) {SetPointPosition(index,sf::Vector2f(x,y));}
			void SetPointPosition(int index, const sf::Vector2f& vec) {myPoints[index]=vec;}
			
			int GetPointCount() {return myPoints.size();}
			const sf::Vector2f& GetPoint(int index) {return myPoints[index];}
			
			
			PolygonType GetPolygonType() {return myPolygonType;}
			
			static Polygon Line(); //
			static Polygon Rectangle();
			static Polygon Circle();
			
	};

} // namespace

#endif


