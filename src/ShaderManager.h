// Singleton for managing the loading of shaders 

#ifndef _ShaderManager
#define _ShaderManager

#include "AzulCore.h"
#include <map>
#include <assert.h>

class ShaderManager
{
private:

	static ShaderManager* ptrInstance;

	ShaderManager();
	ShaderManager(const ShaderManager&) = delete;
	ShaderManager& operator =(const ShaderManager&) = delete;
	~ShaderManager() = default; // <-- gotta define this? 

	static ShaderManager& Instance()
	{

		if (!ptrInstance)
		{

			ptrInstance = new ShaderManager();

		}

		return *ptrInstance;
	}

	// path 
	std::string path = "Shaders\\";

	// map with string key and ShaderObject
	std::map<const std::string, ShaderObject*> Shaders; // add using to simplify types <---

	// creates a shader object and inserts it into the shaders map 
	void privLoad(const std::string key, std::string shaderName);

	// gets shader from map 
	ShaderObject* privGet(const std::string toFind);

	// clear Shaders map
	void privDelete();

	friend class ShaderManagerAttorney;

public:

	// default string 

	const std::string spriteShader = "spriteShader";

	/// <summary>
	///	Adds a .glsl Shader (.vs and .ps) to the Shader Manager
	/// </summary>
	/// <param name="key"> A string to be used to retrieve the Azul Shader from the Shader Manager. </param>
	/// <param name="shaderName"> The name of the shader in the file system. Do not include exstentions. Only one call necessary for the .ps and .vs files.</param>
	static void Load(const std::string key, std::string shaderName) { Instance().privLoad(key, shaderName); };
	/// <summary>
	/// Retrieves an Azul ShaderObject from the Shader Manager.
	/// </summary>
	/// <param name="key"> A string equal to the shader name used in the Load function. </param>
	/// <returns> A pointer to an Azul ShaderObject. </returns>
	static ShaderObject* Get(const std::string key) { return Instance().privGet(key); };
};



#endif _ShaderManager
