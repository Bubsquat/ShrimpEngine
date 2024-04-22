// singleton asset manager for sprite fonts 

#include "SpriteFontManager.h"
#include "SpriteFont.h"

SpriteFontManager* SpriteFontManager::ptrInstance = nullptr;

SpriteFontManager::SpriteFontManager() 
{
}

void SpriteFontManager::privDelete()
{
	for (SpriteFontMap::iterator it = sfMap.begin(); it != sfMap.end(); it++)
	{
		delete it->second;
	}

	delete ptrInstance;
	ptrInstance = nullptr;
}

void SpriteFontManager::privLoad(std::string fontName, std::string fileName)
{
	SpriteFont* newSpriteFont = new SpriteFont(fontName, fileName);
	std::pair<SpriteFontMap::key_type, SpriteFont*> newPair = {fontName, newSpriteFont};
	sfMap.insert(newPair);

}

const SpriteFont* SpriteFontManager::privGet(const SpriteFontMap::key_type& key)
{
	assert(sfMap.find(key) != sfMap.end());
	return sfMap.find(key)->second;
}