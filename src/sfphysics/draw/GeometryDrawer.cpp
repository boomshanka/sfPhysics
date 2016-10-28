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


#include <sfphysics/draw/GeometryDraw.hpp>

#include <SFML/Graphics/Transform.hpp>


sfp::GeometryDraw::GeometryDraw(const sfp::linef& l, const sf::Color& color)
{
	// TODO: infinite lines
	m_vertice = sf::VertexArray(sf::Lines, 2);
	
	m_vertice[0].color = color;
	m_vertice[0].position = static_cast<const sf::Vector2f&>(l.first_point);
	m_vertice[1].color = color;
	m_vertice[1].position = static_cast<const sf::Vector2f&>(l.second_point);
}


sfp::GeometryDraw::GeometryDraw(const sfp::vector2f& vector, const sfp::vector2f& pos, const sf::Color& color)
{
	m_vertice = sf::VertexArray(sf::Lines, 6);
	
	m_vertice[0].color = color;
	m_vertice[0].position = static_cast<const sf::Vector2f&>(pos);
	m_vertice[1].color = color;
	m_vertice[1].position = static_cast<const sf::Vector2f&>(pos + vector);
}

sfp::GeometryDraw::GeometryDraw(const sfp::boxf& b, const sf::Color& color)
{
	m_vertice = sf::VertexArray(sf::LinesStrip, 5);
	
	m_vertice[0].color = color;
	m_vertice[0].position = static_cast<const sf::Vector2f&>(b.lowerPoint());
	m_vertice[1].color = color;
	m_vertice[1].position = sf::Vector2f(b.lowerPoint().x, b.upperPoint().y);
	m_vertice[2].color = color;
	m_vertice[2].position = static_cast<const sf::Vector2f&>(b.upperPoint());
	m_vertice[3].color = color;
	m_vertice[3].position = sf::Vector2f(b.upperPoint().x, b.lowerPoint().y);
	m_vertice[4].color = color;
	m_vertice[4].position = static_cast<const sf::Vector2f&>(b.lowerPoint());
}



void sfp::GeometryDraw::draw(sf::RenderWindow& window, const transformf& scenetransform) const
{
	// draw
	window.draw(m_vertice, static_cast<sf::Transform>(scenetransform));
}


