#include <iostream>
#include<vector>
using namespace std;

void output(vector<vector<int>>matrix,int n);
void zifan(vector<vector<int>>matrix, int n);
void duichen(vector<vector<int>>matrix, int n);
void chuandi(vector<vector<int>>matrix, int n);

int main()
{
	int temp;//用于输入
	cout << "请输入矩阵的行数:";
	int n;//行(列)数
	//加入一些错误处理
	cin >> n;
	while (cin >> n)
	{
		if (n <= 0)
		{
			cout << "输入错误，请重新输入！" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else
			break;
	}
	vector<vector<int>>matrix(n,vector<int>(n));//用来存放关系矩阵的二维vector,直接初始化

	cout << "请输入关系矩阵:" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << endl;
		cout << "请输入矩阵的第" << i << "行元素(元素以空格分隔) :";
		for (int j = 0; j < n; j++)
		{
			cin >> temp;
			matrix[i][j]=temp;
		}
	}
	cout << "输入对应序号选择算法\nl:自反闭包\n2:传递闭包\n3:对称闭包\n4:退出" << endl;
	int choice;//选择序号
	//输入错误处理
	while (cin >> choice)
	{
		if (choice != 1 && choice != 2 && choice != 3 && choice != 4)
		{
			cout << "输入错误，请重新输入！" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else
			break;
	}
	switch (choice)
	{
	case 1:
		zifan(matrix,n);
		break;
	case 2:
		chuandi(matrix, n);
		break;
	case 3:
		duichen(matrix, n);
		break;
	case 4:
		break;
	default:
		break;
	}
	return 0;
}



void output(vector<vector<int>>matrix,int n)
{
	cout << "所求关系矩阵为:" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << matrix[i][j]<<' ';
		cout << endl;
	}
}

//主对角线元素均为1
void zifan(vector<vector<int>>matrix,int n)
{
	for (int i = 0; i < n; i++)
		matrix[i][i] = 1;
	output(matrix,n);
}

void duichen(vector<vector<int>>matrix,int n)
{
	vector<vector<int>>T(n,vector<int>(n));//转置矩阵
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			T[j][i] = matrix[i][j]; //行列交换

	//矩阵相加（逻辑加）
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matrix[i][j] = T[i][j] || matrix[i][j];//逻辑加，以matrix存放结果
	output(matrix,n);
}

void chuandi(vector<vector<int>>matrix,int n)
{
	
	vector<vector<int>>temp(n,vector<int>(n));//临时矩阵，先初始化为0
	vector<vector<int>>result(n, vector<int>(n));//结果矩阵
	vector<vector<int>>mi(n, vector<int>(n));//用来求幂矩阵

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			result[i][j]=matrix[i][j];//结果矩阵为M+M^2+M^3......+M^n
			mi[i][j]=matrix[i][j];//幂矩阵初始化为1次幂，即为原矩阵
		}
	}
	//根据有穷集合，最多不超多R^n
	
	for (int h = 0; h < n; h++)
	{
		/*求幂矩阵*/
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (mi[i][j] == 1) //如果当前幂矩阵该位置为1
				{
					for (int k = 0; k < n; k++)
						if (matrix[j][k] == 1)//且对应的原矩阵的第j行有位置为1
							temp[i][k] = 1; //则临时矩阵存放新的幂次阵的该位置为1
				}
		/*求逻辑加*/
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				mi[i][j] = temp[i][j];//把传递加出来的新的幂矩阵又作为下一个原矩阵继续进行累×
				result[i][j] =result[i][j]||temp[i][j]; //结果矩阵接着就把该幂加进去(逻辑加)
				temp[i][j] = 0;//中间矩阵清零，便于下次存放数据
			}
	}

	output(result,n);

}