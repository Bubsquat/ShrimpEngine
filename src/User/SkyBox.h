// game skybox

#ifndef _SkyBox
#define _SkyBox

#include "../GameObject.h"

class SkyBox : public GameObject
{
public:

	SkyBox();
	SkyBox(const SkyBox&) = delete;
	SkyBox& operator=(const SkyBox&) = delete;
	~SkyBox();

	void Draw();
	void setPos(float x, float y, float z);

	void SceneEntry();
	void SceneExit();

private:

	Vect skyBoxCenter;

	GraphicsObject_TextureFlat* sbTop;
	GraphicsObject_TextureFlat* sbBottom;
	GraphicsObject_TextureFlat* sbLeft;
	GraphicsObject_TextureFlat* sbRight;
	GraphicsObject_TextureFlat* sbFront;
	GraphicsObject_TextureFlat* sbBack;


	const float ScaleFactor = 40000.0f;
	Matrix Scale;

	Matrix TopRt;
	Matrix BottomRt;
	Matrix LeftRt;
	Matrix RightRt;
	Matrix FrontRt;
	Matrix BackRt;
};



#endif _SkyBox
