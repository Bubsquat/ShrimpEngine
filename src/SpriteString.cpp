// sprite string using sprite font and SESprite

#include "SpriteString.h"
#include "SpriteFont.h"
#include "SESpirte.h"

SpriteString::SpriteString(const SpriteFont* _sf)
{
	myFont = _sf;
	numChars = 0;
	width = 0;
	height = _sf->GetGlyph('A')->GetHeight();
	posX = 0;
	posY = 0;
}

SpriteString::~SpriteString()
{

}

SpriteString::SpriteString(const SpriteFont* _sf, std::string s, float x, float y)
{
	myFont = _sf;
	numChars = 0;
	width = 0;
	height = 0;
	posX = 0;
	posY = 0;

	this->Set(_sf, s, x, y);
}

void SpriteString::Set(const SpriteFont* sf, std::string s, float x, float y)
{
	posX = x;
	posY = y;
	myFont = sf;
	numChars = s.length();
	string = s;
	height = sf->GetGlyph('A')->GetHeight();


	glyphList.clear();
	
	width = 0; 

	float curPos = posX;
	for (int i = 0; i < numChars; i++)
	{
		SESprite* newGlyph = sf->GetGlyph(s[i]);
		newGlyph->SetPosition(curPos, posY);
		curPos -= newGlyph->GetWidth();
		if (newGlyph->GetHeight() > height) height = newGlyph->GetHeight();
		width += newGlyph->GetWidth();
		glyphList.push_back(newGlyph);

	}

}

void SpriteString::Set(float x, float y)
{
	posX = x;
	posY = y;
}

void SpriteString::Render()
{

	float curX = posX;

	for (GlyphList::iterator it = glyphList.begin(); it != glyphList.end(); it++)
	{
		(*it)->SetPosition(curX, posY);
	
		(*it)->Render();
		curX -= (*it)->GetWidth();
	}

}

float SpriteString::GetHeight()
{
	return height;
}

float SpriteString::GetWidth()
{
	return width;
}
