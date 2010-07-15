#ifndef SFP_VECTOR2_HPP
#define SFP_VECTOR2_HPP


#include <SFML/System/Vector2.hpp>
#include <cmath>


#define _USE_MATH_DEFINES


namespace sfp
{

	template <typename T>
	class Vector2 : public sf::Vector2<T>
	{
		public:
			Vector2();
			Vector2(T x, T y);
			Vector2(sf::Vector2<T> vec);

			T GetForce();
			float GetDirection();

			void SetForce(T force);
			void SetForce(T force, float direction);
			void SetDirection(float direction);

			void AddForce(T force);
			void AddForce(T force, float direction);
	};
	


	#include "Vector2.inl"

	// Define the most common types
	typedef Vector2<int>   Vector2i;
	typedef Vector2<float> Vector2f;

	
} // namespace


#endif // SFP_VECTOR2_HPP


