/******************************************************************************
 **	sfPhysics - A simple 2D physics engine
 ** Copyright (C) 2011  Olaf Vogt aka Boomshanka
 ** 
 ** This program is free software; you can redistribute it and/or modify it
 ** under the terms of the GNU General Public License as published by the Free
 ** Software Foundation; either version 3 of the License, or (at your option)
 ** any later version. 
 ** 
 ** This program is distributed in the hope that it will be useful, but WITHOUT
 ** ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 ** FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 ** more details. 
 ** 
 ** You should have received a copy of the GNU General Public License along
 ** with this program; if not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************/


template <typename T>
inline transformation<T>::transformation() :
m_matrix{{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}}
{

}


template <typename T>
inline transformation<T>::transformation(T a00, T a01, T a02, T a10, T a11, T a12, T a20, T a21, T a22) :
m_matrix{{{a00, a01, a02}, {a10, a11, a12}, {a20, a21, a22}}}
{

}


template <typename T>
inline transformation<T>::transformation(const transformation<T>& trafo)
{
	m_matrix = trafo.m_matrix;
}



template <typename T>
inline transformation<T>& transformation<T>::translate(const vector2<T>& offset)
{
	transformation<T> trafo(1, 0, offset.x,
							0, 1, offset.y,
							0, 0, 1);
							
	return combine(trafo);
}


template <typename T>
inline transformation<T>& transformation<T>::rotate(const angle<T>& angle)
{
	transformation<T> trafo(trig<T>::cos(angle), -trig<T>::sin(angle), 0,
							trig<T>::sin(angle),  trig<T>::cos(angle), 0,
							0, 0, 1);
	
	return combine(trafo);
}


template <typename T>
inline transformation<T>& transformation<T>::rotate(const angle<T>& angle, const vector2<T>& center)
{
	T sin = trig<T>::sin(angle);
	T cos = trig<T>::cos(angle);
	
	transformation<T> trafo(cos, -sin, center.x * (1-cos) + center.y * sin,
							sin,  cos, center.x * (1-cos) - center.y * sin,
							0, 0, 1);
	
	return combine(trafo);
}


template <typename T>
inline transformation<T>& transformation<T>::scale(const vector2<T>& scale)
{
	transformation<T> trafo(scale.x,0, 		0,
							0, 		scale.y,0,
							0,		0,		1);
	
	return combine(trafo);
}



template <typename T>
inline transformation<T> transformation<T>::get_inverse() const
{
	T det =	m_matrix[0][0] * (m_matrix[2][2] * m_matrix[1][1] - m_matrix[2][1] * m_matrix[1][2]) -
			m_matrix[1][0] * (m_matrix[2][2] * m_matrix[0][1] - m_matrix[2][1] * m_matrix[0][2]) +
			m_matrix[2][0] * (m_matrix[1][2] * m_matrix[0][1] - m_matrix[1][1] * m_matrix[0][2]);

    // Compute the inverse if the determinant is not zero
    if (det != 0)
    {
		return transformation<T>((m_matrix[2][2] * m_matrix[1][1] - m_matrix[2][1] * m_matrix[1][2]) / det,
								-(m_matrix[2][2] * m_matrix[0][1] - m_matrix[2][1] * m_matrix[0][2]) / det,
								 (m_matrix[1][2] * m_matrix[0][1] - m_matrix[1][1] * m_matrix[0][2]) / det,
								-(m_matrix[2][2] * m_matrix[1][0] - m_matrix[2][0] * m_matrix[1][2]) / det,
								 (m_matrix[2][2] * m_matrix[0][0] - m_matrix[2][0] * m_matrix[0][2]) / det,
								-(m_matrix[1][2] * m_matrix[0][0] - m_matrix[1][0] * m_matrix[0][2]) / det,
								 (m_matrix[2][1] * m_matrix[1][0] - m_matrix[2][0] * m_matrix[1][1]) / det,
								-(m_matrix[2][1] * m_matrix[0][0] - m_matrix[2][0] * m_matrix[0][1]) / det,
								 (m_matrix[1][1] * m_matrix[0][0] - m_matrix[1][0] * m_matrix[0][1]) / det);
    }
    else
    {
        return transformation<T>();
    }
}


template <typename T>
inline transformation<T>& transformation<T>::invert()
{
	return *this = get_inverse();
}


template <typename T>
inline transformation<T>& transformation<T>::clear()
{
	return *this = transformation<T>();
}


template <typename T>
transformation<T>& transformation<T>::combine(const transformation<T>& right)
{
	const std::array<std::array<T, 3>, 3>& a = m_matrix;
	const std::array<std::array<T, 3>, 3>& b = right.m_matrix;

    *this = transformation<T>(
		a[0][0] * b[0][0] + a[0][1] * b[1][0] + a[0][2] * b[2][0],
		a[0][0] * b[0][1] + a[0][1] * b[1][1] + a[0][2] * b[2][1],
		a[0][0] * b[0][2] + a[0][1] * b[1][2] + a[0][2] * b[2][2],
		a[1][0] * b[0][0] + a[1][1] * b[1][0] + a[1][2] * b[2][0],
		a[1][0] * b[0][1] + a[1][1] * b[1][1] + a[1][2] * b[2][1],
		a[1][0] * b[0][2] + a[1][1] * b[1][2] + a[1][2] * b[2][2],
		a[2][0] * b[0][0] + a[2][1] * b[1][0] + a[2][2] * b[2][0],
		a[2][0] * b[0][1] + a[2][1] * b[1][1] + a[2][2] * b[2][1],
		a[2][0] * b[0][2] + a[2][1] * b[1][2] + a[2][2] * b[2][2]);

    return *this;
}



template <typename T>
inline sfp::vector2<T> transformation<T>::transform(const vector2<T>& point) const
{
	return sfp::vector2<T>(	m_matrix[0][0] * point.x + m_matrix[0][1] * point.y + m_matrix[0][2],
							m_matrix[1][0] * point.x + m_matrix[1][1] * point.y + m_matrix[1][2]);
}


template <typename T>
inline transformation<T>& transformation<T>::operator =(const transformation& right)
{
	m_matrix = right.m_matrix;
}


template <typename T>
inline bool transformation<T>::operator ==(const transformation& right) const
{
	return m_matrix == right.m_matrix;
}


template <typename T>
inline sfp::vector2<T> operator *(const transformation<T>& left, const vector2<T>& right)
{
	return left.transform(right);
}


template <typename T>
inline transformation<T> operator *(const transformation<T>& left, const transformation<T>& right)
{
	return transformation<T>(left).combine(right);
}


template <typename T>
inline transformation<T>& operator *=(transformation<T>& left, const transformation<T>& right)
{
	return left.combine(right);
}


#ifdef SFML_ENABLED

template <typename T>
inline transformation<T>::operator sf::Transform() const
{
	return sf::Transform(
		static_cast<float>(m_matrix[0][0]), static_cast<float>(m_matrix[0][1]), static_cast<float>(m_matrix[0][2]),
		static_cast<float>(m_matrix[1][0]), static_cast<float>(m_matrix[1][1]), static_cast<float>(m_matrix[1][2]),
		static_cast<float>(m_matrix[2][0]), static_cast<float>(m_matrix[2][1]), static_cast<float>(m_matrix[2][2]));
}

#endif

