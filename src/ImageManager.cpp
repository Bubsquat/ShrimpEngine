// singleton sprite image manager

#include "ImageManager.h"
#include "TextureManager.h"

ImageManager* ImageManager::ptrInstance = nullptr;

void ImageManager::privDelete()
{
	// delete images 
	for (ImageMap::iterator it = imageMap.begin(); it != imageMap.end(); ++it)
	{
		delete it->second;
	}
	imageMap.clear();

	// delete singleton

	delete ptrInstance;
	ptrInstance = nullptr;
}

Image* ImageManager::privGet(const ImageMap::key_type key)
{
	assert(imageMap.find(key) != imageMap.end());
	return imageMap.find(key)->second;
}

void ImageManager::privLoad(const ImageMap::key_type key, Texture* tex)
{

	Image* newImage = new Image(tex, new Rect(0.0f, 0.0f, (float)tex->getWidth(), (float)tex->getHeight()));

	std::pair<const std::string, Image*> newItem = { key, newImage };
	imageMap.insert(newItem);

}

void ImageManager::privLoad(const ImageMap::key_type key, Texture* tex, Rect* r)
{
	Image* newImage = new Image(tex, r);

	std::pair<const std::string, Image*> newItem = { key, newImage };
	imageMap.insert(newItem);
}