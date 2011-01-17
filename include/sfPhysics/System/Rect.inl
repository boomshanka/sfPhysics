/*Foo*/



template <typename T>
inline Rect<T>::Rect()
{

}


template <typename T>
Rect<T>::Rect(T left, T top, T width, T height) :
sf::Rect<T>(left, top, width, height)
{

}


template <typename T>
Rect<T>::Rect(const Vector2<T>& position, const Vector2<T>& size) :
sf::Rect<T>(position, size)
{

}





