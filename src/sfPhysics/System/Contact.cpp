#include <sfPhysics/System/Contact.hpp>


#include <iostream>
sfp::ContactManager::~ContactManager()
{
	for(std::map<sfp::Object*, std::map<sfp::Object*, sfp::Contact*> >::iterator it = myContacts.begin(); it != myContacts.end(); ++it)
	{
		for(std::map<sfp::Object*, sfp::Contact*>::iterator it2 = myContacts[it->first].begin(); it2 != myContacts[it->first].end(); ++it2)
		{
			delete myContacts[it->first][it2->first];
		}
	}
}



void sfp::ContactManager::ComputeContact(sfp::CollisionEvent& event)
{
	if(myContacts[event.first][event.second] == NULL)
	{std::cout<<"first contact\n";
		myContacts[event.first][event.second] = new sfp::Contact();
	}
	else if(myContacts[event.first][event.second]->type == Contact::FirstContact)
	{std::cout<<"dc\n";
		myContacts[event.first][event.second]->type = Contact::DynamicContact;
		myContacts[event.first][event.second]->frames = 3;
	}
	else if(myContacts[event.first][event.second]->type == Contact::DynamicContact)
	{std::cout<<"Dynamic Contact!\n";
		myContacts[event.first][event.second]->frames = 3;
	}
	else if(myContacts[event.first][event.second]->type == Contact::StaticContact)
	{std::cout<<"StaticContact\n";
		myContacts[event.first][event.second]->frames = 3;
	}
}



void sfp::ContactManager::UpdateContacts()
{
	for(std::map<sfp::Object*, std::map<sfp::Object*, sfp::Contact*> >::iterator it = myContacts.begin(); it != myContacts.end(); ++it)
	{
		for(std::map<sfp::Object*, sfp::Contact*>::iterator it2 = myContacts[it->first].begin(); it2 != myContacts[it->first].end(); ++it2)
		{
			--myContacts[it->first][it2->first]->frames;
			
			if(myContacts[it->first][it2->first]->frames == 0)
			{
				delete myContacts[it->first][it2->first];
				myContacts[it->first][it2->first] = NULL;
				myContacts[it->first].erase(it2);
				if(myContacts[it->first].size() == 0)
					myContacts.erase(it);
			}
			else if(myContacts[it->first][it2->first]->type == Contact::StaticContact)
			{
				if(!myContacts[it->first][it2->first]->statcont)
					myContacts[it->first][it2->first]->type = Contact::DynamicContact;
				else
					myContacts[it->first][it2->first]->statcont = false;
			}
		}
	}
}



void sfp::ContactManager::SetStaticContact(sfp::Object* first, sfp::Object* second)
{
	if(myContacts[first][second] != NULL)
	{
		myContacts[first][second]->type = Contact::StaticContact;
		myContacts[first][second]->frames = 3;
		myContacts[first][second]->statcont = true;
	}
}



