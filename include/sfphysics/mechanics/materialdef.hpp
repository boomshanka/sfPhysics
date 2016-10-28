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


#pragma once


namespace sfp
{

	class materialdef
	{
		public:
			materialdef();
			materialdef(const materialdef&);
			materialdef(float density, float restitution, float stat_friction, float dyn_friction);			
			
			float density() const;
			void density(float dens);
						
			float restitution() const;
			void restitution(float res);
			
			float dynamic_friction() const;
			bool dynamic_friction(float dyn);
			
			float static_friction() const;
			bool static_friction(float stat);
			
			bool friction(float stat, float dyn);
			
		private:
			float m_density;
			float m_restitution;
			float m_static_friction;
			float m_dynamic_friction;
	};
	
	
	static materialdef wood;
	static materialdef steel;
	static materialdef aluminium;
	static materialdef stone;
	static materialdef rubber;
	static materialdef soil;
	
}

