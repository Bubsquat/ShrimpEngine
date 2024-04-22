// Manager for registering if an object should be updated 

#ifndef _UpdateableManager
#define _UpdateableManager

#include<list>

class Updateable;

class UpdateableManager
{

private:

	using UpdateList = std::list<Updateable*>;
	UpdateList updateList;

public: 

	UpdateableManager() = default; 
	UpdateableManager(const UpdateableManager&) = delete;
	UpdateableManager& operator = (const UpdateableManager&) = delete; 
	~UpdateableManager();

	void ProcessElements();

	void Register(Updateable* obj);
	void Deregister(Updateable* obj);

	using UpdateListRef = UpdateList::iterator;

};


#endif _UpdatableManager
