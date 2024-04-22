#include "AzulCore.h"
#include "Game.h"
#include "ShaderManagerAttorney.h"
#include "TextureManagerAttorney.h"
#include "ModelManagerAttorney.h"
#include "CameraManager.h"
#include "User/DemoScene1.h"
#include "SceneManagerAttorney.h"
#include "TimeManagerAttorney.h"
#include "VisualizerAttorney.h"
#include "ImageManagerAttorney.h"
#include "SpriteFontManagerAttorney.h"
#include "DataLoggerAttorney.h"
#include "TerrainManagerAttorney.h"

Game* Game::ptrInstance = nullptr;

//-----------------------------------------------------------------------------
// Game::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void Game::Initialize()
{

	// call user defined function
	this->GameInitialize();

}

//-----------------------------------------------------------------------------
// Game::LoadContent()
//		Allows you to load all content needed for your engine,
//	    such as objects, graphics, etc.
//-----------------------------------------------------------------------------
void Game::LoadContent()
{

	// call user defined load function 
	this->LoadResources();

}

//-----------------------------------------------------------------------------
// Game::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------
void Game::Update()
{
	TimeManagerAttorney::ProcessTime();
	SceneManagerAttorney::GameLoop::Update();
	

}

//-----------------------------------------------------------------------------
// Game::Draw()
//		This function is called once per frame
//	    Use this for draw graphics to the screen.
//      Only do rendering here
//-----------------------------------------------------------------------------
void Game::Draw()
{

	VisualizerAttorney::Operation::ExecuteDraws(); // draw visualizer queue first 

	SceneManagerAttorney::GameLoop::Draw();

	DataLoggerAttorney::Render(); // render last 
}

//-----------------------------------------------------------------------------
// Game::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
void Game::UnLoadContent()
{

	VisualizerAttorney::Operation::Terminate();
	SceneManagerAttorney::GameLoop::Terminate();
	TimeManagerAttorney::Terminate();
	ShaderManagerAttorney::Terminate();
	ImageManagerAttorney::Terminate();
	SpriteFontManagerAttorney::Terminate();
	TextureManagerAttorney::Terminate();
	ModelManagerAttorney::Terminate();
	DataLoggerAttorney::Terminate();
	TerrainManagerAttorney::Terminate();
	
}


// public engine services 

void Game::SetWindowName(const char* name)
{
	Instance().setWindowName(name);
}

void Game::SetWindowHeight(int x, int y)
{
	Instance().setWidthHeight(x, y);
}

void Game::setClearColor(float r, float g, float b, float a)
{
	Instance().SetClearColor(r, g, b, a);
}

int Game::GetWidth()
{
	return Instance().getWidth();
}

int Game::GetHeight()
{
	return Instance().getHeight();
}

void Game::priveTermintate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}