// Manager for registering if an object should be drawn 

#ifndef _DrawableManager
#define _DrawableManager

#include <list>

class Drawable; 

class DrawableManager
{
private:

	using DrawList = std::list<Drawable*>;
	DrawList drawList;

public:

	DrawableManager() = default;
	DrawableManager(const DrawableManager&) = delete;
	DrawableManager& operator =(const DrawableManager&) = delete;
	~DrawableManager();
	
	void ProcessElements();

	void Register(Drawable*);
	void Deregister(Drawable*);

	using DrawListRef = DrawList::iterator;
};


#endif _DrawableManager
