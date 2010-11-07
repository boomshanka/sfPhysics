#ifndef POLYGONMANAGER_HPP
#define POLYGONMANAGER_HPP

#include <sfPhysics/Polygon.hpp>

#include <vector>


namespace sfp
{

	class PolygonManager : public Polygon
	{
		friend class Object;
		
		private:
			std::vector<Polygon> myConvexPolygons;
			
		public:
			PolygonManager();
			
			// Funktionen von Polygon
			
			inline void AddPoint(float x, float y) {AddPoint(sf::Vector2f(x,y));}
			void AddPoint(const sf::Vector2f&);
			
			inline void SetPointPosition(unsigned int index, float x, float y) {SetPointPosition(index,sf::Vector2f(x,y));}
			void SetPointPosition(unsigned int, const sf::Vector2f&);
			
			inline int GetPointCount() const {return Polygon::GetPointCount();}
			inline const sf::Vector2f& GetPoint(unsigned int index) const {return Polygon::GetPoint(index);}
			
			// Funktionen von PolManager
			
			unsigned int GetConvexPolygonCount() const {return myConvexPolygons.size();}
			const Polygon& GetConvexPolygon(unsigned int index) const {return myConvexPolygons[index];}
			
			void AddConvexPolygon(const Polygon& pol) {myConvexPolygons.push_back(pol);}
			void SetConvexPolygon(unsigned int index, const Polygon& polygon) {myConvexPolygons[index]=polygon;}
			void RemoveConvexPolygon(unsigned int index) {myConvexPolygons.erase(myConvexPolygons.begin()+index);}
			
			const sf::Vector2f& GetPoint(unsigned int polygon, unsigned int index) const {return myConvexPolygons[polygon].GetPoint(index);}
			
			void SetPolygon(const Polygon&);
			
		protected:
			void ComputeConvexPolygons();
			
	};

} // namespace


#endif	// POLYGONMANAGER_HPP


