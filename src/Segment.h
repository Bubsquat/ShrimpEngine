// container for a single segment in a Linkage

#ifndef _Segment
#define _Segment

#include "AzulCore.h"
#include "Colors.h"

class Segment
{
public:

	Segment(); // default initilization for segment 
	Segment(Vect startPoint, Vect endPoint); // specify by two endpoints 
	Segment(Vect startPoint, Vect dir, float lenght); // specify with a startpoint dir and length 

	// getter methods
	Matrix GetRot();
	Matrix GetAlignmentMatrix();
	Vect GetStartPoint();
	Vect GetEndPoint();
	float GetLenght();

	// setter methods 
	void Rotate(Matrix rotMatrix);
	void SetRotation(Matrix rotMatrix);
	void Translate(Matrix transMatrix);

	// segment debug tools  
	void VisualizeSegment(const Vect& col = Colors::Blue);
	void PrintSegment();

	static const float DefaultLenght;

private:

	float length;

	Vect StartPoint;
	Vect EndPoint;
	Vect Dir;

	Matrix Rotation;
	Matrix Translation;

};

#endif _Segment
