#include "Sim.hpp"



Simulator::Simulator()
{
	myWindow.Create(sf::VideoMode(1024, 768), "sfPhysics Flightsim", sf::Style::Close);
	myWindow.EnableVerticalSync(true);
}


Simulator::~Simulator()
{
	myWindow.Close();
}



void Simulator::Run()
{
	while(myWindow.IsOpened())
	{
		
		Events();
		
		Render();
	}
}


void Simulator::Events()
{
	sf::Event event;
	
	while(myWindow.PollEvent(event))
	{
		if(event.Type == sf::Event::Closed)
			myWindow.Close();
		
	}
}


void Simulator::Render()
{
	myWindow.Clear();
	
	
	
	myWindow.Display();
}


