// Collection of segments that are linked and manipulatable 

#ifndef _Linkage
#define _Linkage

#include "AzulCore.h"
#include <list>
#include "Colors.h"

class Segment; 

class Linkage
{
public:

	Linkage();
	Linkage(int numLinks, float linkLength, Vect startPoint, Vect Dir);
	Linkage(const Linkage&) = delete;
	Linkage& operator=(const Linkage&) = delete;
	~Linkage();

	void AddSegment(Vect startPoint, Vect endPoint);
	void AddSegment(Vect startPoint, Vect dir, float lenght);

	Segment* GetSegment(int segNum);
	int GetNumSegments();

	//void ResetLinkage();
	void RotSegment(int segNum, Matrix rotMatrix);
	void SetSegmentRot(int segNum, Matrix rotMatrix);
	void TransformLinkage(Matrix transMatrix);
	void ShowLinks();

private:

	using SegmentList = std::list<Segment*>;
	SegmentList segList;

	// array of colors for the segment visualization code
	Vect displayColors[5] =
	{
		Colors::Blue,
		Colors::DarkCyan,
		Colors::Pink,
		Colors::Purple,
		Colors::Red
	};

};

#endif _Linkage
