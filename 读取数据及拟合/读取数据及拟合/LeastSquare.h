#pragma once

#include"ReadDatas.h"
#include<iostream>
#include<string>
#include<vector>
using namespace std;


class LeastSquare
{
private:
	//OBCal MyOBCal;
	ReadDatas MyReadDatas;
	vector<double> x ,y,z,f_x, w;//自变量、确定函数，权重
	vector<double>wx_n;//wx_n={w1x1^(n),w2x2^(n),...,wixi^(n)}
	vector<double>wxf_n;//wxf_n={w1x1^(n)f1,w2x2^(n)f2,...,wixi^(n)fi}


	
	/*wx={	Σw,			Σ(wx),				Σ(wxx),				...,		Σ(wx^n)
				Σ(wx),		Σ(wxx),				Σ(wxx),				...,		Σ(wx^n)
									...
				Σ(wx^n),	Σ(wx^(n+1)),	Σ(wx^(n+2)),	 ...,	Σ(wx^(2n))}
	*/
	vector<vector<double>>wx;


	
	double sigma(vector<double>Array,int size);//数组求和
	void get_data(string OriginalDatasPath);
	void Gauss();//列主元高斯消去
public:
	LeastSquare();
	~LeastSquare();
	vector<SCoordinate> Mycoordinate;
	vector<double>X, Y, T;//由雷达数据处理得到的弹道点

	void SphericalToCartesian(vector<double> Azimuth, vector<double>Elevation, vector<double> Range);//球坐标转笛卡尔坐标
	void fitting(string OriginalDatasPath = "", int N = 2);
	void fitting(SOriginalDatas inputOriginalDatas);
	void CartesianToSpherical(double X, double Y, double Z);//笛卡尔坐标转球坐标
	SCoordinate XYtoxyz(SCoordinate point);
	SCoordinate xyzToRAE(SCoordinate point);
};

