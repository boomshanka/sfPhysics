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

#include <sfPhysics/Draw/Drawable.hpp>
#include <sfPhysics/Draw/ShapeDrawer.hpp>
#include <sfPhysics/Mechanics/Body.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <memory>


namespace sfp
{
	typedef std::vector<sf::VertexArray> VertexArrayList;
	
	class Drawbody : public sfp::Drawable, public sfp::Body
	{
		public:
			Drawbody(const Shape& shape, const sf::Color& color = sf::Color::Red); // TODO: Color default=random and add ShapeDrawer
			~Drawbody();
			
			// TODO: usefull functions for drawbdody
			void color(const sf::Color& color);
			void colorize(const sf::Color& color);
		
		private:
			std::unique_ptr<ShapeDrawer> m_drawer;
			sf::Color m_color;
			
			virtual void draw(sf::RenderWindow& window, const transformf& transform) const;
	};
	
} // namespace



