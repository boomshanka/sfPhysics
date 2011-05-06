#define SFML_ENABLED

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

#include <sfPhysics/System.hpp>


#include <unistd.h>



int main()
{
//	fork();
	
//	0°		→	1,0
//	90°		↓	0,1
//	180°	←	-1,0
//	270°	↑	0,-1
//	360°	→	1,0
	
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Physics Test");
	window.EnableVerticalSync(true);
	
	sf::Event event;
	const sf::Input& Input = window.GetInput();
	int mouse_x, mouse_y;
	
	
	sf::Shape* shape1 = new sf::Shape();
	sf::Shape* shape = new sf::Shape();
	
	shape1->AddPoint(-50, 50,  sf::Color(255, 85, 85),   sf::Color(0, 128, 128));
	shape1->AddPoint(50, 50, sf::Color(255, 85, 85), sf::Color(0, 128, 128));
	shape1->AddPoint(50, -50,  sf::Color(255, 170, 170), sf::Color(0, 128, 128));
	shape1->AddPoint(-50, -50,   sf::Color(255, 170, 170),   sf::Color(0, 128, 128));
	
	shape->AddPoint(-50, 50,  sf::Color(0, 0, 255),   sf::Color(255, 255, 0));
	shape->AddPoint(50, 50, sf::Color(0, 0, 255), sf::Color(255, 255, 0));
	shape->AddPoint(50, -50,  sf::Color(0, 0, 255), sf::Color(255, 255, 0));
	shape->AddPoint(-50, -50,   sf::Color(0, 0, 255),   sf::Color(255, 255, 0));
	
	sf::Shape* shape2 = new sf::Shape(*shape1);
	sf::Shape* shape3 = new sf::Shape(*shape1);
	sf::Shape* shape4 = new sf::Shape(*shape1);
	sf::Shape* shape5 = new sf::Shape(*shape1);
	
	shape1->SetPosition(600,550);
	shape2->SetPosition(600,440);
	shape3->SetPosition(600,330);
	shape4->SetPosition(600,220);
	shape5->SetPosition(600,110);
	shape->SetPosition(25,550);
	
	sfp::Object* pShape1 = new sfp::Object(*shape1, 50);
	sfp::Object* pShape2 = new sfp::Object(*shape2, 50);
	sfp::Object* pShape3 = new sfp::Object(*shape3, 50);
	sfp::Object* pShape4 = new sfp::Object(*shape4, 50);
	sfp::Object* pShape5 = new sfp::Object(*shape5, 50);
	sfp::Object* object = new sfp::Object(*shape, 50);
	
	
	sfp::Object* plane1 = new sfp::Object(sfp::Shape::Plane(sf::Vector2f(0,0),sf::Vector2f(0,-1)));
	sfp::Object* plane2 = new sfp::Object(sfp::Shape::Plane(sf::Vector2f(0,0),sf::Vector2f(-1,0)));
	sfp::Object* plane3 = new sfp::Object(sfp::Shape::Plane(sf::Vector2f(0,0),sf::Vector2f(1,0)));
	sfp::Object* plane4 = new sfp::Object(sfp::Shape::Plane(sf::Vector2f(0,0),sf::Vector2f(0,1)));
	plane1->SetPosition(sf::Vector2f(16,12));
	plane2->SetPosition(sf::Vector2f(16,0));
	plane3->SetPosition(sf::Vector2f(0,0));
	
	sfp::Collision* collision = new sfp::Collision();
	sfp::CollisionEvent collisionevent;
	sfp::Environment world;
	
	world.SetLengthFactor(50);
	world.SetGravity(sf::Vector2f(0,10));
	world.SetTimeFactor(0);
	
	world.AddObject(object);
	world.AddObject(pShape1);
	world.AddObject(pShape2);
	world.AddObject(pShape3);
	world.AddObject(pShape4);
	world.AddObject(pShape5);
	
	collision->AddObject(pShape1);
	collision->AddObject(pShape2);
	collision->AddObject(pShape3);
	collision->AddObject(pShape4);
	collision->AddObject(pShape5);
	collision->AddObject(object);
	collision->AddObject(plane1);
	collision->AddObject(plane2);
	collision->AddObject(plane3);
	collision->AddObject(plane4);
	
	pShape1->SetRestitution(0.1);
	pShape2->SetRestitution(0.1);
	pShape3->SetRestitution(0.1);
	pShape4->SetRestitution(0.1);
	pShape5->SetRestitution(0.1);
	plane1->SetRestitution(0.1);
	plane2->SetRestitution(0.1);
	plane3->SetRestitution(0.1);
	plane4->SetRestitution(0.1);
	object->SetRestitution(0.1);
	
	sf::Clock frametime;
	unsigned int frames=0;
	
	
	while (window.IsOpened()) // Window Loop //
	{
		world.UpdateFrameTime(window.GetFrameTime());
		
		// Play God
		world.RenderGravity();
		
		while(collision->PollCollision(collisionevent))
		{
			
			switch(collisionevent.CollisionType)
			{
				case sfp::PreciseCollision:
					collision->CollisionResponse(collisionevent);
					break;
				
				default:
					break;
			}
		}
		
		
		while(window.PollEvent(event))
		{
			if (event.Type == sf::Event::Closed) window.Close();
			
			if (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::A) world.SetGravity(world.GetGravity()+sf::Vector2f(0,2));
			if (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Q) world.SetGravity(world.GetGravity()-sf::Vector2f(0,2));
			
			if (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::S) world.SetTimeFactor(1);
		}
		
		if(Input.IsKeyDown(sf::Key::Up)) object->AddImpulse(sf::Vector2f(0,-100*window.GetFrameTime()));
		if(Input.IsKeyDown(sf::Key::Down)) object->AddImpulse(sf::Vector2f(0,75*window.GetFrameTime()));
		if(Input.IsKeyDown(sf::Key::Right)) object->AddImpulse(sf::Vector2f(75*window.GetFrameTime(),0));
		if(Input.IsKeyDown(sf::Key::Left)) object->AddImpulse(sf::Vector2f(-75*window.GetFrameTime(),0));
		
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
		
		world.MoveObjects();
		
		
		//Draw
		window.Draw(*shape);
		window.Draw(*shape1);
		window.Draw(*shape2);
		window.Draw(*shape3);
		window.Draw(*shape4);
		window.Draw(*shape5);
		
		window.Display();
		window.Clear(sf::Color(0, 175, 255));
		
	} // Window Loop //
	
	delete collision;
	
	delete plane1;
	delete plane2;
	delete plane3;
	delete plane4;
	delete pShape1;
	delete pShape2;
	delete pShape3;
	delete pShape4;
	delete pShape5;
	
	delete object;
	
	delete shape;
	delete shape1;
	delete shape2;
	delete shape3;
	delete shape4;
	delete shape5;
	
	#define HAU return
	#define WOLFRAM 0
	#define D ;
	
	HAU WOLFRAM ;D
}


