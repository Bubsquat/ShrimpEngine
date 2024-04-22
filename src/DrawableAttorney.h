// Attorney for drawable attribute

#ifndef _DrawableAttorney
#define _DrawableAttorney

#include "Drawable.h"

class DrawableAttorney
{
public:
	class GameLoop
	{
	private:
		friend class DrawableManager;
		static void draw(Drawable* obj) { obj->Draw(); };
		static void draw2D(Drawable* obj) { obj->Draw2D(); };
		static void SetListRef(Drawable* obj, DrawableManager::DrawListRef ref) { obj->SetListRef(ref); };
		static DrawableManager::DrawListRef GetListRef(Drawable* obj) { return obj->GetListRef(); };
	};
public:
	class Registration
	{
		friend class DrawRegistrationCommand;
		friend class DrawDeregistrationCommand;
	private:
		static void SceneRegistration(Drawable* obj) { obj->SceneRegistration(); };
		static void SceneDeregistration(Drawable* obj) { obj->SceneDeregistration(); };
	};

};



#endif _DrawableAttorney

