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

#include <SFML/Graphics.hpp>

#include <sfPhysics/Geometry.hpp>
#include <sfPhysics/Mechanics.hpp>
#include <sfPhysics/Draw.hpp>

#include <iostream>

void drawGrid(sfp::Scene& sc);


int main()
{
	/*
	world
	environment <- gravity and air friction
	
	*/
	sfp::CircleShape circle(1, sfp::vector2f(3,2));
	sfp::PolygonShape polygon;
	sfp::PlaneShape plane(sfp::vector2f(0,-1));
	polygon.addPoint(sfp::vector2f(0,0));
	polygon.addPoint(sfp::vector2f(1,-1));
	polygon.addPoint(sfp::vector2f(2,0));
	polygon.addPoint(sfp::vector2f(2,2));
	polygon.addPoint(sfp::vector2f(0,2));
	sfp::RectangleShape rectangle(sfp::vector2f(7,1));
	
	sfp::Drawbody body1(polygon, sf::Color::Green);
	sfp::Drawbody body2(circle, sf::Color::Blue);
	sfp::Drawbody body3(polygon, sf::Color::Red);
	sfp::Drawbody body4(rectangle, sf::Color(100,100,100));
	sfp::Drawbody body5(plane, sf::Color::Green);
	body1.position(sfp::vector2f(4,3));
	body2.position(sfp::vector2f(1.5,2.5));
	body3.position(sfp::vector2f(14,8));
	body4.position(sfp::vector2f(6,6));
	body5.position(sfp::vector2f(5,11));
	
	body3.rotation(sfp::anglef::from_degrees(15));
	body4.rotation(sfp::anglef::from_degrees(85));
	body5.rotation(sfp::anglef::from_degrees(-5));
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "sfPhysics Collision Detection Example");
	window.setFramerateLimit(60);
	
	sfp::Scene scene(window, sfp::vector2f(16,12), sfp::vector2f(800,600));
	
	sfp::Collider collider;
	
	while (window.isOpen())
	{
		// Event process loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		
		body1.position(scene.transformToScene(sf::Vector2f(sf::Mouse::getPosition(window))));
		
		// rotation
		body1.rotation(body1.rotation() + sfp::anglef::from_degrees(0.5));
		
		// Drawing begins
		window.clear(sf::Color::White);
		
		drawGrid(scene);
		
		// All bodys
		scene.draw(body1);
		scene.draw(body2);
		scene.draw(body3);
		scene.draw(body4);
		scene.draw(body5);
		
		// Bounding box of moving object (changes color when intersects)
		if (body1.bounds().intersects(body2.bounds()) || body1.bounds().intersects(body3.bounds()) ||
			body1.bounds().intersects(body4.bounds()))
		{
			scene.draw(sfp::GeometryDrawer(body1.bounds(), sf::Color::Red));
		}
		else
		{
			scene.draw(sfp::GeometryDrawer(body1.bounds(), sf::Color::Black));
		}
		
		// other bounding boxes
		scene.draw(sfp::GeometryDrawer(body2.bounds()));
		scene.draw(sfp::GeometryDrawer(body3.bounds()));
		scene.draw(sfp::GeometryDrawer(body4.bounds()));
		
		// reset colors
		body2.colorize(sf::Color::White);
		body3.colorize(sf::Color::White);
		body4.colorize(sf::Color::White);
		body5.colorize(sf::Color::White);
		
		// check collisions
		sfp::Contact contact;
		if (collider.collision(body1, body2, contact))
		{
			body2.colorize(sf::Color::Red);
		}
		if (collider.collision(body1, body3, contact))
		{
			body3.colorize(sf::Color::Black);
		}
		if (collider.collision(body1, body4, contact))
		{
			body4.colorize(sf::Color::Blue);
		}
		if (collider.collision(body1, body5, contact))
		{
			body5.colorize(sf::Color::Black);
		}
				
		window.display();
	}
	
	
	return 0;
}


void drawGrid(sfp::Scene& sc)
{
	for (unsigned int i = 0; i < 16; ++i)
		sc.draw(sfp::GeometryDrawer(sfp::linef(sfp::vector2f(i, 0), sfp::vector2f(i, 12)), sf::Color(150,150,150)));
	
	for (unsigned int i = 0; i < 12; ++i)
		sc.draw(sfp::GeometryDrawer(sfp::linef(sfp::vector2f(0, i), sfp::vector2f(16, i)), sf::Color(150,150,150)));
}

