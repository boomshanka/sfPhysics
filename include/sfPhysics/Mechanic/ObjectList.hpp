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


#ifndef SFPHYSICS_OBJECTLIST_HPP
#define SFPHYSICS_OBJECTLIST_HPP


#include <sfPhysics/Mechanic/Objects.hpp>

#include <list>

#include <cstddef>



namespace sfp
{

	class ObjectList
	{
		protected:
			std::list<sfp::Object*> myObjectList;
		
		public:
			ObjectList() {}
			virtual ~ObjectList() {}
		
			void AddObject(sfp::Object* object) {myObjectList.push_back(object);}
		
			void EraseObject(std::list<sfp::Object*>::iterator& it) {myObjectList.erase(it);}
			void RemoveObject(sfp::Object* object) {myObjectList.remove(object);}
		
			size_t GetObjectCount() const {return myObjectList.size();}
		
		//	std::list<sfp::Object*>::const_iterator
	};

} // namespace


#endif  // SFPHYSICS_OBJECTLIST_HPP


