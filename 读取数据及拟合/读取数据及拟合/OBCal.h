#pragma once
#include"obrwxml.h"

class OBCal
{
private:
	obrwxml Prwxml;

	SConsParam ConsParam;
	SInitParam IniParam;
	SOutParam OutParam;

	double h;

	
	double u[8], f[8];//u[0]:vx		u[1]:vy		u[2]:vz;		u[3]:x;		u[4]:y;		u[5]:z;		u[6]:t		u[8]:p;

	void INPT(int i);
	void OUT();
	void Constant(SConsParam Params);
	void Inital(SInitParam Params);
	void Output();
	void OutputClear();
	void OBSimu();
	void InputParam(string inputXmlPath);
	void OutputParam(string outputXmlPath);
	void RK(int n, double h, double u[], double f[]);
	void FCT(double u[], double f[]);//�����Ҷ˺����ӳ���
	double T_y(double y);//�¶���߶ȵı仯
	double H(double y);//�����ܶȺ���
	double G(double v, double cs);//��������
	double Cx0(double Ma);//43������ϵ��
	double Interpolation(int n, double x, double a[], double b[]);
public:
	vector<double>TT, XX, YY, ZZ, V, Theta, VX, VY, VZ, P;

	OBCal();
	~OBCal();

	void Simu(string inputXmlPath, string  outputXmlPath);

	void Simu(SInitParam InitParam,SConsParam ConsParam, string  outputPath="output.txt");
};

