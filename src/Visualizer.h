// singleton dev tool for displaying info like collision shapes

#ifndef _Visualizer
#define _Visualizer

#include "AzulCore.h"
#include <list>
#include "Colors.h"

class CollisionVolume;
class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;
class VisualizerDrawCommand;

class Visualizer : public Align16
{
	friend class VisualizerAttorney;
private:

	Visualizer();
	Visualizer(const Visualizer&) = delete;
	Visualizer& operator=(const Visualizer&) = delete;
	~Visualizer() = default;

	static Visualizer* ptrInstance;

	static Visualizer& Instance()
	{
		if (!ptrInstance)
		{
			ptrInstance = new Visualizer();
		}
		return *ptrInstance;
	}

	// vars 
	static Vect DEFAULT_COLOR;
	GraphicsObject_WireframeConstantColor* WFUnitSphere;
	GraphicsObject_WireframeConstantColor* WFUnitBox;

	// generic draw cmd list
	using VolumeDrawCommandList = std::list<VisualizerDrawCommand*>;
	VolumeDrawCommandList vDrawCmds;

	// recycling list 
	using DrawCommandRecyclingList = std::list<VisualizerDrawCommand*>;
	DrawCommandRecyclingList drawCmdRec;

	// specific cmds 

	// collision volumes
	void pSubmitBSphere(const CollisionVolumeBSphere& S, const Vect& col);
	void pSubmitAABB(const CollisionVolumeAABB& a, const Vect& col);
	void pSubmitAABB(const Vect& Min, const Vect& Max, const Vect& col);
	void pSubmitOBB(const CollisionVolumeOBB& o, const Vect& col);

	// recycling 
	VisualizerDrawCommand* getDrawCmd();

	// generic op functions
	void RenderVolumes();
	void privDelete();

public:

	float LineLargeValue = 999999.0f;

	static void ShowCollisionVolume(const CollisionVolume& c, const Vect& col = DEFAULT_COLOR);
	static void ShowAABB(const Vect& min, const Vect& max, const Vect& col = DEFAULT_COLOR) { Instance().pSubmitAABB(min, max, col); };
	static void ShowMarker(const Vect& loc, const Vect& col = Colors::Red, const float size = 0.5f);
	static void ShowMarker(const float x, const float y, const float z, const Vect& col = Colors::Red, const float size = 0.5f) { Instance().ShowMarker(Vect(x, y, z), col, size); };
	static void ShowLineSegment(const Vect& pos1, const Vect& pos2, const Vect& col = Colors::Green, const float width = 0.5f);
	static void ShowRay(const Vect& startPoint, const Vect& dir, const Vect& col = Colors::Green, const float width = 0.5f) { Instance().ShowLineSegment(startPoint, startPoint + (Instance().LineLargeValue * dir), col, width); };
	static void ShowLine(const Vect& startPoint, const Vect& dir, const Vect& col = Colors::Green, const float width = 0.5f) { Instance().ShowLineSegment(startPoint - (Instance().LineLargeValue * dir), startPoint + (Instance().LineLargeValue * dir), col, width); };

};


#endif _Visualizer
