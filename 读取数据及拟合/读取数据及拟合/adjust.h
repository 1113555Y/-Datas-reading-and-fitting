#pragma once
#include "mydatatype.h"
#include"LeastSquare.h"
#include"OBCal.h"
class adjust
{
	SConsParam MyConsParam;
	SInitParam MyInitParam;
	SOutParam MyOutParam;
	


	double deltaVx, deltaVy;
	double deltaX, deltaY;
	OBCal MyOBCal;

	

	void set(vector<double>X, vector<double>Y, vector<double>T);
	
public:
	adjust();
	~adjust();
	SCoordinate endPoint;//Âäµã
	SCoordinate startPoint;//ÅÚÎ»

	void Adjust(vector<double>X, vector<double>Y, vector<double>T);
};

