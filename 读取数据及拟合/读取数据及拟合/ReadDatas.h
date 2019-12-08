#pragma once
#include"mydatatype.h"
#include<fstream>
#include<iostream>

using namespace std;
class ReadDatas
{
private:

	//vector<double> splitBySeparator(const string &s, const string seperator);//²ð·Ö×Ö·û´®
	vector<string> splitBySeparator(const string &s, const string seperator);
	vector<double>getdatas(const string &s);
	
public:
	SOriginalDatas MyOriginalDatas;
	SRadarCoordinate MyRadarCoordinate;

	void readtxt(string OriginalDatasPath, string RadarCoordinatePath="Õ¾×ø±ê.txt");

	ReadDatas();
	~ReadDatas();
};

