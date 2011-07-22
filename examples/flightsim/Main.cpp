#include "Sim.hpp"

int main()
{
	Simulator* sim = new Simulator();
	
	sim->Run();
	
	delete sim;
	return 0;
}


