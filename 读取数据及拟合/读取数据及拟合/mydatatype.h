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
	vector<double> t;
	vector<double> Azimuth;//方位角(rad)
	vector<double>Elevation;//仰角(rad)
	vector<double> Range;//距离(km)
}SOriginalDatas;		//原始数据

typedef struct
{
	vector<double> Param;
	double Longitude;//精度(°)
	double Latitude;//纬度(°)
	double Height;//高(m)
	double  ReferenceHeight;//基准面高度(m)
}SRadarCoordinate;		//站坐标