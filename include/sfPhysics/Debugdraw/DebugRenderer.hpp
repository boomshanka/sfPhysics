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


#ifndef SFPHYSICS_DEBUGRENDERER_HPP
#define SFPHYSICS_DEBUGRENDERER_HPP

#ifdef SFML_ENABLED


#include <SFML/Graphics/Drawable.hpp>



namespace sfp
{
	class DebugRenderer : public sf::Drawable
	{
		private:
			
			
		public:
			DebugRenderer();
			virtual ~DebugRenderer();
			
			virtual void Render(sf::RenderTarget& target, sf::Renderer& renderer) const = 0;
	};
	
	
} // namespace sfp



#endif // SFML_ENABLED


#endif // SFPHYSICS_DEBUGRENDERER_HPP


