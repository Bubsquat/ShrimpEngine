// attorney class for the visualizer singleton

#ifndef _VisualizerAttorney
#define _VisualizerAttorney

#include "Visualizer.h"

class VisualizerAttorney
{
public:

	class Operation
	{
		friend class Game;

	private:
		static void ExecuteDraws() { Visualizer::Instance().RenderVolumes(); };
		static void Terminate() { Visualizer::Instance().privDelete(); }
	};

	class CollisionVolumeAccess
	{
		friend class CollisionVolumeBSphere;
		friend class CollisionVolumeAABB;
		friend class CollisionVolumeOBB;

	private:

		static void SubmitBSphere(const CollisionVolumeBSphere& c, const Vect& col) { Visualizer::Instance().pSubmitBSphere(c, col); };
		static void SubmitAABB(const CollisionVolumeAABB& c, const Vect& col) { Visualizer::Instance().pSubmitAABB(c, col); };
		static void SubmitOBB(const CollisionVolumeOBB& c, const Vect& col) { Visualizer::Instance().pSubmitOBB(c, col); };
	};

};



#endif _VisualizerAttorney


