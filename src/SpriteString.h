// sprite string using sprite font and SESprite

#ifndef _SpriteString
#define _SpriteString

#include <list>

class SpriteFont;
class SESprite;

class SpriteString
{
public:

	SpriteString() = delete;
	SpriteString(const SpriteFont*);
	SpriteString(const SpriteFont* sf, std::string s, float x, float y);
	SpriteString(const SpriteString&) = delete; // maybe add these later
	SpriteString &operator= (const SpriteString&) = delete;
	~SpriteString();

	float GetHeight();
	float GetWidth();

	void Render();

	void Set(float x, float y);
	void Set(const SpriteFont* sf, std::string s, float x, float y);

private:


	using GlyphList = std::list<SESprite*>;
	GlyphList glyphList;

	const SpriteFont* myFont;
	std::string string;
	
	int numChars; 

	float height;
	float width;
	float posX;
	float posY;
};



#endif _SpriteString
