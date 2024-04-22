// singleton dev tool for displaying info like collision shapes

#include "Visualizer.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "SceneManager.h"
#include "CameraManager.h"
#include "CollisionVolume.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"
#include "GameAttorney.h"
#include "VisualizerDrawCommand.h"

Visualizer* Visualizer::ptrInstance = nullptr;
Vect Visualizer::DEFAULT_COLOR = Colors::Blue;

Visualizer::Visualizer()
{
	this->WFUnitSphere = new GraphicsObject_WireframeConstantColor(ModelManager::Get("sphereModel"), ShaderManager::Get("constantColor"), DEFAULT_COLOR);
	this->WFUnitBox = new GraphicsObject_WireframeConstantColor(ModelManager::Get("boxModel"), ShaderManager::Get("constantColor"), DEFAULT_COLOR);
}

// generic cmds

void Visualizer::ShowCollisionVolume(const CollisionVolume& c, const Vect& col)
{
	c.DebugView(col);
}


void Visualizer::privDelete()
{
	delete Instance().WFUnitSphere;
	delete Instance().WFUnitBox;

	// remove active cmds 

	while (!vDrawCmds.empty())
	{
		delete vDrawCmds.front();
		vDrawCmds.pop_front();
	}

	// clear recycling list 

	while (!drawCmdRec.empty())
	{
		delete drawCmdRec.front();
		drawCmdRec.pop_front();
	}

	delete ptrInstance;
	ptrInstance = nullptr;
}

void Visualizer::RenderVolumes()
{
	while (!vDrawCmds.empty())
	{
		//vDrawCmds.front()->execute(); // our execute cmd automatically recycles it after drawing

		vDrawCmds.front()->Execute();
		// now move command to recycling list
		drawCmdRec.push_back(vDrawCmds.front());
		vDrawCmds.remove(vDrawCmds.front());
	}
}

VisualizerDrawCommand* Visualizer::getDrawCmd()
{

	VisualizerDrawCommand* newCmd;

	if (drawCmdRec.empty())
	{
		newCmd = new VisualizerDrawCommand();
	}
	else
	{
		newCmd = drawCmdRec.front();
		drawCmdRec.remove(drawCmdRec.front()); // dont delete front
	}

	return newCmd;
}

void Visualizer::pSubmitBSphere(const CollisionVolumeBSphere& S, const Vect& col)
{
	// apply transformations based on the bsphere center and radius 
	// pass the color through then call render 

	Matrix world = Matrix(MatrixSpecialType::IDENTITY);
	world = world * Matrix(SCALE, S.GetRadius(), S.GetRadius(), S.GetRadius());
	world = world * Matrix(TRANS, S.GetCenter().X(), S.GetCenter().Y(), S.GetCenter().Z());

	// create command 
	VisualizerDrawCommand* newCmd = Instance().getDrawCmd();
	newCmd->Initialize(world, col, WFUnitSphere);
	Instance().vDrawCmds.push_back(newCmd);

}

void Visualizer::pSubmitAABB(const CollisionVolumeAABB& a, const Vect& col)
{

	// calculate world
	Matrix world = Matrix(MatrixSpecialType::IDENTITY);
	Matrix scale = Matrix(SCALE, a.GetMax().X() - a.GetMin().X(), a.GetMax().Y() - a.GetMin().Y(), a.GetMax().Z() - a.GetMin().Z());
	Matrix trans = Matrix(TRANS, 0.5f * (a.GetMax().X() + a.GetMin().X()), 0.5f * (a.GetMax().Y() + a.GetMin().Y()), 0.5f * (a.GetMax().Z() + a.GetMin().Z()));
	world = scale * trans;

	//create command 
	VisualizerDrawCommand* newCmd = Instance().getDrawCmd();
	newCmd->Initialize(world, col, WFUnitBox);
	Instance().vDrawCmds.push_back(newCmd);

}

void Visualizer::pSubmitAABB(const Vect& Min, const Vect& Max, const Vect& col)
{
	// calculate world
	Matrix world = Matrix(MatrixSpecialType::IDENTITY);
	Matrix scale = Matrix(SCALE, Max.X() - Min.X(), Max.Y() - Min.Y(), Max.Z() - Min.Z());
	Matrix trans = Matrix(TRANS, 0.5f * (Max.X() + Min.X()), 0.5f * (Max.Y() + Min.Y()), 0.5f * (Max.Z() + Min.Z()));
	world = scale * trans;

	//create command 
	VisualizerDrawCommand* newCmd = Instance().getDrawCmd();
	newCmd->Initialize(world, col, WFUnitBox);
	Instance().vDrawCmds.push_back(newCmd);
}

void Visualizer::pSubmitOBB(const CollisionVolumeOBB& o, const Vect& col)
{
	// get local box
	Matrix scale = Matrix(SCALE, o.GetLocMax().X() - o.GetLocMin().X(), o.GetLocMax().Y() - o.GetLocMin().Y(), o.GetLocMax().Z() - o.GetLocMin().Z());
	Matrix trans = Matrix(TRANS, 0.5f * (o.GetLocMax().X() + o.GetLocMin().X()), 0.5f * (o.GetLocMax().Y() + o.GetLocMin().Y()), 0.5f * (o.GetLocMax().Z() + o.GetLocMin().Z()));

	Matrix boxWorld = scale * trans;
	boxWorld = boxWorld * o.GetWorld();

	// create command
	VisualizerDrawCommand* newCmd = Instance().getDrawCmd();
	newCmd->Initialize(boxWorld, col, WFUnitBox);
	Instance().vDrawCmds.push_back(newCmd);
}

void Visualizer::ShowMarker(const Vect& loc, const Vect& color, const float size)
{

	Matrix world; 
	world = Matrix(SCALE, size, size, size) * Matrix(TRANS, loc.X(), loc.Y(), loc.Z());

	VisualizerDrawCommand* newCmd = Instance().getDrawCmd();
	newCmd->Initialize(world, color, Instance().WFUnitBox);
	Instance().vDrawCmds.push_back(newCmd);

}

void Visualizer::ShowLineSegment(const Vect& pos1, const Vect& pos2, const Vect& col, const float width )
{
	Matrix Scale = Matrix(SCALE, width, width, (pos2 - pos1).mag());
	Matrix Rot = Matrix(ROT_ORIENT, pos2 - pos1, Vect(0, 1, 0)); // test this 
	Matrix Trans = Matrix(TRANS, 0.5 * (pos1 + pos2));
	Matrix world = Scale * Rot * Trans;

	// create command 
	VisualizerDrawCommand* newCmd = Instance().getDrawCmd();
	newCmd->Initialize(world, col, Instance().WFUnitBox);
	Instance().vDrawCmds.push_back(newCmd);
}
