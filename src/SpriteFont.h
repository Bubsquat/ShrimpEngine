// SpriteFont

#ifndef _SpriteFont
#define _SpriteFont

#include "AzulCore.h"
#include <string>
#include <xmllite.h>
#include <map>

class SESprite;

class SpriteFont
{
public:
	using Key = int;
	//using Glyph = SESprite; 

private:
	std::string Name;
	Texture* FontTexture;
	using FontMap = std::map< Key, SESprite* >;
	FontMap fontmap;

	// Parse the XML file
	void XMLtoCollection(std::string filename);

	// Tool: Reads & converts an XML attribute into an int
	void ElementTextToInt(IXmlReader* pReader, int& out);

	std::string path = "Textures\\";
	std::string extension = ".tga";

public:
	SpriteFont() = delete;
	SpriteFont(std::string name, std::string fileName); // adding font name 
	~SpriteFont();
	SpriteFont(const SpriteFont&) = delete;
	SpriteFont& operator=(const SpriteFont&) = delete;

	SESprite* GetGlyph(char c) const;
};

#endif _SpriteFont