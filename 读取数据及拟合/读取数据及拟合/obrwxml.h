#pragma once
#include <fstream>
#include<iostream>
#include"mydatatype.h"
class obrwxml
{
private:

public:
	obrwxml();
	~obrwxml();

	SConsParam MyConsParam;
	SInitParam MyInitParam;
	SOutParam MyOutParam;


	void readxml(string Path);
	void readtxt(string Path);
	void writexml(string Path);
	void writetxt(string Path);

	vector<double> splitBySeparator(const string &s, const string seperator);//²ð·Ö×Ö·û´®
};

