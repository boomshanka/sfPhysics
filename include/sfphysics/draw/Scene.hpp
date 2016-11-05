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

#include <sfphysics/geometry/vector2.hpp>
#include <sfphysics/geometry/angle.hpp>
#include <sfphysics/geometry/transformation.hpp>

#include <sfphysics/draw/Drawable.hpp>

#include <SFML/Graphics/RenderWindow.hpp>


namespace sfp
{
	class Scene
	{
		public:
			Scene(sf::RenderWindow& window, const vector2f& size_scene, const vector2f& size_window);
			~Scene();
			
			void size_scene(const vector2f& size);
			void size_scene(const vector2f& size, vector2f center);
			const vector2f& size_scene() const;
			
			void center_scene(const vector2f& center);
			const vector2f& center_scene() const;
			
			void rotation_scene(const anglef& angle);
			const anglef& rotation_scene() const;
			
			
			void size_window(const vector2f& size);
			void size_window(const vector2f& size, vector2f center);
			const vector2f& size_window() const;
			
			void center_window(const vector2f& center);
			const vector2f& center_window() const;
			
			// transformation functions
			vector2f transformToScene(const vector2f& windowCoord) const;
			vector2f transformToWindow(const vector2f& sceneCoord) const;
			
			
			void draw(const sfp::Drawable& drawable);
			
		private:
			sf::RenderWindow& m_window;
			
			vector2f m_size_scene;
			vector2f m_center_scene;
			anglef m_angle_scene;
			
			vector2f m_size_window;
			vector2f m_center_window;
			
			mutable float m_scale;
			
			mutable bool m_transform_updated;
			mutable transformf m_transform;
			mutable transformf m_inverseTransform;
			
			void update_transformation() const;
	};
}


