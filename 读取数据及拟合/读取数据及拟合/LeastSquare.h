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
	vector<double> x, f_x, w;//�Ա�����ȷ��������Ȩ��
	vector<double>wx_n;//wx_n={w1x1^(n),w2x2^(n),...,wixi^(n)}
	vector<double>wxf_n;//wxf_n={w1x1^(n)f1,w2x2^(n)f2,...,wixi^(n)fi}

	/*wx={	��w,			��(wx),				��(wxx),				...,		��(wx^n)
				��(wx),		��(wxx),				��(wxx),				...,		��(wx^n)
									...
				��(wx^n),	��(wx^(n+1)),	��(wx^(n+2)),	 ...,	��(wx^(2n))}
	*/
	vector<vector<double>>wx;


	
	double sigma(vector<double>Array,int size);//�������
	void get_data(string OriginalDatasPath);
	void Gauss();//����Ԫ��˹��ȥ
public:
	LeastSquare();
	~LeastSquare();
	void fitting(string OriginalDatasPath = "", int N = 2);
};

