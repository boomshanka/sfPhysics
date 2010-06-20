#ifndef SAP_HPP
#define SAP_HPP

#include "Objects.hpp"

#include <queue>


namespace sfp
{
	class Object;

	class SeparatingAxis
	{
		private:
			std::vector<sf::Vector2f> myAxis;
		public:
			SeparatingAxis() {;}
			SeparatingAxis(sfp::Object& object) {ComputeSeperatingAxix(object);}
			
			~SeparatingAxis() {;}
			
			void ComputeSeperatingAxix(sfp::Object&);
			
			int GetAxisCount() {return myAxis.size();}
			sf::Vector2f GetAx(int index) {return myAxis[index];}
			
		protected:
			void AddAx(const sf::Vector2f&, const sf::Vector2f&);
	};

}


#endif


