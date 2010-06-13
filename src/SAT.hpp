#ifndef SAP_HPP
#define SAP_HPP

#include "Objects.hpp"

#include <queue>
#include <utility>


namespace sfp
{

	class SeparatingAxis
	{
		private:
			std::queue<std::pair<sf::Vector2f, sf::Vector2f> > myAxis;
		public:
			SeparatingAxis() {;}
			SeparatingAxis(sfp::Object& object) {ComputeSeperatingAxix(object);}
			
			~SeparatingAxis() {;}
			
			void ComputeSeperatingAxix(sfp::Object&);
			
			
		protected:
			void AddAx(const sf::Vector2f& first, const sf::Vector2f& second) {myAxis.push(std::make_pair(sf::Vector2f(-first.y,first.x), sf::Vector2f(-second.y,second.x)));}
	};

}


#endif


