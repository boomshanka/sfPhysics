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
sfp::minmax<T>::minmax() : m_init(false)
{

}

template <typename T>
sfp::minmax<T>::minmax(T value) : m_min(value), m_max(value), m_init(true)
{

}
			

template <typename T>
sfp::minmax<T>& sfp::minmax<T>::apply(T value)
{
	if (!m_init)
	{
		m_min = m_max = value;
		m_init = true;
	}
	else
	{
		if (value > m_max)
		{
			m_max = value;
		}
		else if (value < m_min)
		{
			m_min = value;
		}
	}
	
	return *this;
}


template <typename T>
sfp::minmax<T>& sfp::minmax<T>::apply(const sfp::minmax<T>& value)
{
	if (value.m_init)
	{
		if (!m_init)
		{
			m_min = value.m_min;
			m_max = value.m_max;
			m_init = true;
		}
		else
		{
			if (value.m_max > m_max)
			{
				m_max = value.m_max;
			}
			if (value.m_min < m_min)
			{
				m_min = value.m_min;
			}
		}
	}
	
	return *this;
}


template <typename T>
T sfp::minmax<T>::min() const
{
	return m_min;
}

template <typename T>
T sfp::minmax<T>::max() const
{
	return m_max;
}


template <typename T>
bool sfp::minmax<T>::contains(T value) const
{
	if (m_init)
	{
		return (value >= m_min && value <= m_max);
	}
	
	return false;
}


template <typename T>
bool sfp::minmax<T>::intersects(const sfp::minmax<T>& mm) const
{
	if (m_init && mm.m_init)
	{
		// check if number ranges overlap
		if (m_min <= mm.m_max && mm.m_min <= m_max)
		{
			return true;
		}
	}
	
	return false;
}


template <typename T>
bool sfp::minmax<T>::valid() const
{
	return m_init;
}


// ostream operator for output
template <typename T>
std::ostream& operator<<(std::ostream& os, const sfp::minmax<T>& mm)
{
	os << "[" << mm.min() << ", " << mm.max() << "]";
}

