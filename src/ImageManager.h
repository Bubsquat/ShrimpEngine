// singleton sprite image manager

#ifndef _ImageManager
#define _ImageManager

#include <Map>
#include <string>
#include "AzulCore.h"

class ImageManager
{
public:

	using ImageMap = std::map<const std::string, Image*>;

private:

	static ImageManager* ptrInstance;

	ImageManager() = default;
	ImageManager(const ImageManager&) = delete;
	ImageManager& operator = (const ImageManager&) = delete;
	~ImageManager() = default;

	static ImageManager& Instance()
	{

		if (!ptrInstance)
		{
			ptrInstance = new ImageManager();
		}
		return *ptrInstance;
	}

	ImageMap imageMap;

	void privDelete();

	Image* privGet(const ImageMap::key_type key); // make attorney for this 
	void privLoad(const ImageMap::key_type key, Texture* tex);
	void privLoad(const ImageMap::key_type key, Texture* tex, Rect* r);

	friend class ImageManagerAttorney;

public:

	/// <summary> Retrieves an image from the Image Manager. </summary>
	/// <remarks> Must have been loaded in previously with Load command.</remarks>
	/// 
	/// <param name="key"> A string equal to the name used in the Load funciton. </param>
	/// 
	/// <returns> A pointer to a stored Azul Image type.</returns>
	static Image* Get(const ImageMap::key_type key) { return Instance().privGet(key); };

	/// <summary>
	/// Adds a Texture to the Image Manager to be used as an Image.
	/// </summary>
	/// <param name="key"> A string that will be used to retrieve the image from the Image Manager. </param>
	/// <param name="tex"> A pointer to an Azul Texture that will be added to the Image Manager. </param>
	static void Load(const ImageMap::key_type key, Texture* tex) { Instance().privLoad(key, tex); };

	/// <summary>
	/// Adds a Texture to the Image Manager to be used as an Image. Specifies the amount (x,y) and position (x,y) to sample from the texture.
	/// </summary>
	/// <param name="key"> A string that will be used to retrieve the image from the Image Manager. </param>
	/// <param name="tex"> A pointer to an Azul Texture that will be added to the Image Manager. </param>
	/// <param name="r"> An Azul Rect that represents the sampling X, Y then the width, height. </param>
	static void Load(const ImageMap::key_type key, Texture* tex, Rect* r) { Instance().privLoad(key, tex, r); };

};


#endif !_ImageManager
