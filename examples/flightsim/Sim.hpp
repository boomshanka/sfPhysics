#ifndef SIM_HPP
#define SIM_HPP

#include <SFML/Graphics.hpp>


class Simulator
{
	private:
		sf::RenderWindow myWindow;
		
	public:
		Simulator();
		~Simulator();
		
		void Run();
		void Events();
		void Render();
};


#endif


