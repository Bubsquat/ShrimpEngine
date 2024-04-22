// singleton asset manager for sprite fonts 

#ifndef _SpriteFontManager
#define _SpriteFontManager

#include <map>
#include "AzulCore.h"

class SpriteFont;

class SpriteFontManager
{
	friend class SpriteFontManagerAttorney;

private:
	static SpriteFontManager* ptrInstance;

	using SpriteFontMap = std::map<std::string, const SpriteFont*>;
	SpriteFontMap sfMap;

	SpriteFontManager();
	SpriteFontManager(const SpriteFontManager&) = delete;
	SpriteFontManager& operator =(const SpriteFontManager&) = delete;
	~SpriteFontManager() = default;

	static SpriteFontManager& Instance()
	{
		if (!ptrInstance)
		{
			ptrInstance = new SpriteFontManager();
		}
		return *ptrInstance;
	}


	void privLoad(std::string fontName, std::string fileName);
	const SpriteFont* privGet(const SpriteFontMap::key_type&);
	void privDelete();

public:
	/// <summary>
	/// Adds a SpriteFont to the Sprite Font Manager.
	/// </summary>
	/// <param name="fontName"> A string to be used to retrieve the SpriteFont from the Sprite Font Manager. </param>
	/// <param name="textureName"> The name of the .tga file in the /Textures folder that will be used to create the sprite font.
	/// The .tga file will be loaded into the Texture Manager automatically upon SpriteFont creation.  </param>
	static void Load(std::string fontName, std::string textureName) { Instance().privLoad(fontName, textureName); };
	/// <summary>
	/// Retrieves a SpriteFont from the SpriteFont Manager.
	/// </summary>
	/// <param name="key"> A string equal to the SpriteFont name used in the Load function. </param>
	/// <returns> A pointer to a SpriteFont. </returns>
	static const SpriteFont* Get(const SpriteFontMap::key_type& key) { return Instance().privGet(key); };

};



#endif _SpriteFontManager
