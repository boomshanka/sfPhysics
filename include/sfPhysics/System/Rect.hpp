#ifndef SFPHYSICS_RECT_HPP
#define SFPHYSICS_RECT_HPP


#ifdef SFML_ENABLED
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Rect.hpp>
#else
#include <sfPhysics/SFML_System/Vector2.hpp>
#include <sfPhysics/SFML_System/Rect.hpp>
#endif



namespace sfp
{
	
	template <typename T>
	class Rect : public sf::Rect<T>
	{
		public:
			Rect();
			Rect(T left, T top, T width, T height);
			Rect(const Vector2<T>& position, const Vector2<T>& size);
			Rect(const sf::Rect<T>& rect);
			
			
	};
	
	

	#include <sfPhysics/System/Rect.inl>


	// Create typedefs for the most common types
	typedef Rect<int>   IntRect;
	typedef Rect<float> FloatRect;
	
	
} // namespace


#endif // SFPHYSICS_RECT_HPP


