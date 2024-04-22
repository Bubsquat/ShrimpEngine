// singleton for managing models 

#ifndef _ModelManager
#define _ModelManager

#include "AzulCore.h"
#include <map>
#include <assert.h>

class ModelManager
{

private:

	static ModelManager* ptrInstance; 

	ModelManager(); 
	ModelManager(const ModelManager&) = delete;
	ModelManager& operator =(const ModelManager&) = delete;
	~ModelManager() = default; 

	static ModelManager& Instance()
	{

		if (!ptrInstance)
		{
			ptrInstance = new ModelManager();
		}

		return *ptrInstance;
	}

	// relative path
	std::string path = "Models\\";

	// map for storing models 
	std::map<const std::string, Model*> Models; // add using to simplify types <---

	// load model from file 
	void privLoad(std::string key, std::string modelName);

	// load premade model 
	void privLoad(std::string key, Model::PreMadeModels modelType);

	// get Model with key 
	Model* privGet(std::string key);

	// clear models and delete singleton 
	void privDelete();

	friend class ModelManagerAttorney;

public:

	// default model
	const std::string spriteModel = "spriteModel";
	const std::string sphereModel = "sphereModel";
	const std::string boxModel = "boxModel";

	/// <summary>
	/// Adds a .azul Model to the Model Manager
	/// </summary>
	/// <param name="key"> A string that will be used to retreive the model from the Model Manager. </param>
	/// <param name="modelName"> A string equal to the .azul file in the Model Manager. Do not include file extension./Models folder. 
	/// A default model type can also be used with Model::PreMadeModels. </param>
	static void Load(std::string key, std::string modelName) { Instance().privLoad(key, modelName); }
	static void Load(std::string key, Model::PreMadeModels modelType) { Instance().privLoad(key, modelType); }
	/// <summary>
	/// Retrieves a Model From the Model Manager
	/// </summary>
	/// <param name="key"> A string equal to the name used in the Load funciton. </param>
	/// <returns> A pointer to an Azul Model type. </returns>
	static Model* Get(std::string key) { return Instance().privGet(key); }

};



#endif _ModelManager
