// Singleton for managing the loading textures 

#ifndef _TextureManager
#define _TextureManager

#include "AzulCore.h"
#include <map>
#include <assert.h>

class TextureManager
{

private:

	static TextureManager* ptrInstance;

	TextureManager() = default;
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator = (const TextureManager&) = delete; 
	~TextureManager() = default; 

	static TextureManager& Instance()
	{

		if (!ptrInstance)
		{
			ptrInstance = new TextureManager();
		}

		return *ptrInstance;
	}

	// relative path 
	std::string path = "Textures\\";

	// map with textures
	std::map<const std::string, Texture*> Textures; // add using to simplify types <---

	// load texure from file 
	void privLoad(const std::string key, std::string textureName);

	// create texture from rgba
	void privLoad(const std::string key, const unsigned char red, const unsigned char green, const unsigned char blue, const unsigned char alpha);

	// get texture from texure map 
	Texture* privGet(std::string key);

	// clear textures and delete singleton 
	void privDelete();

	friend class TextureManagerAttorney;

public:
	/// <summary>
	/// Adds a Azul Texture to the Texture Manager.
	/// </summary>
	/// <param name="key"> A string that will be used to retrieve the Texture from the Texture Manager. </param>
	/// <param name="textureName"> A string equal to the name of a .tga file in the /Textures folder. </param>
	static void Load(const std::string key, std::string textureName) { Instance().privLoad(key, textureName); }
	/// <summary>
	/// Creates a single color Azul Texture and adds it to the Texture Manager.
	/// </summary>
	/// <param name="key"> A string that will be used to retrieve the Texture from the Texture Manager. </param>
	/// <param name="red"> Red value of Texture color.</param>
	/// <param name="green"> Green value of Texture color. </param>
	/// <param name="blue"> Blue value of Texture color. </param>
	/// <param name="alpha"> Alpha of Texture color. </param>
	static void Load(const std::string key, const unsigned char red, const unsigned char green, const unsigned char blue, const unsigned char alpha) { Instance().privLoad(key, red, green, blue, alpha); }

	/// <summary>
	/// Retrieves a Azul Texture from the Texture Manager.
	/// </summary>
	/// <param name="key"> A string equal to the name of a Texture used in the Load function. </param>
	/// <returns> A pointer to the Azul Texture in the Texture Manager. </returns>
	static Texture* Get(std::string key) { return Instance().privGet(key); }

};


#endif _TextureManager