// Manager for registering if an object should be updated 

#ifndef _UpdatableManager
#define _UpdatableManager

#include<list>

class Updatable;

class UpdatableManager
{

public: 

	UpdatableManager() = default; 
	UpdatableManager(const UpdatableManager&) = delete;
	UpdatableManager& operator = (const UpdatableManager&) = delete; 
	~UpdatableManager();

	void ProcessElements();

	void Register(Updatable* obj);
	void Deregister(Updatable* obj);

private: 

	using UpdateList = std::list<Updatable*>;
	UpdateList updateList;

};


#endif _UpdatableManager
