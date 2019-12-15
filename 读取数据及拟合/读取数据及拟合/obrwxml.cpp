#include "pch.h"
#include "obrwxml.h"


obrwxml::obrwxml()
{
}


obrwxml::~obrwxml()
{
}

void obrwxml::readtxt(string  Path)
{
	char str[100];
	vector<double> result;
	ifstream fin;
	fin.open(Path);
	fin.getline(str, 100);
	result = splitBySeparator(str, ",");
	MyInitParam.v = result[0];
	MyInitParam.theta = result[1];

	MyConsParam.c = result[2];
	MyConsParam.w = result[3];
	MyConsParam.theta_w = result[4];
	

	MyInitParam.vx = result[0] * cos(result[1] / 180 * PI);
	MyInitParam.vy = result[0] * sin(result[1] / 180 * PI);
	MyInitParam.vz = 0;

	MyInitParam.x = 0;
	MyInitParam.y = 0;
	MyInitParam.z = 0;

	fin.close();
}

void obrwxml::writetxt(string  Path)
{
	ofstream file(Path);
	file << "vx(m/s)\tvy(m/s)\tvz(m/s)\tvr(m/s)\tx(m)\ty(m)\tz(m)\tt(s)\tP(kPa)" << endl;

	for (int i = 0; i < MyOutParam.t.size(); i++)
	{	
		file << MyOutParam.vx[i] << "\t" << MyOutParam.vy[i] << "\t" << 0 << "\t" << MyOutParam.v[i] << "\t" << MyOutParam.x[i] << "\t" << MyOutParam.y[i] << "\t" << 0 << "\t" << MyOutParam.t[i] << "\t" << MyOutParam.p[i]/1000 << endl;
	}
	file.close();
}

vector<double> obrwxml::splitBySeparator(const string & s, const string seperator)
{
	
	vector<double> result;
	typedef string::size_type string_size;
	string_size i = 0;

	while (i != s.size())
	{
		//找到字符串中首个不等于分隔符的字母；
		int flag = 0;
		while (i != s.size() && flag == 0)
		{
			flag = 1;
			for (string_size x = 0; x < seperator.size(); ++x)
				if (s[i] == seperator[x])
				{
					++i;
					flag = 0;
					break;
				}
		}
		//找到又一个分隔符，将两个分隔符之间的字符串取出；
		flag = 0;
		string_size j = i;
		while (j != s.size() && flag == 0)
		{
			for (string_size x = 0; x < seperator.size(); ++x)
				if (s[j] == seperator[x])
				{
					flag = 1;
					break;
				}
			if (flag == 0)
				++j;
		}
		if (i != j)
		{
			result.push_back(atof(s.substr(i, j - i).c_str()));
			i = j;
		}
	}
	return result;
	
}
