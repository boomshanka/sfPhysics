#ifndef SFPHYSICS_VECTOR2_HPP
#define SFPHYSICS_VECTOR2_HPP


#ifdef SFML_ENABLED
#include <SFML/System/Vector2.hpp>
#else
#include <sfPhysics/SFML_System/Vector2.hpp>
#endif


#define _USE_MATH_DEFINES
#include <cmath>



namespace sfp
{

	template <typename T>
	class Vector2 : public sf::Vector2<T>
	{
		public:
			Vector2();
			Vector2(T x, T y);
			Vector2(const sf::Vector2<T>& vec);

			T GetForce() const;
			T GetForce(float) const;
			float GetDirection() const;

			void SetForce(T force);
			void SetForce(T force, float direction);
			void SetDirection(float direction);

			void AddForce(T force);
			void AddForce(T force, float direction);
			void Normalize();
			
			float DotProduct(const sf::Vector2<T>&) const;
			float CrossProduct(const sf::Vector2<T>&) const;
			
			sfp::Vector2<T> GetNormal() const;
	};
	
	
	template <typename T>
	Vector2<T> operator *(const Vector2<T>& left, const Vector2<T>& right);
	
	template <typename T>
	Vector2<T>& operator *=(Vector2<T>& left, const Vector2<T>& right);
	
	template <typename T>
	Vector2<T> operator /(const Vector2<T>& left, const Vector2<T>& right);
	
	template <typename T>
	Vector2<T>& operator /=(Vector2<T>& left, const Vector2<T>& right);
	
	
	
	#include <sfPhysics/System/Vector2.inl>
	
	
	// Define the most common types
	typedef Vector2<int>   Vector2i;
	typedef Vector2<float> Vector2f;
	
		
} // namespace


#endif // SFPHYSICS_VECTOR2_HPP


