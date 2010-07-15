/*Foo!*/

template <typename T>
inline sfp::Vector2<T>::Vector2()
{

}


template <typename T>
inline sfp::Vector2<T>::Vector2(T X, T Y) 
{
	sf::Vector2<T>::x=X;
	sf::Vector2<T>::y=Y;
}


template <typename T>
inline sfp::Vector2<T>::Vector2(sf::Vector2<T> vec)
{
	sf::Vector2<T>::x=vec.x;
	sf::Vector2<T>::y=vec.y;
}


template <typename T>
T sfp::Vector2<T>::GetForce()
{
	return std::sqrt(sf::Vector2<T>::x*sf::Vector2<T>::x + sf::Vector2<T>::y*sf::Vector2<T>::y);
}



template <typename T>
float sfp::Vector2<T>::GetDirection()
{
	if(sf::Vector2<T>::x==0)
	{
		return sf::Vector2<T>::y<0 ? -90 : 90;
	}
	else
	{
		if(sf::Vector2<T>::x<0)
		{
			return sf::Vector2<T>::x<0 ? (std::atan(sf::Vector2<T>::y/sf::Vector2<T>::x)* 180.f / M_PI-180)
										:(std::atan(sf::Vector2<T>::y/sf::Vector2<T>::x)* 180.f / M_PI+180);
		}
		return std::atan(sf::Vector2<T>::y/sf::Vector2<T>::x)* 180.f / M_PI;
	}
} //möglicherweise prüfen?



template <typename T>
void sfp::Vector2<T>::SetForce(T force)
{
	float direction=GetDirection();
	
	sf::Vector2<T>::x=std::cos(direction*M_PI/180.f)*force;
	sf::Vector2<T>::y=std::sin(direction*M_PI/180.f)*force;
}



template <typename T>
void sfp::Vector2<T>::SetForce(T force, float direction) //FIXME: Ist die funktion richtig? andere mögliche bugs suchen. inline vergessen?
{
	sf::Vector2<T>::x=std::cos(direction*M_PI/180.f)*force;
	sf::Vector2<T>::y=std::sin(direction*M_PI/180.f)*force;
}



template <typename T>
void sfp::Vector2<T>::SetDirection(float direction)
{
	SetForce(GetForce(), direction);
}



template <typename T>
void sfp::Vector2<T>::AddForce(T force)
{
	float direction=GetDirection();
	
	sf::Vector2<T>::x+=std::cos(direction*M_PI/180.f)*force;
	sf::Vector2<T>::y+=std::sin(direction*M_PI/180.f)*force;
}


template <typename T>
void sfp::Vector2<T>::AddForce(T force, float direction)
{
	sf::Vector2<T>::x+=std::cos(direction*M_PI/180.f)*force;
	sf::Vector2<T>::y+=std::sin(direction*M_PI/180.f)*force;
}

