// 读取数据及拟合.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include"读取数据及拟合.h"
#include"LeastSquare.h"
#include"OBCal.h"
#include "pch.h"
#include"LeastSquare.h"
#include"OBCal.h"
#include "adjust.h"
#include <iostream>

void run(SRadarCoordinate RadarCoordinate)
{

}


void run1(SOriginalDatas OriginalDatas, SRadarCoordinate RadarCoordinate)
{
	
#pragma region 雷达数据->2D弹道离散点
	LeastSquare MyLeastSquare;
	cout << "success" << endl;
	MyLeastSquare.setCoordinate(OriginalDatas);
	cout << "雷达数据确定的2D弹道" << endl;
	cout << " X\t" << "Y\t" << "T\n";
	for (int i = 0; i < MyLeastSquare.MyCoordinate.size(); i++)
	{
		cout << MyLeastSquare.MyCoordinate[i].X << "\t" << MyLeastSquare.MyCoordinate[i].Y << "\t" << MyLeastSquare.MyCoordinate[i].t<< "\n";
	}
#pragma endregion

#pragma region 外弹道计算
	adjust MyAdjust;
	MyAdjust.Adjust(MyLeastSquare.MyCoordinate, RadarCoordinate);

#pragma endregion


	MyAdjust.startPoint = MyLeastSquare.XYtoxyz(MyAdjust.startPoint);
	MyAdjust.endPoint= MyLeastSquare.XYtoxyz(MyAdjust.endPoint);
	MyAdjust.startPoint = MyLeastSquare.xyzToRAE(MyAdjust.startPoint);
	MyAdjust.endPoint = MyLeastSquare.xyzToRAE(MyAdjust.endPoint);
	cout << "炮位坐标(雷达切平面直角坐标)：\n北" << MyAdjust.startPoint.x << "西"<<MyAdjust.startPoint.y << "高"<<MyAdjust.startPoint.z<<endl;
	cout << "炮位坐标(雷达球坐标)：\nR=" << MyAdjust.startPoint.Range << "A=" << MyAdjust.startPoint.Azimuth << "E=" << MyAdjust.startPoint.Elevation << endl;
	cout << "落点坐标(雷达切平面直角坐标)：\n北" << MyAdjust.endPoint.x << "西"<<MyAdjust.endPoint.y << "高"<< MyAdjust.endPoint.z << endl;
	cout << "落点坐标(雷达球坐标)：\nR=" << MyAdjust.endPoint.Range << "A=" << MyAdjust.endPoint.Azimuth << "E=" << MyAdjust.endPoint.Elevation << endl;
}



int main()
{
	SRadarCoordinate inputRadarCoordinate;
	SOriginalDatas inputOriginalDatas;

	ReadDatas MyReadDatas;
	MyReadDatas.readtxt("SimDataH22.txt", "站坐标.txt");
	inputOriginalDatas.Azimuth = MyReadDatas.MyOriginalDatas.Azimuth;
	inputOriginalDatas.Elevation = MyReadDatas.MyOriginalDatas.Elevation;
	inputOriginalDatas.Range = MyReadDatas.MyOriginalDatas.Range;
	inputOriginalDatas.t = MyReadDatas.MyOriginalDatas.t;

	
	inputRadarCoordinate.Height = MyReadDatas.MyRadarCoordinate.Height;
	inputRadarCoordinate.Latitude = MyReadDatas.MyRadarCoordinate.Latitude;
	inputRadarCoordinate.Longitude = MyReadDatas.MyRadarCoordinate.Latitude;
	inputRadarCoordinate.ReferenceHeight = MyReadDatas.MyRadarCoordinate.Latitude;

	inputRadarCoordinate.startH = 100;
	inputRadarCoordinate.endH = 200;

	run1(inputOriginalDatas, inputRadarCoordinate);

	/*string  OriginalDatasPath = "SimDataH22.txt";
	string RadarCoordinatePath = "站坐标.txt";
	run(OriginalDatasPath, RadarCoordinatePath);*/
    std::cout << "Hello World!\n"; 
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
