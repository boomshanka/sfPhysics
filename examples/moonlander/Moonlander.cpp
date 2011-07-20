#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <sfPhysics/System.hpp>



int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Moonlander - sfPhysics");
	window.EnableVerticalSync(true);
	
	sf::Event event;
	
	sf::Shape* sGround = new sf::Shape(sf::Shape::Rectangle(0,0,800,100,sf::Color(142,43,43)));
	sf::Shape * sRocket = new sf::Shape();
	sRocket->AddPoint(-50, 0,  sf::Color(255, 85, 85),   sf::Color(0, 128, 128));
	sRocket->AddPoint(-50, 70, sf::Color(255, 170, 170), sf::Color(0, 128, 128));
	sRocket->AddPoint(0, 30,   sf::Color(255, 255, 255), sf::Color(0, 128, 128)); //Für convex/concav
	sRocket->AddPoint(50, 70,  sf::Color(255, 170, 170), sf::Color(0, 128, 128));
	sRocket->AddPoint(50, 0,   sf::Color(255, 85, 85),   sf::Color(0, 128, 128));
	sRocket->AddPoint(0, -50,  sf::Color(255, 0, 0),     sf::Color(0, 128, 128));
	
	
	sfp::Shape pShape;
	pShape.AddPoint(sf::Vector2f(-1, 0));
	pShape.AddPoint(sf::Vector2f(-1, 1.4));
	pShape.AddPoint(sf::Vector2f(0, 0.6));
	pShape.AddPoint(sf::Vector2f(0, -1));
	pShape.SetShapeType(sfp::Shape::Type::Polygon);
	
	sfp::Object* pGround = new sfp::Object(*sGround, sfp::Shape::Plane(sf::Vector2f(0,0), sfp::Vector2f(0, -1)));
	sfp::Object* pRocket = new sfp::Object(*sRocket, pShape, 50);
	
	pShape = sfp::Shape();
	pShape.AddPoint(sf::Vector2f(0, 0.6));
	pShape.AddPoint(sf::Vector2f(1, 1.4));
	pShape.AddPoint(sf::Vector2f(1, 0));
	pShape.AddPoint(sf::Vector2f(0, -1));
	pShape.SetShapeType(sfp::Shape::Type::Polygon);
	pRocket->AddConvexShape(pShape);
	pRocket->Update();
	
	
	pGround->SetPosition(sf::Vector2f(0,10));
	pRocket->SetPosition(sf::Vector2f(8,2));
	
	pRocket->SetDensity(2);
	
	pGround->SetRestitution(0.2);
	pRocket->SetRestitution(0.2);
	
	pGround->SetDynamicFriction(0.8);
	pRocket->SetDynamicFriction(0.8);
	pGround->SetStaticFriction(1);
	pRocket->SetStaticFriction(1);
	
	
	sfp::Environment* world = new sfp::Environment();
	sfp::CollisionManager* collision = new sfp::CollisionManager();
	sfp::CollisionEvent collisionevent;
	
	world->SetLengthFactor(50);
	world->SetGravity(sf::Vector2f(0,10));
	
	world->AddObject(pGround);
	world->AddObject(pRocket);
	
//	collision->AddObject(pGround);
	collision->AddObject(pRocket);
	collision->AddObject(pGround);//
	
	while (window.IsOpened()) // Window Loop //
	{
		world->UpdateFrameTime(window.GetFrameTime());
		
		while(window.PollEvent(event))
		{
			if (event.Type == sf::Event::Closed) window.Close();
		}
		
		sfp::Vector2f vec(0, -150);
		vec.Rotate(pRocket->GetRotation());
		if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Right)) pRocket->AddRotationImpulse(10.f * window.GetFrameTime()/1000.f);
		if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Left)) pRocket->AddRotationImpulse(-10.f * window.GetFrameTime()/1000.f);
		
		if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Up)) pRocket->Impulse(sf::Vector2f(0,00), vec * static_cast<float>(window.GetFrameTime())/1000.f);
		
		
		world->RenderGravity();
		
		collision->UpdateCollisions();
		
		world->MoveObjects();
		
		
		//Draw
		window.Draw(*sGround);
		window.Draw(*sRocket);
		
		window.Display();
		window.Clear(sf::Color(10, 10, 60));
		
	} // Window Loop //
	
	delete sGround;
	delete sRocket;
	
	delete pGround;
	delete pRocket;
	
	delete world;
	delete collision;
		
	return 0;
}



