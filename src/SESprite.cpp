// 2d sprite wrapper class

#include "SESpirte.h"
#include "ImageManager.h"
#include "ShaderManager.h"
#include "ModelManager.h"


SESprite::SESprite(std::string imgKey)
{
	angle = 0.0f;
	scaleX = ImageManager::Get(imgKey)->pImageRect->width;
	scaleY = ImageManager::Get(imgKey)->pImageRect->height;
	centerX = 0.0f;
	centerY = 0.0f;

	offset = Matrix(TRANS, centerX, centerY, 0.0f);

	spriteRect = new Rect(0.0f, 0.0f, scaleX, scaleY);
	pGOSprite = new GraphicsObject_Sprite(ModelManager::Get("spriteModel"), ShaderManager::Get("spriteShader"), ImageManager::Get(imgKey), spriteRect);
	Scale = Matrix(SCALE, 1.0f, 1.0f, 1.0f);
	Rot = Matrix(ROT_Z, angle);
	Trans = Matrix(TRANS, pGOSprite->origPosX , pGOSprite->origPosY, 0.0f);

	Matrix world = Scale * offset *Rot * Trans;
	pGOSprite->SetWorld(world);

}

SESprite::~SESprite()
{
	delete spriteRect;
	delete pGOSprite;
}

void SESprite::Render(Camera* pCam )
{
	Matrix world = Scale * Rot * offset * Trans;
	pGOSprite->SetWorld(world);
	pGOSprite->Render(pCam);
}

float SESprite::GetAngle()
{
	return this->angle;
}

void SESprite::SetAngle(float _angle) 
{
	this->angle = _angle; 
	Rot = Matrix(ROT_Z, angle) * Rot;
}

void SESprite::SetCenter(float _xOffset, float _yOffset)
{
	this->centerX = _xOffset;
	this->centerY = _yOffset;

	offset = Matrix(TRANS, centerX, centerY, 0.0f);

}

void SESprite::SetPosition(float _x, float _y)
{
	Trans = Matrix(TRANS, _x, _y, 0.0f);
}

void SESprite::SetScalePixel(float width, float height) // this function is probably doing the wrong thing 
{

	scaleX = width;
	scaleY = height;

	spriteRect->width = scaleX;
	spriteRect->height = scaleY;

	Image* img = pGOSprite->pImage;
	delete pGOSprite;

	pGOSprite = new GraphicsObject_Sprite(ModelManager::Get("spriteModel"), ShaderManager::Get("spriteShader"), img, spriteRect);

}

float SESprite::GetWidth()
{
	return pGOSprite->pImage->pImageRect->width;
}

float SESprite::GetHeight()
{
	return pGOSprite->pImage->pImageRect->height;
}