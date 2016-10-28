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


#include <sfphysics/draw/drawbody.hpp>
#include <sfphysics/geometry/circle.hpp>
#include <sfphysics/geometry/polygon.hpp>


sfp::drawbody::drawbody(const sfp::Shape& shape, const sf::Color& color) :
body(shape), m_drawer(new DefaultDrawer()), m_color(color)
{
	m_drawer->createShape(shape, m_color);
}

sfp::drawbody::~drawbody()
{
	
}


void sfp::drawbody::color(const sf::Color& color)
{
	m_color = color;
	m_drawer->createShape(body::bodyshape(), m_color);
}

void sfp::drawbody::colorize(const sf::Color& color)
{
	m_drawer->createShape(body::bodyshape(), color*m_color);
}


void sfp::drawbody::draw(sf::RenderWindow& window, const transformf& scenetransform) const
{
	// apply position and rotation to transformation
	transformf trafo(scenetransform);
	trafo.translate(body::position()).rotate(body::rotation()).translate(-body::center());
	
	// draw
	m_drawer->draw(window, trafo);
}


