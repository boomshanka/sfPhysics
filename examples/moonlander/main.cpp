#define SFML_ENABLED

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

#include <sfPhysics/System.hpp>



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
	
	sfp::Object* pCircle1 = new sfp::Object(circle1, sfp::Shape::Circle(sf::Vector2f(1,1),1),50);
	sfp::Object* pCircle2 = new sfp::Object(circle2, sfp::Shape::Circle(sf::Vector2f(1,1),1),50);
	sfp::Object* pCircle3 = new sfp::Object(circle3, sfp::Shape::Circle(sf::Vector2f(1,1),1),50);
	sfp::Object* pCircle4 = new sfp::Object(circle4, sfp::Shape::Circle(sf::Vector2f(1,1),1),50);
	
	sfp::Object* plane1 = new sfp::Object(sfp::Shape::Plane(sf::Vector2f(0,0), sfp::Vector2f(0,1)));
	sfp::Object* plane2 = new sfp::Object(sfp::Shape::Plane(sf::Vector2f(0,0), sfp::Vector2f(1,0)));
	sfp::Object* plane3 = new sfp::Object(sfp::Shape::Plane(sf::Vector2f(0,0), sfp::Vector2f(-1,0)));
	sfp::Object* plane4 = new sfp::Object(sfp::Shape::Plane(sf::Vector2f(0,0), sfp::Vector2f(0,-1)));
	plane3->SetPosition(sf::Vector2f(16,12));
	plane4->SetPosition(sf::Vector2f(16,12));
	
	sfp::Collision collision;
	sfp::CollisionEvent collisionevent;
	sfp::Environment* world = new sfp::Environment();
	
	world->SetLengthFactor(50);
	world->SetGravity(sf::Vector2f(0,0));
	
	world->AddObject(*pCircle1);
	world->AddObject(*pCircle2);
	world->AddObject(*pCircle3);
	world->AddObject(*pCircle4);
	
	collision.AddObject(*pCircle1);
	collision.AddObject(*pCircle2);
	collision.AddObject(*pCircle3);
	collision.AddObject(*pCircle4);
	
	collision.AddObject(*plane1);
	collision.AddObject(*plane2);
	collision.AddObject(*plane3);
	collision.AddObject(*plane4);
	
	pCircle1->SetVelocity(sf::Vector2f(5,2));
	pCircle2->SetVelocity(sf::Vector2f(5,-2));
	pCircle3->SetVelocity(sf::Vector2f(-5,2));
	pCircle4->SetVelocity(sf::Vector2f(-5,-2));
	
	pCircle1->SetDensity(3);
	pCircle2->SetDensity(2);
	pCircle3->SetDensity(1);
	pCircle4->SetDensity(0.5);
	
	pCircle1->SetRestitution(1);
	pCircle2->SetRestitution(1);
	pCircle3->SetRestitution(1);
	pCircle4->SetRestitution(1);
	
	plane1->SetRestitution(1);
	plane2->SetRestitution(1);
	plane3->SetRestitution(1);
	plane4->SetRestitution(1);
	
	
	while (window.IsOpened()) // Window Loop //
	{
		world->UpdateFrameTime(window.GetFrameTime());
		
		while(window.GetEvent(event))
		{
			if (event.Type == sf::Event::Closed) window.Close();
			
			if (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::A) world->SetGravity(world->GetGravity()+sf::Vector2f(0,2));
			if (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Q) world->SetGravity(world->GetGravity()-sf::Vector2f(0,2));
		}
		
	//	if(Input.IsKeyDown(sf::Key::Up)) pCircle.AddImpulse(sf::Vector2f(0,-126*window.GetFrameTime()));
	//	if(Input.IsKeyDown(sf::Key::Down)) pCircle.AddImpulse(sf::Vector2f(0,63*window.GetFrameTime()));
	//	if(Input.IsKeyDown(sf::Key::Right)) pCircle.AddImpulse(sf::Vector2f(63*window.GetFrameTime(),0));
	//	if(Input.IsKeyDown(sf::Key::Left)) pCircle.AddImpulse(sf::Vector2f(-63*window.GetFrameTime(),0));
		
		std::cout<<pCircle1->GetVelocity().GetForce()<<"\n";
		
		while(collision.PollCollision(collisionevent))
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
		
//		std::cout<<pCircle1.GetImpulse().GetForce()-pCircle2.GetImpulse().GetForce()-pCircle3.GetImpulse().GetForce()-pCircle4.GetImpulse().GetForce()<<"\n";
		
		
		// Play God
		world->RenderGravity();
		
		
		world->MoveObjects();
		
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
	
	delete plane1;
	delete plane2;
	delete plane3;
	delete plane4;
	
	delete pCircle1;
	delete pCircle2;
	delete pCircle3;
	delete pCircle4;
	
	delete world;
		
	return 0;
}
