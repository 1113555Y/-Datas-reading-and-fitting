#include "pch.h"

#include "LeastSquare.h"


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
	
	x = { 0,1,2,3,4,5,6,7,8,9 };
	f_x = { 1,3,7,13,21,31,43,57,73,91 };
	w = { 1,1,1,1,1,1,1,1,1,1 };
	/*x = { 1,2,3,4,5};
	f_x = {4,4.5,6,8,8.5 };
	w = { 2,1,3,1,1 };*/
}

void LeastSquare::Gauss()
{

	double temp[15], d;


	cout << "��������������Ϊ:\n";

	for (int i = 0; i < wx.size(); i++)
	{
		for (int j = 0; j < wx[i].size(); j++)
		{
			cout << wx[i][j] << "\t";
		}
		cout << endl;
	}

	int m, n, i, j, k;
	m = wx.size();
	n = wx[1].size() - 1;

	for (k = 0; k < n - 1; k++) //������Ԫ���ֵ
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
			cout << "�޷�����" << endl;
			return;
		}
		if (k != hang) //����
		{
			for (i = 0; i < m + 1; i++)
			{
				temp[i] = wx[k][i];
				wx[k][i] = wx[hang][i];
				wx[hang][i] = temp[i];
			}
		}
		cout << "ѡ����Ԫ:\n";
		for (i = 0; i < m; i++)
		{
			for (j = 0; j < n + 1; j++)
			{
				cout << wx[i][j] << " ";
			}
			cout << "\n";
		}
		for (i = k + 1; i < m; i++) //��Ԫ
		{
			double d = wx[i][k] / wx[k][k];
			for (j = 0; j < n + 1; j++)
			{
				wx[i][j] = wx[i][j] - d * wx[k][j];
			}
		}
		cout << "��Ԫ:\n";
		for (i = 0; i < m; i++)
		{
			for (j = 0; j < n + 1; j++)
			{
				cout << wx[i][j] << " ";
			}
			cout << "\n";
		}
	}
	memset(temp, 0, 15 * sizeof(float)); //��temp��0��׼����Ž�����
	for (i = m - 1; i >= 0; i--) //�������
	{
		d = 0;
		for (k = 0; k < n; k++)
		{
			d = d + temp[k] * wx[i][k];
		}
		temp[i] = (wx[i][n] - d) / wx[i][i];
	}
	cout << "�˷�����Ľ�����ת��Ϊ��("; //���������
	for (i = 0; i < m; i++)
	{
		cout << " "   << temp[i];//5λС��
	}
	cout << " )" << endl;

	cout << "��ϵķ���Ϊ��y=" ;
	for (int i = 0; i < wx.size(); i++)
	{
		cout << "+" << temp[i] << "*x^" << i;
	}
	cout << endl;





	//for (int j = 0; j < wx[j].size() - 1; j++) //������Ԫ���ֵ
	//{
	//	double max = 0;
	//	int hang = 0, num = 0;
	//	for (int i = j; i < wx[j].size(); i++)
	//	{
	//		if (fabs(wx[i][j]) > max)
	//		{
	//			max = fabs(wx[i][j]);
	//			hang = i;
	//		}
	//	}
	//	if (wx[hang][j] == 0)
	//	{
	//		cout << "�޷�����" << endl;
	//		return;
	//	}
	//	if (j != hang) //����
	//	{
	//		for (int i = 0; i < wx.size(); i++)
	//		{
	//			double temp = wx[i][j];
	//			wx[i][j] = wx[hang][j];
	//			wx[hang][j] = temp;
	//		}
	//	}
	//	cout << "ѡ����Ԫ:\n";
	//	for (int i = 0; i < wx.size(); i++)
	//	{
	//		for (int j = 0; j < wx[i].size(); j++)
	//		{
	//			cout << wx[i][j] << " ";
	//		}
	//		cout << "\n";
	//	}

	//	//for (i = k + 1; i < m; i++) //��Ԫ
	//	//{
	//	//	d = a[i][k] / a[k][k];
	//	//	for (j = 0; j < n + 1; j++)
	//	//	{
	//	//		a[i][j] = a[i][j] - d * a[k][j];
	//	//	}
	//	//}
	//	//cout << "��Ԫ:\n";
	//	//for (i = 0; i < m; i++)
	//	//{
	//	//	for (j = 0; j < n + 1; j++)
	//	//	{
	//	//		cout << a[i][j] << " ";
	//	//	}
	//	//	cout << "\n";
	//	//}
	//}

}

LeastSquare::LeastSquare()
{
}


LeastSquare::~LeastSquare()
{
}

void LeastSquare::fitting(string inputXmlPath , int N )
{
	get_data(inputXmlPath);

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




}

	

	


