#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

#include "Physics.hpp"


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Physics Test");
	window.UseVerticalSync(true);
	
	sf::Event event;
	const sf::Input& Input = window.GetInput();
	int mouse_x, mouse_y;
	
	
	sf::Shape shape, bottom;
	
	//sfp::Object pShape(shape); sfp::Object pBottom(bottom); sfp::Object pBalken(balken);
	
	shape.AddPoint(0, -50,  sf::Color(255, 0, 0),     sf::Color(0, 128, 128));
	shape.AddPoint(50, 0,   sf::Color(255, 85, 85),   sf::Color(0, 128, 128));
	shape.AddPoint(50, 70,  sf::Color(255, 170, 170), sf::Color(0, 128, 128));
	shape.AddPoint(0, 30,  sf::Color(255, 255, 255), sf::Color(0, 128, 128));
	shape.AddPoint(-50, 70, sf::Color(255, 170, 170), sf::Color(0, 128, 128));
	shape.AddPoint(-50, 0,  sf::Color(255, 85, 85),   sf::Color(0, 128, 128));
	
	bottom.AddPoint(0, 0,  sf::Color(0, 200, 0),   sf::Color(0, 0, 200));
	bottom.AddPoint(0, 30,  sf::Color(0, 200, 0),   sf::Color(0, 0, 200));
	bottom.AddPoint(800, 30,  sf::Color(0, 200, 0),   sf::Color(0, 0, 200));
	bottom.AddPoint(800, 0,  sf::Color(0, 200, 0),   sf::Color(0, 0, 200));
	
	bottom.SetPosition(0,500);
	shape.SetPosition(300,200);
	
	sfp::Object object(shape);
	
	sfp::Collision collision;
	sfp::CollisionEvent collisionevent;
	sfp::Environment world;
	
	world.AddObject(object);
	
	bool up(false), right(false), left(false);
	
	sf::Clock frametime;
	unsigned int frames=0;

	
	while (window.IsOpened()) // Window Loop //
	{
		world.ReceiveFrameTime();
		
		while(window.GetEvent(event))
		{
			if (event.Type == sf::Event::Closed) window.Close();
			
			if (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::A) ;//world.SetGravity(5+world.GetGravity());
			if (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Q) ;//world.SetGravity(world.GetGravity()-5);
		}
		
		if(Input.IsKeyDown(sf::Key::Up)) object.SetImpulse(object.GetImpulse()+sf::Vector2f(0,-1400*sfp::Time::ElapsedTime));
		if(Input.IsKeyDown(sf::Key::Down)) object.SetImpulse(object.GetImpulse()+sf::Vector2f(0,500*sfp::Time::ElapsedTime));
		if(Input.IsKeyDown(sf::Key::Right)) object.SetImpulse(object.GetImpulse()+sf::Vector2f(350*sfp::Time::ElapsedTime,0));
		if(Input.IsKeyDown(sf::Key::Left)) object.SetImpulse(object.GetImpulse()+sf::Vector2f(-350*sfp::Time::ElapsedTime,0));
		
		mouse_x=Input.GetMouseX();
		mouse_y=Input.GetMouseY();
		
		// End of Events and Inputs
		
		//Frames
		++frames;
		if(frametime.GetElapsedTime()>=1)
		{
			std::cerr<<frames<<"\n";
			frametime.Reset();
			frames=0;
		}
		
		// Play God
		world.RenderGravity();
		
		while(collision.GetCollision(collisionevent))
		{
		
		}
		
		world.MoveObjects();
		
		//Draw
		window.Draw(shape);
		window.Draw(bottom);
		
		window.Display();
		window.Clear(sf::Color(0, 0, 150));
	} // Window Loop //
}


