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


#include <sfphysics/draw/bodydraw>



sfp::bodydraw::bodydraw(std::shared_ptr<body> drawbody, std::shared_ptr<drawsettings> settings)
:m_body(drawbody), m_drawsettings(settings), m_drawable(NULL)
{

}



void sfp::bodydraw::Draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(m_drawable != NULL)
	{
		target.draw(*m_drawable, states);
	}
}


void sfp::bodydraw::create_shape()
{
	
}



