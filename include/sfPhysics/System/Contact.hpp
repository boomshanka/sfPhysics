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


#ifndef SFPHYSICS_CONTACT_HPP
#define SFPHYSICS_CONTACT_HPP


#include <sfPhysics/System/CollisionEvent.hpp>

#include <map>



namespace sfp
{
	class Contact
	{
		public:
			Contact() {frames=5;}
			
			enum ContactType
			{
				FirstContact = 0,
				DynamicContact = 1,
				StaticContact = 2
			} type;
			
			size_t frames;
			bool statcont;
	};
	
	
	class ContactManager
	{
		private:
			std::map<sfp::Object*, std::map<sfp::Object*, sfp::Contact*> > myContacts;
			
		public:
			ContactManager() {}
			~ContactManager();
			
			void ComputeContact(sfp::CollisionEvent&);
			void UpdateContacts();
			
			void SetStaticContact(sfp::Object* first, sfp::Object* second);
			
			Contact* GetContact(sfp::Object* first, sfp::Object* second) {return myContacts[first][second];}
	};

} // namespace



#endif // SFPHYSICS_CONTACT_HPP



