#define SFML_ENABLED

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

#include <sfPhysics/System.hpp>



int main()
{
//	0°		→	1,0
//	90°		↓	0,1
//	180°	←	-1,0
//	270°	↑	0,-1
//	360°	→	1,0
	
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Physics Test");
	window.EnableVerticalSync(true);
	
	sf::Image* image = new sf::Image();
	image->LoadFromFile("kreis.png");
	sf::Sprite kreise(*image);
	
	sf::Event event;
	const sf::Input& Input = window.GetInput();
	int mouse_x, mouse_y;
	
	
	sf::Shape shape; sf::Shape* bottom = new sf::Shape();// circle=sf::Shape::Circle(sf::Vector2f(50,50),50,sf::Color::Green),
	sf::Shape circle2=sf::Shape::Circle(sf::Vector2f(50,50),50,sf::Color::White),
	circle3=sf::Shape::Circle(sf::Vector2f(50,50),50,sf::Color::White),
	circle4=sf::Shape::Circle(sf::Vector2f(50,50),50,sf::Color::White),
	circle5=sf::Shape::Circle(sf::Vector2f(50,50),50,sf::Color::White);
	
//	circle.SetPointColor(0,sf::Color::Yellow);
	circle5.SetPointColor(0,sf::Color::Yellow);
//	circle.SetPointColor(1,sf::Color::Yellow);
	circle5.SetPointColor(1,sf::Color::Yellow);
	
	//sfp::Object pShape(shape); sfp::Object pBottom(bottom); sfp::Object pBalken(balken);
	
	shape.AddPoint(-50, 0,  sf::Color(255, 85, 85),   sf::Color(0, 128, 128));
	shape.AddPoint(-50, 70, sf::Color(255, 170, 170), sf::Color(0, 128, 128));
//	shape.AddPoint(0, 30,  sf::Color(255, 255, 255), sf::Color(0, 128, 128)); //Für convex/concav
	shape.AddPoint(50, 70,  sf::Color(255, 170, 170), sf::Color(0, 128, 128));
	shape.AddPoint(50, 0,   sf::Color(255, 85, 85),   sf::Color(0, 128, 128));
	shape.AddPoint(0, -50,  sf::Color(255, 0, 0),     sf::Color(0, 128, 128));
	
	bottom->AddPoint(0, 0,  sf::Color(0, 200, 0),   sf::Color(0, 0, 200));
	bottom->AddPoint(0, 100,  sf::Color(0, 200, 0),   sf::Color(0, 0, 200));
	bottom->AddPoint(800, 100,  sf::Color(0, 200, 0),   sf::Color(0, 0, 200));
	bottom->AddPoint(800, 0,  sf::Color(0, 200, 0),   sf::Color(0, 0, 200));
	
	bottom->SetPosition(400,550);
	shape.SetPosition(400,200);
	kreise.SetPosition(0.5,50);
	circle2.SetPosition(50,250);
	circle3.SetPosition(255,250);
	circle4.SetPosition(152.5,500);
	circle5.SetPosition(400, 50);
	
	
	sfp::Object object(shape,50);
	sfp::Object* foo = new sfp::Object(*bottom,50);
	
	sfp::Object pCircle(kreise, sfp::Shape::Circle(sf::Vector2f(1,1),1),50);
	pCircle.AddConvexShape(sfp::Shape::Circle(sf::Vector2f(3,1),1));
	pCircle.Update();
	//pCircle.SetPosition(sf::Vector2f(3.125,2));
	
	sfp::Object pCircle2(circle2, sfp::Shape::Circle(sf::Vector2f(1,1),1),50);
	sfp::Object pCircle3(circle3, sfp::Shape::Circle(sf::Vector2f(1,1),1),50);
	sfp::Object pCircle4(circle4, sfp::Shape::Circle(sf::Vector2f(1,1),1),50);
	sfp::Object pCircle5(circle5, sfp::Shape::Circle(sf::Vector2f(1,1),1),50);
	foo->GetConvexShape(0).SetShapeType(sfp::Shape::Type::Polygon);
	
	sfp::Object* plane = new sfp::Object(sfp::Shape::Plane(sf::Vector2f(0,0),sf::Vector2f(0,-1)));
	sfp::Object* plane2 = new sfp::Object(sfp::Shape::Plane(sf::Vector2f(0,0),sf::Vector2f(-1,0)));
	sfp::Object* plane3 = new sfp::Object(sfp::Shape::Plane(sf::Vector2f(0,0),sf::Vector2f(1,0)));
	plane->SetPosition(sf::Vector2f(16,12));
	plane2->SetPosition(sf::Vector2f(6.1,0));
	plane3->SetPosition(sf::Vector2f(0,0));
	
	sfp::Collision* collision = new sfp::Collision();
	sfp::CollisionEvent collisionevent;
	sfp::Environment world;
	
	world.SetLengthFactor(50);
	world.SetGravity(sf::Vector2f(0,10));
	world.SetTimeFactor(0);
	
	world.AddObject(&object);
	world.AddObject(&pCircle);
	world.AddObject(&pCircle2);
	world.AddObject(&pCircle3);
	world.AddObject(&pCircle4);
	world.AddObject(&pCircle5);
	world.AddObject(plane);
	world.AddObject(plane2);
	world.AddObject(plane3);
	
	collision->AddObject(&object);
//	collision->AddObject(foo);
	collision->AddObject(&pCircle5);
	collision->AddObject(&pCircle4);
	collision->AddObject(&pCircle3);
	collision->AddObject(&pCircle);
	collision->AddObject(&pCircle2);
	collision->AddObject(plane);
//	collision->AddObject(plane2);
	collision->AddObject(plane3);
	
	pCircle2.SetDensity(1);
	pCircle.SetDensity(1);
	
	pCircle.SetRestitution(0.5);
	pCircle2.SetRestitution(0.6);
	pCircle3.SetRestitution(0.6);
	pCircle4.SetRestitution(0.4);
	pCircle5.SetRestitution(0.4);
	plane->SetRestitution(0.3);
	plane2->SetRestitution(0.6);
	plane3->SetRestitution(0.6);
	foo->SetRestitution(0.5);
	object.SetRestitution(0.4);
	
	pCircle.SetDynamicFriction(0.5);
	pCircle2.SetDynamicFriction(0.5);
	pCircle3.SetDynamicFriction(0.5);
	pCircle4.SetDynamicFriction(0.5);
	pCircle5.SetDynamicFriction(0.8);
	plane->SetDynamicFriction(0.5);
	plane2->SetDynamicFriction(0.5);
	plane3->SetDynamicFriction(0.5);
	foo->SetDynamicFriction(0.5);
	object.SetDynamicFriction(0.5);
	
	sf::Clock frametime;
	unsigned int frames=0;
	
	pCircle2.Fix(true);
	pCircle3.Fix(true);
	pCircle4.Fix(true);
	
	foo->Fix(true);
	
	object.SetRotation(45);
	
	pCircle.SetRotation(90);
	pCircle.SetRotationVelocity(500);
	
	pCircle5.SetRotationVelocity(100);
	
	while (window.IsOpened()) // Window Loop //
	{
//		std::cout<<"-\n";
		
		world.UpdateFrameTime(window.GetFrameTime());
		
		
		world.RenderGravity();
		
		while(collision->PollCollision(collisionevent))
		{
			
			switch(collisionevent.CollisionType)
			{
				case sfp::PreciseCollision:
//					if(collisionevent.GetFirstObject().GetDrawable()!=NULL)
//						collisionevent.GetFirstObject().GetDrawable()->SetColor(sf::Color::Red);
//					if(collisionevent.GetSecondObject().GetDrawable()!=NULL)
//						collisionevent.GetSecondObject().GetDrawable()->SetColor(sf::Color::Red);
					
					collision->CollisionResponse(collisionevent);
					break;
				
				default:
					//collisionevent.GetFirstObject().GetDrawable()->SetColor(sf::Color::White);
					//collisionevent.GetSecondObject().GetDrawable()->SetColor(sf::Color::White);
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
		
		if(Input.IsKeyDown(sf::Key::Up)) pCircle.AddImpulse(sf::Vector2f(0,-126.f * window.GetFrameTime()/1000.f));
		if(Input.IsKeyDown(sf::Key::Down)) pCircle.AddImpulse(sf::Vector2f(0,63.f * window.GetFrameTime()/1000.f));
		if(Input.IsKeyDown(sf::Key::Right)) pCircle.AddImpulse(sf::Vector2f(63.f * window.GetFrameTime()/1000.f,0));
		if(Input.IsKeyDown(sf::Key::Left)) pCircle.AddImpulse(sf::Vector2f(-63.f * window.GetFrameTime()/1000.f,0));
		
		//FIXME Test
		//pCircle.AddRotationVelocity(-pCircle.GetRotationVelocity()*0.1*window.GetFrameTime());
//		pCircle.Impulse(sfp::Vector2f(0,1),sfp::Vector2f(0,-1),M_PI/3.f);
		
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
		
		
		world.MoveObjects();
		
		
		//Draw
		window.Draw(shape);
		window.Draw(kreise);
		window.Draw(circle2);
		window.Draw(circle3);
		window.Draw(circle4);
		window.Draw(circle5);
//		window.Draw(*bottom);
		
		window.Display();
		window.Clear(sf::Color(0, 0, 150));
		
		shape.SetColor(sf::Color::White);
		bottom->SetColor(sf::Color::White);
		kreise.SetColor(sf::Color::White);
		circle2.SetColor(sf::Color::White);
		circle3.SetColor(sf::Color::White);
		circle4.SetColor(sf::Color::White);
	} // Window Loop //
	
	delete image;
	
	delete collision;
	
	delete plane;
	delete plane2;
	delete plane3;
	delete foo;
	delete bottom;
	
	#define HAU return
	#define WOLFRAM 0
	#define D ;
	
	HAU WOLFRAM ;D
}


