// visualizer draw command 

#ifndef _VisualizerDrawCommand
#define _VisualizerDrawCommand

#include "AzulCore.h"

class VisualizerDrawCommand
{
public:

	VisualizerDrawCommand() = default;
	VisualizerDrawCommand(const VisualizerDrawCommand&) = delete;
	VisualizerDrawCommand& operator=(const VisualizerDrawCommand&) = delete;
	~VisualizerDrawCommand() = default;

	void Initialize(Matrix world, Vect col, GraphicsObject_WireframeConstantColor* obj);
	void Execute();

private:

	Matrix world;
	Vect col;
	GraphicsObject_WireframeConstantColor* pGO;
};

#endif _VisualizerDrawCommand
