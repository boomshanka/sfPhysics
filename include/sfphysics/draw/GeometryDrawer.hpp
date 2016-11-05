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


#pragma once

#include <sfphysics/draw/Drawable.hpp>

#include <sfphysics/geometry/vector2.hpp>
#include <sfphysics/geometry/line.hpp>
#include <sfphysics/geometry/box.hpp>
#include <sfphysics/geometry/transformation.hpp>

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Color.hpp>


namespace sfp
{
	class GeometryDrawer : public sfp::Drawable
	{
		public:
			GeometryDrawer(const sfp::linef& l, const sf::Color& color = sf::Color::Black);
			GeometryDrawer(const sfp::vector2f& vector, const sfp::vector2f& pos = sfp::vector2f(0,0), const sf::Color& color = sf::Color::Black);
			GeometryDrawer(const sfp::boxf& b, const sf::Color& color = sf::Color::Black);
			
			virtual void draw(sf::RenderWindow& window, const transformf& transform) const;
			
		private:
			sf::VertexArray m_vertice;
	};
}


