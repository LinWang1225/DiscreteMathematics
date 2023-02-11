#include <iostream>
#include<vector>
using namespace std;

void warShall(vector<vector<int>>matrix, int n);
void output(vector<vector<int>>matrix, int n);

int main()
{
    int temp;//用于输入
    cout << "请输入矩阵的行数:";
    int n;//行(列)数
    //加入一些错误处理
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
    vector<vector<int>>matrix(n, vector<int>(n));//用来存放关系矩阵的二维vector,直接初始化

    cout << "请输入关系矩阵:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << endl;
        cout << "请输入矩阵的第" << i << "行元素(元素以空格分隔) :";
        for (int j = 0; j < n; j++)
        {
            cin >> temp;
            matrix[i][j] = temp;
        }
    }
    cout << "1.warShall方法求传递闭包" << endl;
    cout << "2.退出程序" << endl;
    cout << "请输入你的选择:";
    int choice;
    //输入错误处理
    while (cin >> choice)
    {
        if (choice != 1 && choice != 2)
        {
            cout << "输入错误，请重新输入！" << endl;
            cin.clear();
            cin.ignore(1024, '\n');
        }
        else
            break;
    }
    switch (choice) {
    case 1:
        warShall(matrix, n);
        break;
    case 2:
        break;
    default:
        break;
    }  
    return 0;
}
void warShall(vector<vector<int>>matrix, int n) {
    //最外层循环代表以i为内部顶点，可以经过i到达其它点
    for (int i = 0; i < n; i++) {
        //里面这两层循环代表由j点出发经i点到达k点
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                //由j到k无非就是两种情况，j直接到k或者j到i，i再到k
                //所以中间用按位或来判断，只要有一个成立就行
                matrix[j][k] = matrix[j][k] || (matrix[j][i] && matrix[i][k]);
    
            }
        }
    }
    output(matrix, n);
}
//
//void warShall(vector<vector<int>>matrix, int n) {
//
//    for (int k = 0; k < n; k++) {
//        for (int i = 0; i < n; i++) {
//            for (int j = 0; j < n; j++) {
//                if (matrix[i][j] != 1)
//                    matrix[i][j] = matrix[i][k] && matrix[k][j];
//            }
//        }
//    }
//    output(matrix, n);
//}
//输出结果
void output(vector<vector<int>>matrix, int n)
{
    cout << "所求关系矩阵为:" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << matrix[i][j] << ' ';
        cout << endl;
    }
}

