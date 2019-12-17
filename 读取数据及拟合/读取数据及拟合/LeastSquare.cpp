#include "pch.h"
#include "LeastSquare.h"


void LeastSquare::setCoordinate(SOriginalDatas OriginalDatas)
{
	SCoordinate Coordinate;
	vector<double>temp_x, temp_y;
	
	for (int i = 0; i < OriginalDatas.t.size(); i++)
	{
		Coordinate.Azimuth = OriginalDatas.Azimuth[i];
		Coordinate.Elevation = OriginalDatas.Elevation[i];
		Coordinate.Range = OriginalDatas.Range[i];
		Coordinate.t = OriginalDatas.t[i];
		MyCoordinate.push_back(Coordinate);
		MyCoordinate[i] = SphericalToCartesian(MyCoordinate[i]);
		temp_x.push_back(MyCoordinate[i].x);
		temp_y.push_back(MyCoordinate[i].y);
	}
	temp_y = fitting(temp_x, temp_y, 1);
	for (int i = 0; i < temp_x.size(); i++)
	{
		MyCoordinate[i].y = temp_y[i];
		MyCoordinate[i] = xyzToXY(MyCoordinate[i]);
	}
}

void LeastSquare::SphericalToCartesian(vector<double> Azimuth, vector<double> Elevation, vector<double> Range)
{

	x.clear();
	y.clear();
	z.clear();
	f_x.clear();
	w.clear();
	for (int i = 0; i < Range.size(); i++)
	{	
		x.push_back(Range[i]*cos(Elevation[i])*cos(Azimuth[i]));
		y.push_back(Range[i] * cos(Elevation[i])*sin(-Azimuth[i]));
		z.push_back(Range[i] * sin(Elevation[i]));
		w.push_back(1);
	}

}

SCoordinate LeastSquare::SphericalToCartesian(SCoordinate point)
{
	point.x = point.Range*cos(point.Elevation)*cos(point.Azimuth);
	point.y = point.Range*cos(point.Elevation)*sin(-point.Azimuth);
	point.z = point.Range*sin(point.Elevation);

	return point;
}

SCoordinate LeastSquare::xyzToXY(SCoordinate point)
{
	point.X = sqrt((point.x-MyCoordinate[0].x)*(point.x - MyCoordinate[0].x) + (point.y - MyCoordinate[0].y) +( point.y - MyCoordinate[0].y));
	point.Y = point.z;

	return point;
}

double LeastSquare::sigma(vector<double> Array, int size)
{
	double val=0;
	for (int i = 0; i < size; i++)
		val += Array[i];
	return val;
}

void LeastSquare::get_data(string OriginalDatasPath)
{

	MyReadDatas.readtxt(OriginalDatasPath);
	SphericalToCartesian(MyReadDatas.MyOriginalDatas.Azimuth, MyReadDatas.MyOriginalDatas.Elevation, MyReadDatas.MyOriginalDatas.Range);
	//f_x = MyReadDatas.MyOriginalDatas.t;

	cout << "x\t" << "y\t" << "z\t" << "t" << endl;
	for (int i = 0; i < MyReadDatas.MyOriginalDatas.t.size();i++)
	{
		cout << x[i] << "\t" << y[i] << "\t" << z[i] << "\t" << MyReadDatas.MyOriginalDatas.t[i] << endl;
	}
	cout << "坐标转换完成" << endl;

	/*x = { 0,1,2,3,4,5,6,7,8,9 };
	f_x = { 1,3,7,13,21,31,43,57,73,91 };
	w = { 1,1,1,1,1,1,1,1,1,1 };
	x = { 1,2,3,4,5};
	f_x = {4,4.5,6,8,8.5 };
	w = { 2,1,3,1,1 };*/
}

vector<double>LeastSquare::Gauss()
{
	vector<double>val;
	double temp[15], d;

	int m, n, i, j, k;
	m = wx.size();
	n = wx[1].size() - 1;

	for (k = 0; k < n - 1; k++) //找列主元最大值
	{
		double max = 0;
		int hang = 0, num = 0;
		for (i = k; i < n; i++)
		{
			if (fabs(wx[i][k]) > max)
			{
				max = fabs(wx[i][k]);
				hang = i;
			}
		}
		if (wx[hang][k] == 0)
		{
			cout << "无法计算" << endl;
			
		}
		if (k != hang) //换行
		{
			for (i = 0; i < m + 1; i++)
			{
				temp[i] = wx[k][i];
				wx[k][i] = wx[hang][i];
				wx[hang][i] = temp[i];
			}
		}
		/*cout << "选列主元:\n";
		for (i = 0; i < m; i++)
		{
			for (j = 0; j < n + 1; j++)
			{
				cout << wx[i][j] << " ";
			}
			cout << "\n";
		}*/
		for (i = k + 1; i < m; i++) //消元
		{
			double d = wx[i][k] / wx[k][k];
			for (j = 0; j < n + 1; j++)
			{
				wx[i][j] = wx[i][j] - d * wx[k][j];
			}
		}
		/*cout << "消元:\n";
		for (i = 0; i < m; i++)
		{
			for (j = 0; j < n + 1; j++)
			{
				cout << wx[i][j] << " ";
			}
			cout << "\n";
		}*/
	}
	memset(temp, 0, 15 * sizeof(float)); //将temp清0，准备存放解向量
	for (i = m - 1; i >= 0; i--) //求解向量
	{
		d = 0;
		for (k = 0; k < n; k++)
		{
			d = d + temp[k] * wx[i][k];
		}
		temp[i] = (wx[i][n] - d) / wx[i][i];
	}

	cout << "拟合的方程为：y=" ;
	for (int i = 0; i < wx.size(); i++)
	{
		cout << "+" << temp[i] << "*x^" << i;
		val.push_back(temp[i]);
	}
	cout << endl;

	return val;
}

LeastSquare::LeastSquare()
{
}


LeastSquare::~LeastSquare()
{
}
vector<double> LeastSquare::fitting(vector<double> x, vector<double> y, int N)
{
		f_x = y;
		N = 1;
		wx.resize(N + 1);

		for (int i = 0; i <= N; i++)
		{
			for (int j = 0; j <= N; j++)
			{
				wx_n.clear();
				for (int k = 0; k < x.size(); k++)
				{
					wx_n.push_back( pow(x[k], i + j));
				}
				wx[i].push_back(sigma(wx_n, wx_n.size()));
			}
		}
		for (int i = 0; i <= N; i++)
		{
			wxf_n.clear();
			for (int k = 0; k < x.size(); k++)
			{
				wxf_n.push_back(pow(x[k], i)*f_x[k]);
			}
			wx[i].push_back(sigma(wxf_n, wxf_n.size()));
		}
		for (int i = 0; i <= N; i++)
		{
			/*for (int j = 0; j <= N + 1; j++)
			{
				cout << wx[i][j] << "\t";
			}
			cout << endl;*/
		}
		vector<double>a=Gauss();

		for (int i = 0; i < x.size(); i++)
		{
			y[i] = 0;
			for (int j = 0; j < N+1; j++)
			{
			y[i] = y[i] +a[j]* pow(x[i],j);
			}
		}
		return y;
}
void LeastSquare::fitting(string inputXmlPath , int N )
{
	get_data(inputXmlPath);
	f_x = y;
	N = 1;
	wx.resize(N + 1);

	for (int i = 0; i <=  N; i++)
	{
		for (int j = 0; j <= N; j++)
		{
			wx_n.clear();
			for (int k = 0; k < x.size(); k++)
			{
				wx_n.push_back(w[k] * pow(x[k], i+j));
			}
			wx[i].push_back(sigma(wx_n, wx_n.size()));
		}
	}
	for (int i = 0; i <= N; i++)
	{
		wxf_n.clear();
		for (int k = 0; k < x.size(); k++)
		{
			wxf_n.push_back(w[k] * pow(x[k], i )*f_x[k]);
		}
		//Vector_wxf(i)= sigma(wxf_n,wxf_n.size());
		wx[i].push_back(sigma(wxf_n, wxf_n.size()));
	}
	for (int i = 0; i <= N; i++)
	{
		for (int j = 0; j <= N+1; j++)
		{
			//Matrix_wx(i,j)=wx[i][j];
			cout << wx[i][j] << "\t";
		}
		cout << endl;
	}
	/*for (int i = 0; i <= N; i++)
	{
		cout<<Vector_wxf [i]<<endl;
	}*/

	Gauss();
	for (int i = 0; i < x.size(); i++)
	{
		X.push_back(sqrt((x[i]-x[0]) * (x[i]-x[0]) + (y[i]-y[0]) * (y[i]-y[0])));
		Y.push_back(z[i]);
		T.push_back(MyReadDatas.MyOriginalDatas.t[i]);
	}
}

void LeastSquare::fitting(SOriginalDatas inputOriginalDatas)
{
	cout << "坐标转换完成" << endl;
	f_x = y;
	int N = 1;
	wx.resize(N + 1);

	for (int i = 0; i <= N; i++)
	{
		for (int j = 0; j <= N; j++)
		{
			wx_n.clear();
			for (int k = 0; k < x.size(); k++)
			{
				wx_n.push_back(w[k] * pow(x[k], i + j));
			}
			wx[i].push_back(sigma(wx_n, wx_n.size()));
		}
	}
	for (int i = 0; i <= N; i++)
	{
		wxf_n.clear();
		for (int k = 0; k < x.size(); k++)
		{
			wxf_n.push_back(w[k] * pow(x[k], i)*f_x[k]);
		}
		//Vector_wxf(i)= sigma(wxf_n,wxf_n.size());
		wx[i].push_back(sigma(wxf_n, wxf_n.size()));
	}
	for (int i = 0; i <= N; i++)
	{
		for (int j = 0; j <= N + 1; j++)
		{
			cout << wx[i][j] << "\t";
		}
		cout << endl;
	}

	Gauss();
	for (int i = 0; i < x.size(); i++)
	{
		X.push_back(sqrt((x[i] - x[0]) * (x[i] - x[0]) + (y[i] - y[0]) * (y[i] - y[0])));
		Y.push_back(z[i]);
		T.push_back(inputOriginalDatas.t[i]);
	}
}



void LeastSquare::CartesianToSpherical(double X, double Y, double Z)
{

}

SCoordinate LeastSquare::CartesianToSpherical(SCoordinate point)
{
	SCoordinate Coordinate;


	return SCoordinate();
}

SCoordinate LeastSquare::XYtoxyz(SCoordinate point)
{

	point.x = MyCoordinate[0].x + point.X / MyCoordinate[1].X * (MyCoordinate[1].x - MyCoordinate[0].x);
	point.y = MyCoordinate[0].y + point.X / MyCoordinate[1].X * (MyCoordinate[1].y - MyCoordinate[0].y);

	/*
	point.x = MyCoordinate[0].x + point.X*cos(atan((MyCoordinate[1].y- MyCoordinate[0].y)/(MyCoordinate[1].x - MyCoordinate[0].x)));
	point.y = MyCoordinate[0].y + point.X*sin(atan((MyCoordinate[1].y - MyCoordinate[0].y) / (MyCoordinate[1].x - MyCoordinate[0].x)));
	*/
	point.z = point.Y;
	return point;
}

SCoordinate LeastSquare::xyzToRAE(SCoordinate point)
{
	point.Range = sqrt(point.x*point.x + point.y + point.y + point.z + point.z);
	if (sqrt(point.x*point.x + point.y + point.y)==0)
	{
		point.Elevation = 0;
	}
	else
	{
		point.Elevation = atan(point.z / sqrt(point.x*point.x + point.y + point.y));
	}

	if (point.x > 0)
	{
		if (point.y >= 0)
		{
			point.Azimuth =2 * PI -atan(point.y / point.x);
		}
		else
		{
			cout<< -atan(point.y / point.x);
			point.Azimuth =  - atan(point.y / point.x);
		}
	}
	else if (point.x == 0)
	{
		if (point.y > 0)
		{
			point.Azimuth = PI*3/2;
		}
		else if (point.y < 0)
		{
			point.Azimuth = PI/2;
		}
		else if (point.y == 0)
		{
			point.Azimuth = 0;
		}
	}
	else if(point.x<0)
	{
		point.Azimuth = PI - atan(point.y / point.x);
	}
	

	return point;
}

	

	


