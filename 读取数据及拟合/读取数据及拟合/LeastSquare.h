#pragma once

#include"ReadDatas.h"
#include<iostream>
#include<string>
#include<vector>
using namespace std;


class LeastSquare
{
private:
	ReadDatas MyReadDatas;
	vector<double> x, f_x, w;//自变量、确定函数，权重
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
	void fitting(string OriginalDatasPath = "", int N = 2);
};

