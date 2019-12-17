#include "pch.h"
#include "adjust.h"


void adjust::set(vector<SCoordinate> MyCoordinate, SRadarCoordinate Radar)
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

	MyConsParam.endH = Radar.endH;

	MyInitParam.p = MyConsParam.p0n;//不太对，以后再改
	MyInitParam.t = MyCoordinate[0].t;

	MyInitParam.vx = (MyCoordinate[MyCoordinate.size() - 1].X - MyCoordinate[0].X) / (MyCoordinate[MyCoordinate.size() - 1].t - MyCoordinate[0].t);
	MyInitParam.vy = (MyCoordinate[MyCoordinate.size() - 1].Y - MyCoordinate[0].Y) / (MyCoordinate[MyCoordinate.size() - 1].t - MyCoordinate[0].t);
	MyInitParam.x = MyCoordinate[0].X;
	MyInitParam.y = MyCoordinate[0].Y;

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

void adjust::Adjust(vector<SCoordinate> MyCoordinate, SRadarCoordinate Radar)
{
	set(MyCoordinate, Radar);
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
				if (MyOBCal.TT[i] >= MyCoordinate[MyCoordinate.size() - 1].t)
				{
					deltaVx= (MyCoordinate[MyCoordinate.size() - 1].X - MyCoordinate[0].X) / (MyCoordinate[MyCoordinate.size() - 1].t- MyCoordinate[0].t)- (MyOBCal.XX[i] - MyOBCal.XX[0]) / (MyOBCal.TT[i] - MyOBCal.TT[0]);
					deltaVy = (MyCoordinate[MyCoordinate.size() - 1].Y - MyCoordinate[0].Y) / (MyCoordinate[MyCoordinate.size() - 1].t - MyCoordinate[0].t) - (MyOBCal.YY[i] - MyOBCal.YY[0]) / (MyOBCal.TT[i] - MyOBCal.TT[0]);
					break;
				}
			}
			if (fabs(deltaVx*MyCoordinate[MyCoordinate.size() - 1].t) <= 1&&fabs(deltaVy*MyCoordinate[MyCoordinate.size() - 1].t)<= 1)
				break;
		}

		//计算每个点的误差
		for (int i = 0; i < MyCoordinate.size(); i++)
		{
			for (int j = 0;j < MyOBCal.TT.size(); j++)
			{
				if (MyOBCal.TT[j] >= MyCoordinate[i].t)
				{
					if (MyOBCal.XX[j] - MyCoordinate[i].X >= deltaX)
						deltaX = MyOBCal.XX[j] - MyCoordinate[i].X;
					if (MyOBCal.YY[j] - MyCoordinate[i].Y >= deltaY)
						deltaY = MyOBCal.YY[j] - MyCoordinate[i].Y;
					cout << MyOBCal.XX[j] - MyCoordinate[i].X<<"\t"<< MyOBCal.YY[j] - MyCoordinate[i].Y<<endl;
					break;
				}
			}
		}

		if (fabs(deltaX) < 30 && fabs(deltaY) < 35)
		{
			endPoint.X = MyOBCal.XX[MyOBCal.XX.size() - 1];
			endPoint.Y = MyOBCal.YY[MyOBCal.YY.size() - 1];
			cout << "vx=" << MyInitParam.vx << ";vy=" << MyInitParam.vy << endl;
			break;		
		}
			
			
	}
	cout << "落点：\n" << MyOBCal.XX[MyOBCal.XX.size() - 1] << "\t" << MyOBCal.YY[MyOBCal.YY.size() - 1] << endl;
	//计算炮位
	MyConsParam.h = -MyConsParam.h;
	MyConsParam.endH = Radar.startH;
	MyOBCal.Simu(MyInitParam, MyConsParam,"计算炮位.txt");
	cout << "炮位：\n" << MyOBCal.XX[MyOBCal.XX.size() - 1] << "\t" << MyOBCal.YY[MyOBCal.YY.size() - 1] << endl;
	startPoint.X = MyOBCal.XX[MyOBCal.XX.size() - 1];
	startPoint.Y = MyOBCal.YY[MyOBCal.YY.size() - 1];
	

}

	

