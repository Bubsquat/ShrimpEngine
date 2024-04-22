// Singleton for managing the loading textures 

#include "TextureManager.h"

TextureManager* TextureManager::ptrInstance = nullptr; 

// load texure from file 
void TextureManager::privLoad(const std::string key, std::string textureName)
{
	assert(Textures.find(key) == Textures.end());

	std::string textureWithPath = path + textureName;
	Texture* newTexture = new Texture(textureWithPath.c_str());
	std::pair<const std::string, Texture*> newItem = { key, newTexture };
	Textures.insert(newItem);
}

// create texture from rgba
void TextureManager::privLoad(const std::string key, const unsigned char red, const unsigned char green, const unsigned char blue, const unsigned char alpha)
{
	assert(Textures.find(key) == Textures.end());

	Texture* newTexture = new Texture(red, green, blue, alpha);
	std::pair<const std::string, Texture*> newItem = { key, newTexture };
	Textures.insert(newItem);
}

// get texture from texure map 
Texture* TextureManager::privGet(std::string key)
{
	assert(Textures.find(key) != Textures.end()); 
	return Textures.find(key)->second;
}

// clear textures and delete singleton 
void TextureManager::privDelete()
{
	// delete textures 
	for (std::map<const std::string, Texture*>::iterator it = Textures.begin(); it != Textures.end(); ++it)
	{
		delete it->second;
	}

	Textures.clear();

	// delete the singleton  
	delete ptrInstance;
	ptrInstance = nullptr;
}