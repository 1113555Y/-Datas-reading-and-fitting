#pragma once
#define  PI 3.141593
# include <string>
# include <map>
# include <vector>

using namespace std;

struct MyDataNode
{
	string nodeName;  //节点名称，例如:root,paraclass,param
	map<string, string> attributes;// 属性名称和值
	vector<MyDataNode> childNodes;//子节点
};



typedef struct
{
	double Azimuth, Elevation, Range;//方位角(rad)//仰角(rad)	//距离(km)

	double Longitude, Latitude, Height;//经度(°)//纬度(°);//高(m)

	double X, Y;//2D弹道地面坐标

	double x, y, z;//雷达切平面直角坐标

	double t;//时间
}SCoordinate;	//坐标

typedef struct
{
	vector<double> t;
	vector<double> Azimuth;//方位角(rad)
	vector<double>Elevation;//仰角(rad)
	vector<double> Range;//距离(km)
}SOriginalDatas;		//原始数据

typedef struct
{
	//vector<double> Param;
	double Param[4];
	double Longitude;//经度(°)
	double Latitude;//纬度(°)
	double Height;//高(m)
	double  ReferenceHeight;//基准面高度(m)

	double startH;//炮位高度
	double endH;//落点高度
}SRadarCoordinate;		//站坐标

typedef struct {
	double G0;//地球表面重力加速度G0= 9.80665
	double R0;//地球半径R0= 6356766
	double w;//风速
	double theta_w;//风向
	double wx;
	double wy;
	double wz;
	double c;//弹道系数

	double R1;//空气气体常数R1=287J/(kg*K)
	double G;//温度递减率G = 6.328E-3

	//标准气象条件
	double T0n;//标准温度T0n=288.15K
	double p0n;//气压p0n=100kPa
	double tau0n;//虚温τ0n=289.1K
	double rho0n;//ρ0n=1.205kg/m³

	double h;//仿真步长h=0.01
	double endH;//终点高度=0
}SConsParam;	//输入常数

typedef struct
{
	double t;
	double v;
	double theta;
	double vx;
	double vy;
	double vz;
	double x;
	double y;
	double z;
	double p;
}SInitParam;	//初始参数

typedef struct
{
	vector<double> t;
	vector<double> vx;
	vector<double> vy;
	vector<double> vz;
	vector<double> v;
	vector<double> x;
	vector<double> y;
	vector<double> z;
	vector<double> p;
}SOutParam;		//输出参数


