// Collection of segments that are linked and manipulatable 

#include "Linkage.h"
#include "Segment.h"

Linkage::Linkage()
{}

Linkage::Linkage(int numLinks, float linkLength, Vect startPoint, Vect Dir)
{

	Vect start = startPoint;
	Vect end = start + (linkLength * Dir);

	for (int i = 0; i < numLinks; i++)
	{
		segList.push_back(new Segment(start, end));
		start = end;
		end = start + (linkLength * Dir);
	}

}

Linkage::~Linkage()
{
	while (!segList.empty())
	{
		delete segList.front();
		segList.pop_front();
	}
}

void Linkage::AddSegment(Vect startPoint, Vect endPoint)
{
	Segment* newSegment = new Segment(startPoint, endPoint);
	segList.push_back(newSegment);
}

void Linkage::AddSegment(Vect startPoint, Vect dir, float length)
{
	Segment* newSegment = new Segment(startPoint, dir, length);
	segList.push_back(newSegment);
}

Segment* Linkage::GetSegment(int segNum)
{
	SegmentList::iterator it = segList.begin();
	std::advance(it, segNum);
	return (*it);
}

int Linkage::GetNumSegments()
{
	return segList.size();
}

void Linkage::TransformLinkage(Matrix transMatrix)
{

	for (int i = 0; i < (signed)segList.size(); i++)
	{
		Segment* seg = GetSegment(i);
		seg->Translate(transMatrix);
	}

}

void Linkage::RotSegment(int segNum, Matrix rotMatrix)
{

	Segment* curSeg = GetSegment(segNum);
	curSeg->Rotate(rotMatrix);

	for (int i = segNum + 1; i < (signed)segList.size(); i++)
	{
		Segment* nexSeg = GetSegment(i);
		nexSeg->Rotate(rotMatrix);
		nexSeg->Translate(Matrix(TRANS, curSeg->GetEndPoint() - nexSeg->GetStartPoint()));
		curSeg = nexSeg;
	}

}

void Linkage::SetSegmentRot(int segNum, Matrix rotMatrix)
{
	Segment* curSeg = GetSegment(segNum);
	curSeg->SetRotation(rotMatrix);

	for (int i = segNum + 1; i < (signed)segList.size(); i++)
	{
		Segment* nexSeg = GetSegment(i);
		nexSeg->Translate(Matrix(TRANS, curSeg->GetEndPoint() - nexSeg->GetStartPoint()));
		curSeg = nexSeg;
	}

}

//void Linkage::ResetLinkage()
//{
//
//	for (int i = 0; i < (signed)segList.size(); i++)
//	{
//		Segment* seg = GetSegment(i);
//		seg->Rotate(seg->GetRot().getInv());
//	}
//
//}

void Linkage::ShowLinks()
{
	int displayColor = 0;

	for (SegmentList::iterator it = segList.begin(); it != segList.end(); it++)
	{
		(*it)->VisualizeSegment(displayColors[displayColor]);
		displayColor++;
		if (displayColor >= 5) displayColor = 0;
	}
}