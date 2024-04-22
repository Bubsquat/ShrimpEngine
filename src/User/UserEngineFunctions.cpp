// function definitions for User defined engine functions (GameInitialize, LoadResources, GameEnd)

#include "../Game.h"
#include "../ShaderManager.h"
#include "../ModelManager.h"
#include "../TextureManager.h"
#include "../SceneManager.h"
#include "../SpriteFontManager.h"
#include "../ImageManager.h"
#include "../TerrainManager.h"
#include "DemoScene1.h"
#include "DemoGameScene.h"
#include "TestingScene.h"
#include "Level1Scene.h"
#include "Level2Scene.h"
#include "SplashScreenScene.h"
#include "IKDemoScene1.h"
#include "Demo2Level1Scene.h"
#include "Demo2Level2Scene.h"

// user defined functions 

void Game::LoadResources()
{

	// loading graphics for demo scene 1

	//shaders
	ShaderManager::Load("texture", "textureFlatRender");
	ShaderManager::Load("textureLight", "textureLightRender");
	ShaderManager::Load("colorNoTexture", "colorNoTextureRender");
	ShaderManager::Load("constantColor", "colorConstantRender");

	//models
	ModelManager::Load("axisModel", "Axis.azul");
	ModelManager::Load("planeModel", "Plane.azul");
	ModelManager::Load("frigateModel", "space_frigate.azul");
	ModelManager::Load("cottageModel", "Cottage.azul");
	ModelManager::Load("tankBodyModel", "TankBodyMoreDetails.azul");
	ModelManager::Load("tankTurretModel", "TankTurret.azul");
	ModelManager::Load("tankThighModel", "TankThigh.azul");
	ModelManager::Load("tankFootModel", "TankFoot.azul");
	ModelManager::Load("IKTankBodyModel", "TankBodyV2.azul");
	ModelManager::Load("IKTankTurretModel", "TankTurretV2.azul");
	ModelManager::Load("IKTankLowerLegModel", "TankLowerLegV2.azul");
	ModelManager::Load("IKTankUpperLegModel", "TankUpperLegV2.azul");

	//textures
	TextureManager::Load("frigateTex", "space_frigate.tga");
	TextureManager::Load("planeTex", "grid.tga");
	TextureManager::Load("cottageTex", "Cabintexture.tga");
	TextureManager::Load("chimneyTex", "Chimneytexture.tga");
	TextureManager::Load("roofTex", "Rooftexture.tga");
	TextureManager::Load("brickTex", "brick-wall.tga");
	TextureManager::Load("tankBodyTex", "body.tga");
	TextureManager::Load("stitchImgTex", "stitch.tga");
	TextureManager::Load("dvdLogoTex", "dvdLogo.tga");
	TextureManager::Load("asphaultTex", "asphaultTexture.tga");
	TextureManager::Load("gridTex", "grid.tga");

	TextureManager::Load("sbFrontTex", "nightMesaSkyBoxMiddle.tga");
	TextureManager::Load("sbBackTex", "nightMesaSkyBoxBack.tga");
	TextureManager::Load("sbLeftTex", "nightMesaSkyBoxLeft.tga");
	TextureManager::Load("sbRightTex", "nightMesaSkyBoxRight.tga");
	TextureManager::Load("sbTopTex", "nightMesaSkyBoxTop.tga");
	TextureManager::Load("sbBottomTex", "nightMesaSkyBoxBottom.tga");

	TextureManager::Load("splashScreenTex", "DemoGameSplashScreen.tga");
	TextureManager::Load("splashScreen2Tex", "DemoGameSplashScreen2.tga");
	TextureManager::Load("hudTex", "Hud.tga");
	TextureManager::Load("healthChunkTex", "healthChunk.tga");
	TextureManager::Load("dirtTex", "seamlessDirt1.tga");

	//images
	ImageManager::Load("SplashScreenImg", TextureManager::Get("splashScreenTex"));
	ImageManager::Load("SplashScreen2Img", TextureManager::Get("splashScreen2Tex"));
	ImageManager::Load("hudImg", TextureManager::Get("hudTex"));
	ImageManager::Load("healthChunkImg", TextureManager::Get("healthChunkTex"));

	//fonts
	SpriteFontManager::Load("impact", "Impact");

	//terrains 
	TerrainManager::Load("testTerrain", "HMTest.tga", Vect(100.0f, 0.0f, 0.0f), 5000.0f, 500.0f, TextureManager::Get("gridTex"), -50.0f, 10, 10);
	TerrainManager::Load("D2Level1Terrain", "ArenaHeightmap.tga", Vect(0, 0, 0), 50000.0f, 3500.0f, TextureManager::Get("asphaultTex"), -50.0f, 25, 25);
	TerrainManager::Load("D2Level2Terrain", "ArenaHeightmap2.tga", Vect(0, 0, 0), 50000.0f, 3500.0f, TextureManager::Get("dirtTex"), -50.0f, 25, 25);

	//SceneManager::SetStartScene(new DemoGameScene());
	//SceneManager::SetStartScene(new IKDemoScene1());
	//SceneManager::SetStartScene(new Demo2Level1Scene());
	//SceneManager::SetStartScene(new Demo2Level2Scene(-1));
	SceneManager::SetStartScene(new SplashScreenScene(-1));
}

void Game::GameInitialize()
{
	// Game Window Device setup
	this->setWindowName("Shrimp Engine");
	this->setWidthHeight(800, 600);
	this->SetClearColor(0.4f, 0.4f, 0.8f, 1.0f);

}

void Game::GameEnd()
{


}