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

#include <sfphysics/geometry/transformation.hpp>
#include <sfphysics/geometry/circle.hpp>
#include <sfphysics/geometry/polygon.hpp>
#include <sfphysics/geometry/rectangle.hpp>
#include <sfphysics/geometry/plane.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <vector>


namespace sfp
{
	typedef std::vector<sf::VertexArray> VertexArrayList;
	
	class ShapeDrawer : public ShapeDispatcher
	{
	public:
		virtual void createShape(const Shape& shape, const sf::Color& color) = 0;
		virtual void draw(sf::RenderWindow& window, const transformf& transform) const = 0;
	};
	
	
	class DefaultDrawer : public ShapeDrawer
	{
		public:
			DefaultDrawer() {}
			
			void createShape(const Shape& shape, const sf::Color& color);
			
			void dispatch(const CircleShape& shape);
			void dispatch(const PolygonShape& shape);
			void dispatch(const RectangleShape& shape);
			void dispatch(const PlaneShape& shape);
			
			void draw(sf::RenderWindow& window, const transformf& transform) const;
			
		private:
			sf::Color m_color;
			VertexArrayList m_vertice;
			
			const unsigned int m_circle_points = 60;
			const unsigned int m_circle_slice_points = 5;
	};
	
} // namespace



