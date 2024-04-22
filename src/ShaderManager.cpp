// Singleton for managing the loading of shaders 

#include "ShaderManager.h"

ShaderManager* ShaderManager::ptrInstance = nullptr; 

ShaderManager::ShaderManager() // preload 
{
	privLoad(spriteShader, "spriteRender"); // preload sprite shader 

}

// creates a shader object and inserts it into the shaders map 
void ShaderManager::privLoad(const std::string key, std::string shaderName)
{
	assert(Shaders.find(key) == Shaders.end());

	std::string shaderWithPath = path + shaderName;
	ShaderObject* newShader = new ShaderObject(shaderWithPath.c_str());
	std::pair<const std::string, ShaderObject*> newItem = { key, newShader };
	Shaders.insert(newItem);
}

// gets shader from map 
ShaderObject* ShaderManager::privGet(const std::string toFind)
{
	assert(Shaders.find(toFind) != Shaders.end()); // maybe better way of doing this 
	return Shaders.find(toFind)->second;
}

// clear Shaders map
void ShaderManager::privDelete()
{
	//delete all of the shaders 

	for (std::map<const std::string, ShaderObject*>::iterator it = Shaders.begin(); it != Shaders.end(); ++it)
	{
		delete it->second;
	}

	Shaders.clear();

	// delete the singleton  
	delete ptrInstance;
	ptrInstance = nullptr;
}