// singleton for managing models 

#include "ModelManager.h"

ModelManager* ModelManager::ptrInstance = nullptr;

ModelManager::ModelManager()
{
	privLoad(spriteModel, Model::PreMadeModels::UnitSquareXY);
	privLoad(sphereModel, Model::PreMadeModels::UnitSphere);
	privLoad(boxModel, Model::PreMadeModels::UnitBox_WF);
}

// load model from file 
void ModelManager::privLoad(std::string key, std::string modelName)
{
	
	assert(Models.find(key) == Models.end());

	std::string modelWithPath = path + modelName;
	Model* newModel = new Model(modelWithPath.c_str());
	std::pair<const std::string, Model*> newItem = { key, newModel };
	Models.insert(newItem);
}

// load premade model 
void ModelManager::privLoad(std::string key, Model::PreMadeModels modelType)
{
	
	assert(Models.find(key) == Models.end());
	
	Model* newModel = new Model(modelType);
	std::pair<const std::string, Model*> newItem = { key, newModel };
	Models.insert(newItem);
	
}

// get Model with key 
Model* ModelManager::privGet(std::string key)
{
	assert(Models.find(key) != Models.end());
	return Models.find(key)->second;
}

// clear models and delete singleton 
void ModelManager::privDelete()
{
	// delete textures 
	for (std::map<const std::string, Model*>::iterator it = Models.begin(); it != Models.end(); ++it)
	{
		delete it->second;
	}

	Models.clear();

	// delete the singleton  
	delete ptrInstance;
	ptrInstance = nullptr;
}