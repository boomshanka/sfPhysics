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


#include <iostream>
#include <ostream>

#include <sfphysics/geometry.hpp>


namespace Color
{
	enum Code {
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_BLUE     = 34,
        FG_DEFAULT  = 39,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_BLUE     = 44,
        BG_DEFAULT  = 49
    };
    
     std::ostream& operator<<(std::ostream& os, Code code) {
		#ifdef __linux__
        return os << "\033[" << static_cast<int>(code) << "m";
        #else
        return os;
        #endif
    }
}

int main()
{
	std::cout << "This is " << Color::FG_RED << "red" << Color::FG_DEFAULT << "!\n";
	
	sfp::transformf trafo;
	
	trafo.translate(sfp::vector2f(1,1));
	std::cout << trafo.transform(sfp::vector2f(0,0)) << std::endl;
	trafo.invert();
	std::cout << trafo.transform(sfp::vector2f(1,1)) << std::endl;
	
	std::cin.clear();
	std::cin.get();
	
	
	return 0;
}
