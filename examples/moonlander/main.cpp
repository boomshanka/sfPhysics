#define SFML_ENABLED

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

#include <sfPhysics/System.hpp>
#include <sfPhysics/Collision.hpp>


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Physics Test");
	window.EnableVerticalSync(true);
	
	sf::Event event;
	const sf::Input& Input = window.GetInput();
	
	
	sf::Shape	circle1=sf::Shape::Circle(sf::Vector2f(50,50),50,sf::Color::Green),
				circle2=sf::Shape::Circle(sf::Vector2f(50,50),50,sf::Color::White),
				circle3=sf::Shape::Circle(sf::Vector2f(50,50),50,sf::Color::White),
				circle4=sf::Shape::Circle(sf::Vector2f(50,50),50,sf::Color::White);
	
	circle1.SetPointColor(0,sf::Color::Yellow);
	circle2.SetPointColor(0,sf::Color::Yellow);
	circle1.SetPointColor(1,sf::Color::Yellow);
	circle2.SetPointColor(1,sf::Color::Yellow);
	
	circle1.SetPosition(50,50);
	circle2.SetPosition(50,550);
	circle3.SetPosition(750,50);
	circle4.SetPosition(750,550);
	
	sfp::Object pCircle1(circle1, sfp::Shape::Circle(sf::Vector2f(1,1),1),50);
	sfp::Object pCircle2(circle2, sfp::Shape::Circle(sf::Vector2f(1,1),1),50);
	sfp::Object pCircle3(circle3, sfp::Shape::Circle(sf::Vector2f(1,1),1),50);
	sfp::Object pCircle4(circle4, sfp::Shape::Circle(sf::Vector2f(1,1),1),50);
	
	sfp::Collision collision;
	sfp::CollisionEvent collisionevent;
	sfp::Environment world;
	
	world.SetLengthFactor(50);
	world.SetGravity(sf::Vector2f(0,0));
	
	world.AddObject(pCircle1);
	world.AddObject(pCircle2);
	world.AddObject(pCircle3);
	world.AddObject(pCircle4);
	
	collision.AddObject(pCircle1);
	collision.AddObject(pCircle2);
	collision.AddObject(pCircle3);
	collision.AddObject(pCircle4);
	
	pCircle1.SetSpeed(sf::Vector2f(4.7,2));
	pCircle2.SetSpeed(sf::Vector2f(5,-2));
	pCircle3.SetSpeed(sf::Vector2f(-5,2.3));
	pCircle4.SetSpeed(sf::Vector2f(-5.1,-2));
	
	while (window.IsOpened()) // Window Loop //
	{
		world.UpdateFrameTime(window.GetFrameTime());
		
		while(window.GetEvent(event))
		{
			if (event.Type == sf::Event::Closed) window.Close();
			
			if (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::A) world.SetGravity(world.GetGravity()+sf::Vector2f(0,2));
			if (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Q) world.SetGravity(world.GetGravity()-sf::Vector2f(0,2));
		}
		
	//	if(Input.IsKeyDown(sf::Key::Up)) pCircle.AddImpulse(sf::Vector2f(0,-126*window.GetFrameTime()));
	//	if(Input.IsKeyDown(sf::Key::Down)) pCircle.AddImpulse(sf::Vector2f(0,63*window.GetFrameTime()));
	//	if(Input.IsKeyDown(sf::Key::Right)) pCircle.AddImpulse(sf::Vector2f(63*window.GetFrameTime(),0));
	//	if(Input.IsKeyDown(sf::Key::Left)) pCircle.AddImpulse(sf::Vector2f(-63*window.GetFrameTime(),0));
		
		
		// Play God
		world.RenderGravity();
		
		while(collision.GetCollision(collisionevent))
		{
			
			switch(collisionevent.CollisionType)
			{
				case sfp::PreciseCollision:
				//	collisionevent.GetFirstObject().GetDrawable()->SetColor(sf::Color::Red);
				//	collisionevent.GetSecondObject().GetDrawable()->SetColor(sf::Color::Red);
					
					collision.Bounce(collisionevent);
					break;
				
				default:
					//collisionevent.GetFirstObject().GetDrawable()->SetColor(sf::Color::White);
					//collisionevent.GetSecondObject().GetDrawable()->SetColor(sf::Color::White);
					break;
			}
		}
		
		if(pCircle1.GetPosition().x<1 || pCircle1.GetPosition().x>15)
			pCircle1.SetSpeed(pCircle1.GetSpeed()*sfp::Vector2f(-1,1));
			
		if(pCircle2.GetPosition().x<1 || pCircle2.GetPosition().x>15)
			pCircle2.SetSpeed(pCircle2.GetSpeed()*sfp::Vector2f(-1,1));
		
		if(pCircle3.GetPosition().x<1 || pCircle3.GetPosition().x>15)
			pCircle3.SetSpeed(pCircle3.GetSpeed()*sfp::Vector2f(-1,1));
		
		if(pCircle4.GetPosition().x<1 || pCircle4.GetPosition().x>15)
			pCircle4.SetSpeed(pCircle4.GetSpeed()*sfp::Vector2f(-1,1));
			
		if(pCircle1.GetPosition().y<1 || pCircle1.GetPosition().y>11)
			pCircle1.SetSpeed(pCircle1.GetSpeed()*sfp::Vector2f(1,-1));
			
		if(pCircle2.GetPosition().y<1 || pCircle2.GetPosition().y>11)
			pCircle2.SetSpeed(pCircle2.GetSpeed()*sfp::Vector2f(1,-1));
		
		if(pCircle3.GetPosition().y<1 || pCircle3.GetPosition().y>11)
			pCircle3.SetSpeed(pCircle3.GetSpeed()*sfp::Vector2f(1,-1));
		
		if(pCircle4.GetPosition().y<1 || pCircle4.GetPosition().y>11)
			pCircle4.SetSpeed(pCircle4.GetSpeed()*sfp::Vector2f(1,-1));
		
		
		world.MoveObjects();
		
		//Draw
		window.Draw(circle1);
		window.Draw(circle2);
		window.Draw(circle3);
		window.Draw(circle4);
		
		window.Display();
		window.Clear(sf::Color(130, 0, 0));
		
		circle1.SetColor(sf::Color::White);
		circle2.SetColor(sf::Color::White);
		circle3.SetColor(sf::Color::White);
		circle4.SetColor(sf::Color::White);
	} // Window Loop //
	
	return 0;
}
