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


#include <sfphysics/draw/Scene.hpp>

#include <iostream>


sfp::Scene::Scene(sf::RenderWindow& window, const vector2f& size_scene, const vector2f& size_window) :
m_window(window),
m_size_scene(size_scene),
m_center_scene(size_scene / 2.f),
m_angle_scene(anglef::from_degrees(0)),
m_size_window(size_window),
m_center_window(size_window / 2.f),
m_transform_updated(false)
{
	
}


sfp::Scene::~Scene()
{
	
}


void sfp::Scene::size_scene(const vector2f& size)
{
	m_size_scene = size;
	m_transform_updated = false;
}

void sfp::Scene::size_scene(const vector2f& size, vector2f center)
{
	m_size_scene = size;
	m_center_scene = center;
	m_transform_updated = false;
}

const sfp::vector2f& sfp::Scene::size_scene() const
{
	return m_size_scene;
}


void sfp::Scene::center_scene(const vector2f& center)
{
	m_center_scene = center;
	m_transform_updated = false;
}

const sfp::vector2f& sfp::Scene::center_scene() const
{
	return m_center_scene;
}


void sfp::Scene::rotation_scene(const anglef& angle)
{
	m_angle_scene = angle;
	m_transform_updated = false;
}

const sfp::anglef& sfp::Scene::rotation_scene() const
{
	return m_angle_scene;
}


	
void sfp::Scene::size_window(const vector2f& size)
{
	m_size_window = size;
	m_transform_updated = false;
}

void sfp::Scene::size_window(const vector2f& size, vector2f center)
{
	m_size_window = size;
	m_center_window = center;
	m_transform_updated = false;
}

const sfp::vector2f& sfp::Scene::size_window() const
{
	return m_size_window;
}


void sfp::Scene::center_window(const vector2f& center)
{
	m_center_window = center;
	m_transform_updated = false;
}

const sfp::vector2f& sfp::Scene::center_window() const
{
	return m_center_window;
}


sfp::vector2f sfp::Scene::transformToScene(const sfp::vector2f& windowCoord) const
{
	return m_inverseTransform.transform(windowCoord);
}

sfp::vector2f sfp::Scene::transformToWindow(const sfp::vector2f& sceneCoord) const
{
	return m_transform.transform(sceneCoord);
}


void sfp::Scene::draw(const sfp::Drawable& drawable)
{
	if (!m_transform_updated)
	{
		update_transformation();
	}
	
	drawable.draw(m_window, m_transform);
}


void sfp::Scene::update_transformation() const
{
	m_transform.clear();
	
	if ((m_size_window.x / m_size_scene.x) != (m_size_window.y / m_size_scene.y))
	{
		std::cout << "sfp::Scene warning: Scene size and window view have different ratios";
	}
	m_scale = m_size_window.x / m_size_scene.x;
	
	m_transform.translate(m_center_window);
	m_transform.scale(vector2f(m_scale, m_scale));
	m_transform.rotate(-m_angle_scene);
	m_transform.translate(-m_center_scene);
	m_inverseTransform = m_transform.get_inverse();
		
	m_transform_updated = true;
}

