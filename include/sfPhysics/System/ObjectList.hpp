#ifndef SFPHYSICS_OBJECTLIST_HPP
#define SFPHYSICS_OBJECTLIST_HPP


#include <sfPhysics/System/Objects.hpp>

#include <list>



namespace sfp
{

	class ObjectList
	{
		protected:
			std::list<sfp::Object*> myObjectList;
		
		public:
			ObjectList() {}
			~ObjectList() {}
		
			void AddObject(sfp::Object* object) {myObjectList.push_back(object);}
		
			void EraseObject(std::list<sfp::Object*>::iterator& it) {myObjectList.erase(it);}
			void RemoveObject(sfp::Object* object) {myObjectList.remove(object);}
		
			size_t GetObjectCount() const {return myObjectList.size();}
		
		//	std::list<sfp::Object*>::const_iterator
	};

} // namespace


#endif  // SFPHYSICS_OBJECTLIST_HPP


