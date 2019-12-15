#include "pch.h"
#include "adjust.h"


void adjust::set(vector<double> X, vector<double> Y, vector<double> T)
{
	MyConsParam.c = 1;
	MyConsParam.G = 6.328E-3;
	MyConsParam.G0 = 9.80665;
	MyConsParam.p0n = 100e3;
	MyConsParam.R0 = 6356766;
	MyConsParam.R1 = 287;
	MyConsParam.rho0n = 1.205;
	MyConsParam.T0n = 288015;
	MyConsParam.tau0n = 289.1;
	MyConsParam.h = 0.01;

	MyInitParam.p = MyConsParam.p0n;//不太对，以后再改
	MyInitParam.t = T[0];
	MyInitParam.vx = (X[X.size() - 1] - X[0]) / (T[T.size() - 1] - T[0]);
	MyInitParam.vy = (Y[Y.size() - 1] - Y[0]) / (T[T.size() - 1] - T[0]);
	MyInitParam.x = X[0];
	MyInitParam.y = Y[0];

	deltaVx = 0;
	deltaVy = 0;
	deltaX = 0;
	deltaY = 0;
}

adjust::adjust()
{
}


adjust::~adjust()
{
}

void adjust::Adjust(vector<double> X, vector<double> Y, vector<double> T)
{
	set(X,Y,T);
	double c1=0, c2=5;
	while (true)
	{
		if (deltaX > 0)
		{
			MyConsParam.c =(MyConsParam.c+c1)/2;
			c2 = MyConsParam.c;
		}
		if (deltaX < 0)
		{
			MyConsParam.c = (MyConsParam.c + c2) / 2;
			c1 = MyConsParam.c;
		}
		deltaX = 0;
		deltaY = 0;
		cout << "c=" << MyConsParam.c << endl;
		
		//调整速度使得起止点符合
		while (true)
		{
			MyInitParam.vx = MyInitParam.vx+ deltaVx;
			MyInitParam.vy = MyInitParam.vy+ deltaVy;
	
			MyOBCal.Simu(MyInitParam, MyConsParam);

			for (int i = 0; i < MyOBCal.TT.size(); i++)
			{
				if (MyOBCal.TT[i] >= T[T.size() - 1])
				{
					deltaVx= (X[X.size() - 1] - X[0]) / (T[T.size() - 1] - T[0])- (MyOBCal.XX[i] - MyOBCal.XX[0]) / (MyOBCal.TT[i] - MyOBCal.TT[0]);
					deltaVy = (Y[Y.size() - 1] - Y[0]) / (T[T.size() - 1] - T[0]) - (MyOBCal.YY[i] - MyOBCal.YY[0]) / (MyOBCal.TT[i] - MyOBCal.TT[0]);
					break;
				}
			}
			if (fabs(deltaVx*T[T.size() - 1]) <= 1&&fabs(deltaVy*T[T.size() - 1] )<= 1)
				break;
		}

		//计算每个点的误差
		for (int i = 0; i <T.size(); i++)
		{
			for (int j = 0;j < MyOBCal.TT.size(); j++)
			{
				if (MyOBCal.TT[j] >= T[i])
				{
					if (MyOBCal.XX[j] - X[i] >= deltaX)
						deltaX = MyOBCal.XX[j] - X[i];
					if (MyOBCal.YY[j] - Y[i] >= deltaY)
						deltaY = MyOBCal.YY[j] - Y[i];
					cout << MyOBCal.XX[j] - X[i]<<"\t"<< MyOBCal.YY[j] - Y[i]<<endl;
					break;
				}
			}
		}

		if (fabs(deltaX) < 30 && fabs(deltaY) < 35)
			cout << "vx=" << MyInitParam.vx << ";vy=" << MyInitParam.vy << endl;
			break;		
	}
	cout << "落点：\n" << MyOBCal.XX[MyOBCal.XX.size() - 1] << "\t" << MyOBCal.YY[MyOBCal.YY.size() - 1] << endl;
	//计算炮位
	/*MyInitParam.vx = -MyInitParam.vx;
	MyInitParam.vy = -MyInitParam.vy;
	MyConsParam.c = -MyConsParam.c;*/
	MyConsParam.h = -MyConsParam.h;
	MyOBCal.Simu(MyInitParam, MyConsParam,"计算炮位.txt");
	cout << "炮位：\n" << MyOBCal.XX[MyOBCal.XX.size() - 1] << "\t" << MyOBCal.YY[MyOBCal.YY.size() - 1] << endl;
	startPoint.X = MyOBCal.XX[MyOBCal.XX.size() - 1];
	startPoint.Y = MyOBCal.YY[MyOBCal.YY.size() - 1];
	
}

	

