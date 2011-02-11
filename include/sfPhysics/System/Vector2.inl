/*Foo!*/
//	0°		→	1,0
//	90°		↓	0,1
//	180°	←	-1,0
//	270°	↑	0,-1
//	360°	→	1,0



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
inline sfp::Vector2<T>::Vector2(const sf::Vector2<T>& vec)
{
	sf::Vector2<T>::x=vec.x;
	sf::Vector2<T>::y=vec.y;
}


template <typename T>
inline T sfp::Vector2<T>::GetForce() const
{
	return std::sqrt(sf::Vector2<T>::x*sf::Vector2<T>::x + sf::Vector2<T>::y*sf::Vector2<T>::y);
}



template <typename T>
inline T sfp::Vector2<T>::GetForce(float direction) const
{
	float force=std::cos(direction*M_PI/180.f)*sf::Vector2<T>::x;
	force+=std::sin(direction*M_PI/180.f)*sf::Vector2<T>::y;
	
	return force;
}



template <typename T>
inline float sfp::Vector2<T>::GetDirection() const // Liefert Werte zw 0° und °360
{
	if(sf::Vector2<T>::y<0)
		return std::atan2(sf::Vector2<T>::y, sf::Vector2<T>::x) * 180.f/M_PI + 360;
	
	return std::atan2(sf::Vector2<T>::y, sf::Vector2<T>::x) * 180.f/M_PI; //Werte zw -180° und 180°
}



template <typename T>
inline void sfp::Vector2<T>::SetForce(T force)
{
	float direction=GetDirection();
	
	sf::Vector2<T>::x=std::cos(direction*M_PI/180.f)*force;
	sf::Vector2<T>::y=std::sin(direction*M_PI/180.f)*force;
}


template <typename T>
inline void sfp::Vector2<T>::SetForce(T force, float direction) //FIXME: Ist die funktion richtig? andere mögliche bugs suchen.
{
	sf::Vector2<T>::x=std::cos(direction*M_PI/180.f)*force;
	sf::Vector2<T>::y=std::sin(direction*M_PI/180.f)*force;
}



template <typename T>
inline void sfp::Vector2<T>::SetDirection(float direction)
{
	SetForce(GetForce(), direction);
}



template <typename T>
inline void sfp::Vector2<T>::AddForce(T force)
{
	float direction=GetDirection();
	
	sf::Vector2<T>::x+=std::cos(direction*M_PI/180.f)*force;
	sf::Vector2<T>::y+=std::sin(direction*M_PI/180.f)*force;
}


template <typename T>
inline void sfp::Vector2<T>::AddForce(T force, float direction)
{
	sf::Vector2<T>::x+=std::cos(direction*M_PI/180.f)*force;
	sf::Vector2<T>::y+=std::sin(direction*M_PI/180.f)*force;
}



template <typename T>
inline void sfp::Vector2<T>::Normalize()
{
	*this/=GetForce();
}



template <typename T>
inline float sfp::Vector2<T>::DotProduct(const sf::Vector2<T>& vector) const
{
	return sf::Vector2<T>::x*vector.x + sf::Vector2<T>::y*vector.y;
}


template <typename T>
inline float sfp::Vector2<T>::CrossProduct(const sf::Vector2<T>& vector) const
{
	return sf::Vector2<T>::x*vector.y - sf::Vector2<T>::y*vector.x;
}



template <typename T>
inline sfp::Vector2<T> sfp::Vector2<T>::GetNormal() const
{
	return sfp::Vector2<T>(-sf::Vector2<T>::y, sf::Vector2<T>::x);
}





template <typename T>
inline sfp::Vector2<T> operator *(const sfp::Vector2<T>& left, const sfp::Vector2<T>& right)
{
	return sfp::Vector2<T>(left.x*right.x, left.y*right.y);
}


template <typename T>
inline sfp::Vector2<T>& operator *=(sfp::Vector2<T>& left, const sfp::Vector2<T>& right)
{
	left.x*=right.x;
	left.y*=right.y;
	
	return left;
}


template <typename T>
inline sfp::Vector2<T> operator /(const sfp::Vector2<T>& left, const sfp::Vector2<T>& right)
{
	return sfp::Vector2<T>(left.x/right.x, left.y/right.y);
}


template <typename T>
inline sfp::Vector2<T>& operator /=(sfp::Vector2<T>& left, const sfp::Vector2<T>& right)
{
	left.x/=right.x;
	left.y/=right.y;
	
	return left;
}



