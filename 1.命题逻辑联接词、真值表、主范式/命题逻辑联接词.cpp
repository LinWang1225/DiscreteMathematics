/*2152590 王琳*/

#include <iostream>
#include<conio.h> //getch函数
#include<Windows.h>

using namespace std;

//头部提示输出
void head_display()
{
	cout<<"***************************************\n";  //标语
	cout << "**                                   **\n";
	cout << "**        欢迎进入逻辑运算程序       **\n";
	cout << "**                                   **\n";
	cout << "***************************************\n\n";
}

int main()
{

	int p,q;//P、Q对应真值
	
	while (1)
	{
		head_display();
		while (2)
		{
			cout << "  请输入P的值（0或1），以回车结束：";
			cin >> p;
			//错误处理
			if (p != 0 && p != 1)
			{
				cerr << "  p的值输入有误，请重新输入" << endl;
				cin.clear();
				cin.ignore(1024, '\n');
			}
			else
				break;
		}

		cout << endl;
		while (3)
		{
			cout << "  请输入Q的值（0或1），以回车结束：";
			cin >> q;
			//错误处理
			if (q != 0 && q != 1)
			{
				cerr << "  q的值输入有误，请重新输入" << endl;
				cin.clear();
				cin.ignore(1024, '\n');
			}
			else
				break;
		}

		cout << endl;
		char judge;
		cout << "  合取:" << endl << "       P/" << '\\' << "Q=" << (p && q) << endl;
		cout << "  析取:" << endl << "       P" << '\\' << "/Q=" << (p || q) << endl;
		cout << "  条件:" << endl << "       P->Q=" << (!p || q) << endl;
		cout << "  双条件:" << endl << "       P<->Q=" << ((!p || q) && (!q || p))<< endl;
		cout << endl;
		cout << "是否继续运算？（y/n）";
		while (cin >> judge)
		{
			//错误处理
			if (judge != 'y' && judge != 'n')
			{
				cout << "  输入错误，请重新输入" << endl;
				cin.clear();
				cin.ignore(1024, '\n');
			}
			else
				break;
		}

		if (judge == 'y')
		{
			system("cls");  //清屏
			cin.clear();
			cin.ignore(1024, '\n');//如果第一个是对的，就只取第一个
			continue;
		}
		else
		{
			cout << "欢迎下次再次使用! Press any key to continue";
			int re = _getch();
			return 0;
		}
	}	
	return 0;
}

