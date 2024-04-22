// container for a single segment in a Linkage

#include "Segment.h"
#include "Visualizer.h"
#include "DataLogger.h"

const float Segment::DefaultLenght = 100.0f;

Segment::Segment()
{
	this->StartPoint = Vect(0.0f, 0.0f, 0.0f, 1.0f);
	this->EndPoint = Vect(0.0f, 0.0f, DefaultLenght, 1.0f); // forward in the z direction
	this->Translation = Matrix(TRANS, StartPoint);
	this->Rotation = Matrix(ROT_X, 0);
	this->Dir = Vect(0.0f, 0.0f, 1.0f, 0.0f); //forward in the z direction
	this->length = DefaultLenght;
}

Segment::Segment(Vect _startPoint, Vect _endPoint)
{
	this->StartPoint = _startPoint;
	this->EndPoint = _endPoint;
	this->Translation = Matrix(TRANS, StartPoint);
	//this->Rotation = Matrix(ROT_ORIENT, StartPoint - EndPoint, Vect(0, 1, 0));
	this->Rotation = Matrix(ROT_ORIENT, Vect(0, 1, 0), EndPoint - StartPoint);
	this->Dir = EndPoint - StartPoint;
	this->length = Dir.mag();
	this->Dir = Dir.getNorm();
	Dir.W() = 0.0f; // make sure this is a vector and not a point 
}

Segment::Segment(Vect _startPoint, Vect _dir, float _lenght)
{
	this->StartPoint = _startPoint;
	this->length = _lenght;
	this->EndPoint = StartPoint + (length * _dir);
	this->Translation = Matrix(TRANS, StartPoint);
	this->Rotation = Matrix(ROT_ORIENT, Vect(0, 1, 0), EndPoint - StartPoint );
	this->Dir = _dir;
	this->Dir = Dir.getNorm();
	Dir.W() = 0.0f;
}

Matrix Segment::GetRot()
{
	return this->Rotation;
}

Vect Segment::GetStartPoint()
{
	return this->StartPoint;
}

Vect Segment::GetEndPoint()
{
	return this->EndPoint;
}

float Segment::GetLenght()
{
	return this->length;
}

Matrix Segment::GetAlignmentMatrix()
{

	Matrix TransMidpoint = Matrix(TRANS, (StartPoint + ((length / 2.0f) * Dir)));
	Matrix rotOut = Matrix(ROT_ORIENT, EndPoint - StartPoint, Vect(0, 1, 0));
	return  rotOut * TransMidpoint;

}

void Segment::Rotate(Matrix _rotMatrix)
{
	this->Rotation = _rotMatrix;
	this->Dir = Dir * Rotation;
	this->EndPoint = StartPoint + (length * Dir);
}

void Segment::SetRotation(Matrix rotMatrix)
{
	this->Dir = Dir * Rotation.getInv();
	this->Rotation = rotMatrix;
	this->Dir = Dir * Rotation;
	this->EndPoint = StartPoint + (length * Dir);
}

void Segment::Translate(Matrix _transMatrix)
{
	this->Translation = _transMatrix;
	this->StartPoint = StartPoint * Translation;
	this->EndPoint = StartPoint + (length * Dir);
}

void Segment::VisualizeSegment(const Vect& _col)
{
	// visualize start and end points with line 
	Visualizer::ShowMarker(StartPoint, _col, 5.0f);
	Visualizer::ShowMarker(EndPoint, _col, 5.0f);
	Visualizer::ShowLineSegment(StartPoint, EndPoint, _col, 1.0f);

}

void Segment::PrintSegment()
{
	DataLogger::Add("StartPoint");
	DataLogger::Add("X:  %f  Y:  %f  Z:  %f", StartPoint.X(), StartPoint.Y(), StartPoint.Z());
	DataLogger::Add("EndPoint");
	DataLogger::Add("X:  %f  Y:  %f  Z:  %f", EndPoint.X(), EndPoint.Y(), EndPoint.Z());
	DataLogger::Add("Dir:  %f  %f  %f  Lenght:  %f", Dir.X(), Dir.Y(), Dir.Z(), length);
}