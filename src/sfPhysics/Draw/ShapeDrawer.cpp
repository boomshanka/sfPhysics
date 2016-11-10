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


#include <sfPhysics/Draw/ShapeDrawer.hpp>
#include <sfPhysics/Geometry/trigonometry.hpp>
#include <sfPhysics/Geometry/angle.hpp>

#include <limits>


void sfp::DefaultDrawer::createShape(const Shape& shape, const sf::Color& color)
{
	m_color = color;
	shape.accept(*this);
}


void sfp::DefaultDrawer::dispatch(const sfp::CircleShape& shape)
{
	sf::Color filling_color = m_color;
	sf::Color slice_color = sf::Color(120, 120, 120) + m_color;
	sf::Color surrounding_color = sf::Color(0,0,0, m_color.a);
	
	// VertexArray for circle, slice, surrounding line and V-line
	m_vertice = VertexArrayList(3);
	
	// Two more points for center and beginning
	m_vertice[0] = sf::VertexArray(sf::TrianglesFan, m_circle_slice_points + 2);
	// Two more points for center and last point
	m_vertice[1] = sf::VertexArray(sf::TrianglesFan, m_circle_points - m_circle_slice_points + 2);
	// One more point for last point = first point
	m_vertice[2] = sf::VertexArray(sf::LinesStrip, m_circle_points + 1);
	
	// Slice
	m_vertice[0][0].position = shape.center();
	m_vertice[0][0].color = slice_color;
	for (unsigned int i = 0; i < m_circle_slice_points + 1; ++i)
	{
		anglef angle = anglef::from_degrees(360 * i/m_circle_points);
		m_vertice[0][i+1].position = static_cast<const sf::Vector2f&>(shape.center()) +
							  shape.radius() * sf::Vector2f(trigf::sin(angle), trigf::cos(angle));
		m_vertice[0][i+1].color = slice_color;
	}
	// Filling
	m_vertice[1][0].position = shape.center();
	m_vertice[1][0].color = filling_color;
	for (unsigned int i = 0; i < m_circle_points - m_circle_slice_points + 1; ++i)
	{
		anglef angle = anglef::from_degrees(360 * (i + m_circle_slice_points) / m_circle_points);
		m_vertice[1][i+1].position = static_cast<const sf::Vector2f&>(shape.center()) +
							  shape.radius() * sf::Vector2f(trigf::sin(angle), trigf::cos(angle));
		m_vertice[1][i+1].color = filling_color;
	}
	// Circle for surrounding
	for (unsigned int i = 0; i < m_circle_points + 1; ++i)
	{
		anglef angle = anglef::from_degrees(360 * i/m_circle_points);
		m_vertice[2][i].position = static_cast<const sf::Vector2f&>(shape.center()) +
							  shape.radius() * sf::Vector2f(trigf::sin(angle), trigf::cos(angle));
		m_vertice[2][i].color = surrounding_color;
	}
}

void sfp::DefaultDrawer::dispatch(const sfp::PolygonShape& shape)
{
	m_vertice = VertexArrayList(2);
	
	// Two more points for center and last point = first point
	m_vertice[0] = sf::VertexArray(sf::TrianglesFan, shape.pointCount() + 2);
	// For surrounding line, last point = first point
	m_vertice[1] = sf::VertexArray(sf::LinesStrip, shape.pointCount() + 1);
	
	// First point is center
	m_vertice[0][0].position = static_cast<const sf::Vector2f&>(shape.center());
	m_vertice[0][0].color = m_color;
	
	// Loop over all points
	for (unsigned int i = 0; i < shape.pointCount() + 1; ++i)
	{
		if (i != shape.pointCount())
		{
			m_vertice[0][i+1].position = static_cast<const sf::Vector2f&>(shape.point(i));
			m_vertice[1][i].position = static_cast<const sf::Vector2f&>(shape.point(i));
		}
		else
		{
			// Last point, use position of first point
			m_vertice[0][i+1].position = static_cast<const sf::Vector2f&>(shape.point(0));
			m_vertice[1][i].position = static_cast<const sf::Vector2f&>(shape.point(0));
		}
		
		m_vertice[0][i+1].color = m_color;
		m_vertice[1][i].color = sf::Color::Black;
	}
}

void sfp::DefaultDrawer::dispatch(const sfp::RectangleShape& shape)
{
	m_vertice = VertexArrayList(2);
	
	// Filling. Two more points for center and last point = first point
	m_vertice[0] = sf::VertexArray(sf::TrianglesFan, 6);
	// For surrounding line, last point = first point
	m_vertice[1] = sf::VertexArray(sf::LinesStrip, 5);
	
	// center
	m_vertice[0][0].position = static_cast<const sf::Vector2f&>(shape.center());
	m_vertice[0][0].color = m_color;
	
	// corners
	boxf bounds = shape.bounds();
	m_vertice[0][1].position = static_cast<const sf::Vector2f&>(bounds.lowerPoint());
	m_vertice[0][1].color = m_color;
	m_vertice[1][0].position = static_cast<const sf::Vector2f&>(bounds.lowerPoint());
	m_vertice[1][0].color = sf::Color::Black;
	
	m_vertice[0][2].position = sf::Vector2f(bounds.upperPoint().x,bounds.lowerPoint().y);
	m_vertice[0][2].color = m_color;
	m_vertice[1][1].position = sf::Vector2f(bounds.upperPoint().x,bounds.lowerPoint().y);
	m_vertice[1][1].color = sf::Color::Black;
	
	m_vertice[0][3].position = static_cast<const sf::Vector2f&>(bounds.upperPoint());
	m_vertice[0][3].color = m_color;
	m_vertice[1][2].position = static_cast<const sf::Vector2f&>(bounds.upperPoint());
	m_vertice[1][2].color = sf::Color::Black;
	
	m_vertice[0][4].position = sf::Vector2f(bounds.lowerPoint().x,bounds.upperPoint().y);
	m_vertice[0][4].color = m_color;
	m_vertice[1][3].position = sf::Vector2f(bounds.lowerPoint().x,bounds.upperPoint().y);
	m_vertice[1][3].color = sf::Color::Black;
	
	m_vertice[0][5].position = static_cast<const sf::Vector2f&>(bounds.lowerPoint());
	m_vertice[0][5].color = m_color;
	m_vertice[1][4].position = static_cast<const sf::Vector2f&>(bounds.lowerPoint());
	m_vertice[1][4].color = sf::Color::Black;
}

void sfp::DefaultDrawer::dispatch(const sfp::PlaneShape& shape)
{
	// Draw one HUGE rectangle so the plane seems infinite
	m_vertice = VertexArrayList(2);
	
	// Filling. One more point for last point = first point
	m_vertice[0] = sf::VertexArray(sf::TrianglesFan, 5);
	// For upper line
	m_vertice[1] = sf::VertexArray(sf::LinesStrip, 2);
	
	// Upper edges
	sfp::vector2f edge1 = shape.center() - (shape.normal().normal() * m_pseudo_infinity_factor);
	sfp::vector2f edge2 = shape.center() + (shape.normal().normal() * m_pseudo_infinity_factor);
	m_vertice[0][0].position = static_cast<sf::Vector2f>(edge1);
	m_vertice[0][0].color = m_color;
	 // Last point = first point
	m_vertice[0][4].position = static_cast<sf::Vector2f>(edge1);
	m_vertice[0][4].color = m_color;
	m_vertice[1][0].position = static_cast<sf::Vector2f>(edge1);
	m_vertice[1][0].color = sf::Color::Black;
	// Other edge
	m_vertice[0][1].position = static_cast<sf::Vector2f>(edge2);
	m_vertice[0][1].color = m_color;
	m_vertice[1][1].position = static_cast<sf::Vector2f>(edge2);
	m_vertice[1][1].color = sf::Color::Black;
	
	// Lower edges
	edge1 = shape.center() + (( shape.normal().normal() - shape.normal()) * m_pseudo_infinity_factor);
	edge2 = shape.center() + ((-shape.normal().normal() - shape.normal()) * m_pseudo_infinity_factor);
	m_vertice[0][2].position = static_cast<sf::Vector2f>(edge1); 
	m_vertice[0][2].color = m_color;
	
	m_vertice[0][3].position = static_cast<sf::Vector2f>(edge1);
	m_vertice[0][3].color = m_color;
}


void sfp::DefaultDrawer::draw(sf::RenderWindow& window, const transformf& transform) const
{
	for (const sf::VertexArray& vertex : m_vertice)
	{
		window.draw(vertex, static_cast<sf::Transform>(transform));
	}
}

