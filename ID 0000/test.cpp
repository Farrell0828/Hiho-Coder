#include <cstring>
#include <iostream>
#include <string>
#include <set>
using namespace std;

const int SUR_LENGTH = 3;
typedef pair<int, int> point;

/*
 @函数功能：返回输入矩阵顺时针旋转90°之后的矩阵
 @参数mat：输入的矩阵
 @参数row：输入矩阵的行数
 @参数col：输入矩阵的列数
*/
char ** Rotate(char **mat, int row, int col)
{
	int new_row = col;
	int new_col = row;

	char **new_mat = new char*[new_row];
	for (int i = 0; i < new_row; i++)
	{
		new_mat[i] = new char[new_col];
	}

	for (int i = 0; i < new_row; i++)
	{
		for (int j = 0; j < new_col; j++)
		{
			new_mat[i][j] = mat[row - j - 1][i];
		}
	}
	return new_mat;
}

/*
 @函数功能：在mat1中匹配mat2，如果匹配到则将mat2在mat1中对应位置左上角的下标插入到result中
 @参数mat1：mat1
 @参数row1：mat1的行数
 @参数col1：mat1的列数
 @参数mat2：mat2
 @参数row2：mat2的行数
 @参数col2：mat2的列数
 @参数result：保存结果位置的指针
*/
void Match(char **mat1, int row1, int col1, 
	char **mat2, int row2, int col2, set<point> *result)
{
	for (int i = 0; i <= row1 - row2; i++)
	{
		for (int j = 0; j <= col1 - col2; j++)
		{
			bool is_same = true;
			bool need_break = false;
			for (int k = i; k < i + row2; k++)
			{
				if (need_break) break;
				for (int l = j; l < j + col2; l++)
				{
					if (mat1[k][l] != mat2[k - i][l - j])
					{
						is_same = false;
						need_break = true;
						break;
					}
				}
			}
			if (is_same)
			{
				(*result).insert(point(i, j));
			}
		}
	}
}

int main()
{
	int row, col;						// 地图矩阵的行数、列数
	cin >> row >> col;

	char **mat_map = new char*[row];	// 地图矩阵
	for (int i = 0; i < row; i++)
	{
		mat_map[i] = new char[col];
		cin >> mat_map[i];
		// cout << mat_map[i] << endl;
	}

	char **mat_sur = new char*[SUR_LENGTH];// 周围环境矩阵
	for (int i = 0; i < SUR_LENGTH; i++)
	{
		mat_sur[i] = new char[SUR_LENGTH];
		cin >> mat_sur[i];
		// cout << mat_sur[i] << endl;
	}

	set<point> result;					// 保存结果的set

	// 在地图矩阵中匹配初始环境矩阵
	Match(mat_map, row, col, mat_sur, SUR_LENGTH, SUR_LENGTH, &result);

	char **temp = mat_sur;				// 保存旋转之后的矩阵的临时变量
	for (int i = 0; i < 3; i++)
	{
			temp = Rotate(temp, SUR_LENGTH, SUR_LENGTH);
			Match(mat_map, row, col, temp, SUR_LENGTH, SUR_LENGTH, &result);
	}

	for (auto x : result)
	{
		cout << x.first + ((SUR_LENGTH + 1) / 2) << " " 
			<< x.second + ((SUR_LENGTH + 1) / 2) << endl;
	}

	return 0;
}