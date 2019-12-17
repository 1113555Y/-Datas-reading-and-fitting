#include "pch.h"
#include "OBCal.h"


OBCal::OBCal()
{
}


OBCal::~OBCal()
{
}

void OBCal::Simu(string inputXmlPath, string outputXmlPath)
{
	InputParam(inputXmlPath);
	OBSimu(0);
	OutputParam(outputXmlPath);
}

void OBCal::Simu(SInitParam InitParam, SConsParam ConsParam, string  outputPath )
{
	Constant(ConsParam);
	Inital(InitParam);
	OBSimu(ConsParam.endH);
	OutputParam(outputPath);
}

void OBCal::INPT(int i)
{
	u[0] = VX[i]; //水平方向分速
	u[1] = VY[i]; //垂直方向分速
	u[2] = VZ[i];
	u[3] = XX[i]; //水平方向位移
	u[4] = YY[i]; //垂直方向位移
	u[5] = ZZ[i];
	u[6] = TT[i];
	u[7] = P[i];
}

void OBCal::OUT()
{
	VX.push_back(u[0]);
	VY.push_back(u[1]);
	VZ.push_back(u[2]);
	XX.push_back(u[3]);
	YY.push_back(u[4]);
	ZZ.push_back(u[5]);
	TT.push_back(u[6]);
	P.push_back(u[7]);
	double vr = sqrt(pow(u[0], 2) + pow(u[1], 2) + pow(u[2], 2));
	V.push_back(vr);
	//cout<<u[0]<<"\t"<<u[1]<<"\t"<<u[2]<<"\t"<<vr<<"\t"<<u[3]<<"\t"<<u[4]<<"\t"<<u[5]<<"\t"<<u[6]<<endl;
	Prwxml.MyOutParam.t.push_back(u[6]);
	Prwxml.MyOutParam.x.push_back(u[3]);
	Prwxml.MyOutParam.y.push_back(u[4]);
	Prwxml.MyOutParam.z.push_back(u[5]);
	Prwxml.MyOutParam.vx.push_back(u[0]);
	Prwxml.MyOutParam.vy.push_back(u[1]);
	Prwxml.MyOutParam.vz.push_back(u[2]);
	Prwxml.MyOutParam.v.push_back(vr);
	Prwxml.MyOutParam.p.push_back(u[7]);
}

void OBCal::Constant(SConsParam Params)
{
	ConsParam.G0 = 9.806;//地球表面重力加速度G0= 9.80665
	ConsParam.R0 = 6356766;//地球半径R0= 6356766
	ConsParam.R1 = 287;
	ConsParam.h = Params.h;
	ConsParam.c = Params.c;
	ConsParam.endH = Params.endH;

	//炮兵标准气象
	ConsParam.T0n = 288.15;		//气温T0n = 288.15K
	ConsParam.p0n = 100.0e3;		//气压p0n = 100.0kPa
	ConsParam.tau0n = 289.1;		//虚温τ0n = 289.1K
	ConsParam.rho0n = 1.205;		//大气密度rho0n = 1.205kg/m³
	ConsParam.G = 6.328E-3;		//温度递减率G = 6.328E-3

	//风
//	ConsParam.w = Prwxml.MyConsParam.w;
//	ConsParam.theta_w = Prwxml.MyConsParam.theta_w;

}

void OBCal::Inital(SInitParam Params)
{
	IniParam.t = 0;
	IniParam.vx = Params.vx;
	IniParam.vy = Params.vy;
	IniParam.vz = Params.vz;
	IniParam.x = Params.x;
	IniParam.y = Params.y;
	IniParam.z = Params.z;
	IniParam.p = 100e3;
}

void OBCal::OutputClear()
{
	TT.clear();
	XX.clear();
	YY.clear();
	ZZ.clear();
	VX.clear();
	VY.clear();
	VZ.clear();
	P.clear();
	V.clear();

	OutParam.p.clear();
	OutParam.t.clear();
	OutParam.v.clear();
	OutParam.vx.clear();
	OutParam.vy.clear();
	OutParam.vz.clear();
	OutParam.x.clear();
	OutParam.y.clear();
	OutParam.z.clear();

	Prwxml.MyOutParam.t.clear();
	Prwxml.MyOutParam.x.clear();
	Prwxml.MyOutParam.y.clear();
	Prwxml.MyOutParam.z.clear();
	Prwxml.MyOutParam.vx.clear();
	Prwxml.MyOutParam.vy.clear();
	Prwxml.MyOutParam.vz.clear();
	Prwxml.MyOutParam.v.clear();
	Prwxml.MyOutParam.p.clear();
}

void OBCal::OBSimu(double endH)
{
	int i = 0;//步数
	double c[6] = { 0, 0.5 * h, 0.5 * h, h, h, 0.5 * h };
	//h = 0.01;
	h = ConsParam.h;
	OutputClear();
	TT.push_back(0);
	XX.push_back(IniParam.x);  //水平位移初值
	YY.push_back(IniParam.y);  //垂直位移初值
	ZZ.push_back(IniParam.z);
	VX.push_back(IniParam.vx);//水平分速初值
	VY.push_back(IniParam.vy);//垂直分速初值
	VZ.push_back(IniParam.vz);
	P.push_back(IniParam.p);//大气压力
	V.push_back(sqrt(VX[0] * VX[0] + VY[0] * VY[0] + VZ[0] * VZ[0]));
	INPT(i);
	Prwxml.MyOutParam.t.push_back(u[6]);
	Prwxml.MyOutParam.x.push_back(u[3]);
	Prwxml.MyOutParam.y.push_back(u[4]);
	Prwxml.MyOutParam.z.push_back(u[5]);
	Prwxml.MyOutParam.vx.push_back(u[0]);
	Prwxml.MyOutParam.vy.push_back(u[1]);
	Prwxml.MyOutParam.vz.push_back(u[2]);
	Prwxml.MyOutParam.v.push_back(sqrt(u[0]* u[0]+ u[1]* u[1]));
	Prwxml.MyOutParam.p.push_back(u[7]);
	while (u[4] >= endH)
	{
		INPT(i);		
		i = i + 1;
		RK(8, h, u, f);
		OUT();
	}

	cout << "计算结束。X=" << u[3]<<"m"<< endl;
}

void OBCal::InputParam(string inputXmlPath)
{
	Prwxml.readtxt(inputXmlPath);
	Constant(Prwxml.MyConsParam);
	Inital(Prwxml.MyInitParam);
}

void OBCal::OutputParam(string outputXmlPath)
{
	Prwxml.writetxt(outputXmlPath);
}

void OBCal::RK(int n, double h, double u[], double f[])
{
	int i, j;
	double t, ts;
	double p[8];
	double w[8];

	double c[6] = { 0, 0.5 * h, 0.5 * h, h, h, 0.5 * h };
	t = 0;
	ts = t;
	for (i = 0; i < n; i++)
	{
		p[i] = u[i];
		w[i] = u[i];
	}
	for (j = 0; j < 4; j++)
	{
		FCT(p, f);
		t = ts + c[j];
		for (i = 0; i < n; i++)
		{
			p[i] = c[j] * f[i] + w[i];
			u[i] = c[j + 1] * f[i] / 3.0 + u[i];
		}
	}
}

void OBCal::FCT(double u[], double f[])
{
	double Tau, vr, sonic;
	double c = ConsParam.c;//弹形系数

	//H=l_H/d+l_t/d-0.3;	//l_H是弹头部长度，l_t是尾锥部长度，d是弹径
	//i=2.900-1.373*H+0.320*H*H0.026*H*H*H;
	//c=i*d*d/me3;
	
	Tau = T_y(u[4]);

	vr = sqrt(pow(u[0], 2) + pow(u[1], 2) + pow(u[2] , 2));
	sonic = 20.045 * sqrt(Tau);//音速

	f[0] = -c * H(u[4])*G(vr, sonic) * (u[0]);											//		dvx/dt=-c*H(y)*G(v,cs)*vx
	f[1] = -c * H(u[4])*G(vr, sonic) * u[1] - ConsParam.G0;				//		dvy/dt=-c*H(y)*G(v,cs)*vy-g
	f[2] = -c * H(u[4])*G(vr, sonic) * (u[2]);											//		dvz/dt=-c*H(y)*G(v,cs)*vz			
	//f[2] = 0;
	f[3] = u[0];																					//		dx/dt=vx
	f[4] = u[1];																					//		dy/dt=vy
	f[5] = u[2];																					//		dz/dt=vz
//	f[5] = 0;
	f[6] = 1.0;
	f[7]=-u[7]/ ConsParam.R1/Tau* ConsParam.G0*u[1];					//		dp/dt=ρ*g*vy	，ρ=p/R1/τ
}

double OBCal::T_y(double y)
{
	double a = 230.2, b = 0.006328, c = 1.172e-6;
	double T0 = 289.9;
	double Tau = 0;
	if (y <= 9300)
		Tau = ConsParam.tau0n - ConsParam.G * y;
	if (y > 9300 && y <= 12000)
		Tau = a - b * (y - 9300) + c * (y - 9300) * (y - 9300);
	if (y > 12000)
		Tau = 221.7;
	return Tau;
}

double OBCal::H(double y)
{
	//double T0n = 288.9, R1 = 287,rho0n=1.205;//标准温度τ0n=288.9K,空气气体常数R1=287J/(kg*K),ρ0n=1.205kg/m³
	double rho, p, tau;//空气密度ρ，气压，虚温τ
	double val;

	/*if (y <= 9300)
		val = pow(1 - y * 2.1904E-5, 4.4);
	else*/
	{
		p = u[7] ;
		tau = T_y(u[4]);
		rho = p / ConsParam.R1 / tau;
		val = rho / ConsParam.rho0n;
	}
		
	
	return val;
}

double OBCal::G(double v, double cs)
{
	double rho0n = 1.205;//标准大气密度ρ0n=1.205kg/m³
	double val;
	val = PI / 8000 * rho0n*Cx0(v / cs)*v;
	return val;
}

double OBCal::Cx0(double Ma)
{
	int f = 0;
	double MA[] = { 0.10, 0.70, 0.80, 0.90, 0.92, 0.94, 0.96, 0.98, 1.0, 1.03, 1.10, 1.20, 1.30, 1.50, 1.70, 1.90, 2.0, 2.50, 3.0, 3.50, 4.0 };
	double CX0[] = { 0.157, 0.157, 0.159, 0.184, 0.204, 0.234, 0.270, 0.302, 0.325, 0.351, 0.378, 0.384, 0.379, 0.362, 0.342, 0.323, 0.317, 0.313, 0.270, 0.263, 0.260 };
	double val;
	for (f = 0; f < 21; f++)
		if (Ma <= MA[f]) break;
	val = Interpolation(50000, Ma, MA, CX0);
	return val;
}

double OBCal::Interpolation(int n, double x, double a[], double b[])
{
	
	int n1, i;
	double a1, a2, a3, u, v, w, y;
	n1 = n - 2;
	for (i = 0; i < n1; i++)
	{
		if (x <= a[i + 1]) goto Loop1;
	}
	i = n - 2;
Loop1:
	if (i == 0) goto Loop2;
	if ((x - a[i]) >= (a[i + 1] - x)) goto Loop2;
	i = i - 1;
Loop2:
	a1 = a[i];
	a2 = a[i + 1];
	a3 = a[i + 2];
	u = (x - a2) * (x - a3) / ((a1 - a2) * (a1 - a3));
	v = (x - a1) * (x - a3) / ((a2 - a1) * (a2 - a3));
	w = (x - a1) * (x - a2) / ((a3 - a1) * (a3 - a2));
	y = u * b[i] + v * b[i + 1] + w * b[i + 2];
	return (y);
}
