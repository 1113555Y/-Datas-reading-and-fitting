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

	

	void set(vector<SCoordinate> MyCoordinate, SRadarCoordinate Radar);
	SCoordinate XYtoxyz(SCoordinate point);
	SCoordinate xyzToRAE(SCoordinate point);
public:
	adjust();
	~adjust();
	SCoordinate endPoint;//Âäµã
	SCoordinate startPoint;//ÅÚÎ»

	void Adjust(vector<SCoordinate> MyCoordinate,SRadarCoordinate Radar);
};

