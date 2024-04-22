// Manager for registering if an object should be drawn 

#include "DrawableManager.h"
#include "DrawableAttorney.h"
#include "RegistrationStateEnum.h"

void DrawableManager::Register(Drawable* obj)
{
	DrawableAttorney::GameLoop::SetListRef(obj, drawList.insert(drawList.end(), obj));
}

void DrawableManager::Deregister(Drawable* obj)
{
	drawList.erase(DrawableAttorney::GameLoop::GetListRef(obj));
}

void DrawableManager::ProcessElements()
{
	for (DrawList::iterator it = drawList.begin(); it != drawList.end(); it++)
	{
		DrawableAttorney::GameLoop::draw((*it));
	}
	for (DrawList::iterator it = drawList.begin(); it != drawList.end(); it++)
	{
		DrawableAttorney::GameLoop::draw2D((*it));
	}
}

DrawableManager::~DrawableManager()
{
	this->drawList.clear();
}
