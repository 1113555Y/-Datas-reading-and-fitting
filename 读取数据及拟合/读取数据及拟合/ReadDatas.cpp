#include "pch.h"
#include "ReadDatas.h"


//vector<double> ReadDatas::splitBySeparator(const string & s, const string seperator)
//	{
//	vector<double> result;
//	typedef string::size_type string_size;
//	string_size i = 0;
//
//	while (i != s.size())
//	{
//		//找到字符串中首个不等于分隔符的字母；
//		int flag = 0;
//		while (i != s.size() && flag == 0)
//		{
//			flag = 1;
//			for (string_size x = 0; x < seperator.size(); ++x)
//				if (s[i] == seperator[x])
//				{
//					++i;
//					flag = 0;
//					break;
//				}
//		}
//		//找到又一个分隔符，将两个分隔符之间的字符串取出；
//		flag = 0;
//		string_size j = i;
//		while (j != s.size() && flag == 0)
//		{
//			for (string_size x = 0; x < seperator.size(); ++x)
//				if (s[j] == seperator[x])
//				{
//					flag = 1;
//					break;
//				}
//			if (flag == 0)
//				++j;
//		}
//		if (i != j)
//		{
//			result.push_back(atof(s.substr(i, j - i).c_str()));
//			i = j;
//		}
//	}
//	return result;
//}

vector<string> ReadDatas::splitBySeparator(const string & s, const string seperator)
{
	vector<string> result;

	int pos = 0;
	string tmp = s;
	pos = tmp.find(seperator);
	while (pos != string::npos)
	{
		if (pos != 0)
		{
			if (pos == tmp.size() - 1)
			{
				break;
			}
			string prepart = tmp.substr(0, pos);
			result.push_back(prepart);

		}
		else
		{
			//result.push_back("");
		}
		if (pos == tmp.size() - 1)
		{
			break;
		}
		else
		{
			tmp = tmp.substr(pos + 1);
		}

		pos = tmp.find(seperator);
	}

	result.push_back(tmp);
	return(result);
}

vector<double> ReadDatas::getdatas(const string & s)
{
	int start, end;
	vector<double> result;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] >= '0'&&s[i] <= '9')
		{
			start = i;
			for (int j = i; j < s.size(); j++)
			{
				if (((s[j] < '0' || s[j] > '9') && s[j] != '.'&&s[j] != 'e'&&s[j] != 'E')||j==s.size()-1)
				{
					end = j;
					result.push_back(atof(s.substr(i, j - i+1).c_str()));
					i = j;
					break;
				}				
			}	
			
		}
		
	}
	return result;
}



void ReadDatas::readtxt(string OriginalDatasPath, string RadarCoordinatePath)
{
	char str[100];
	vector<string> result_s;
	vector<double> result;
	ifstream fin(OriginalDatasPath);

	fin.getline(str, 500);
	//cout << str<<endl;




	while(true)
	{
		fin.getline(str, 500);
		result = getdatas(str);
		if (result.size() == 0)
			break;
		MyOriginalDatas.t.push_back(result[0]);
		MyOriginalDatas.Azimuth.push_back(result[1]);
		MyOriginalDatas.Elevation.push_back(result[2]);
		MyOriginalDatas.Range.push_back(result[3]);
		//cout << result[0] << "\t" << result[1] << "\t" << result[2] << "\t" << result[3] << "\n";
	}
	fin.close();

	ifstream fin2(RadarCoordinatePath);
	
	fin2.getline(str, 100);
	cout << str << endl;
	for(int i=0;i<4;i++)
	{
		fin2.getline(str, 100);
		result = getdatas(str);
		if (result.size() == 0)
			break;
		MyRadarCoordinate.Param[i]=(result[0]);
		

		//MyRadarCoordinate.Longitude = result[1];
		//cout << result[1] << "\t" << result[2] << "\t" << result[3] << "\t" << result[4] << "\n";
	}
	MyRadarCoordinate.Longitude = MyRadarCoordinate.Param[0];
	MyRadarCoordinate.Latitude = MyRadarCoordinate.Param[1];
	MyRadarCoordinate.Height = MyRadarCoordinate.Param[2];
	MyRadarCoordinate.ReferenceHeight = MyRadarCoordinate.Param[3];
	cout <<  "经度(度)\t" <<  "纬度(度)\t" << "高(米)\t" << "基准面高度(米)\n";
	cout << MyRadarCoordinate.Longitude << "\t" << MyRadarCoordinate.Latitude << "\t" << MyRadarCoordinate.Height << "\t" << MyRadarCoordinate.ReferenceHeight << "\n";
	fin2.close();
}

ReadDatas::ReadDatas()
{
}


ReadDatas::~ReadDatas()
{
}
