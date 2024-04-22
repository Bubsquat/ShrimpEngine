// 2d sprite wrapper class

#ifndef _SESprite
#define _SESprite

#include "AzulCore.h"
#include <string>

class Camera;

#include "SceneManager.h"
#include "Scene.h"
#include "CameraManager.h"

class SESprite
{
public:

	SESprite() = delete;
	SESprite(std::string imgKey);
	SESprite(const SESprite&) = delete;
	SESprite& operator =(const SESprite&) = delete;
	~SESprite();

	void Render(Camera* pCam = SceneManager::GetCurrentScene()->GetCameraManager()->Get2DCamera());

	float GetAngle();
	void SetAngle(float a);
	void SetCenter(float offsetX, float offsetY);
	void SetPosition(float x, float y);
	void SetScalePixel(float width, float height);
	float GetWidth();
	float GetHeight();

private:

	Matrix Scale;
	Matrix Rot;
	Matrix Trans;
	Matrix offset;

	Rect* spriteRect;
	GraphicsObject_Sprite* pGOSprite;

	float angle;
	float centerX;
	float centerY;
	float scaleX;
	float scaleY;

};


#endif _SESprite
