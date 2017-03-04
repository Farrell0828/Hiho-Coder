/**
 * Source: http://hihocoder.com/problemset/problem/1094
 * Author: Farrell Meng
 * Date: 2017-03-04
 *
 * #1094 : Lost in the City
 * Time Limit:10000ms
 * Case Time Limit:1000ms
 * Memory Limit:256MB
 * Description
 * Little Hi gets lost in the city. He does not know where he is. He does not know 
 * which direction is north.
 * 
 * Fortunately, Little Hi has a map of the city. The map can be considered as a grid 
 * of N*M blocks. Each block is numbered by a pair of integers. The block at the 
 * north-west corner is (1, 1) and the one at the south-east corner is (N, M).
 * 
 * Each block is represented by a character, describing the construction on that 
 * block: '.' for empty area, 'P' for parks, 'H' for houses, 'S' for streets, 'M' for 
 * malls, 'G' for government buildings, 'T' for trees and etc.
 * 
 * Given the blocks of 3*3 area that surrounding Little Hi(Little Hi is at the middle 
 * block of the 3*3 area), please find out the position of him. Note that Little Hi 
 * is disoriented, the upper side of the surrounding area may be actually north side, 
 * south side, east side or west side.
 * 
 * Input
 * Line 1: two integers, N and M(3 <= N, M <= 200).
 * Line 2~N+1: each line contains M characters, describing the city's map. 
 * The characters can only be 'A'-'Z' or '.'.
 * Line N+2~N+4: each line 3 characters, describing the area surrounding Little Hi.
 * 
 * Output
 * Line 1~K: each line contains 2 integers X and Y, indicating that block (X, Y) may be 
 * Little Hi's position. If there are multiple possible blocks, output them from north 
 * to south, west to east.
 * 
 * Sample Input
 * 8 8
 * ...HSH..
 * ...HSM..
 * ...HST..
 * ...HSPP.
 * PPGHSPPT
 * PPSSSSSS
 * ..MMSHHH
 * ..MMSH..
 * SSS
 * SHG
 * SH.
 * 
 * Sample Output
 * 5 4
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>
using namespace std;

// 自定义矩阵类
class Matrix
{
private:
	vector< vector<char> > data;

public:
	// 构造函数, x为矩阵的行数, y为矩阵的列数
	Matrix(size_t x = 0, size_t y = 0)
	{
		data.resize(x);
		for (size_t i = 0; i < x; i++)
		{
			data[i].resize(y);
		}
	}

	~Matrix() {}	// 析构函数

	void Resize(size_t x = 0, size_t y = 0)
	{
		data.resize(x);
		for (size_t i = 0; i < x; i++)
		{
			data[i].resize(y);
		}
	}

	// 是否为空矩阵
	bool IsEmpty()
	{
		return (data.size() == 0);
	}

	// 获取矩阵的行数
	size_t GetRow()
	{
		return data.size();
	}

	// 获取矩阵的列数
	size_t GetCol()
	{
		return data[0].size();
	}

	vector<char> Convert(string str)
	{
		vector<char> result;
		for (int i = 0; i < str.length(); i++)
		{
			result.push_back(str[i]);
		}
		return result;
	}

	// 重载[]运算符
	vector<char> & operator[](size_t i)
	{
		return data[i];
	}

	// 
	void Load()
	{
		string line;
		for (int i = 0; i < GetRow(); i++)
		{
			cin >> line;
			vector<char> line_vect = Convert(line);
			data[i] = line_vect;
		}
	}

	Matrix Rotate(int flag)
	{
		Matrix result;
		switch (flag)
		{
		case 1:
			result.Resize(GetCol(), GetRow());
			for (size_t i = 0; i < result.GetRow(); i++)
			{
				for (size_t j = 0; j < result.GetCol(); j++)
				{
					result[i][j] = data[GetRow() - j - 1][i];
				}
			}
			break;

		case 2:
			result.Resize(GetRow(), GetCol());
			for (size_t i = 0; i < result.GetRow(); i++)
			{
				for (size_t j = 0; j < result.GetCol(); j++)
				{
					result[i][j] = data[GetRow() - i - 1][GetCol() - j - 1];
				}
			}
			break;

		case 3:
			result.Resize(GetCol(), GetRow());
			for (size_t i = 0; i < result.GetRow(); i++)
			{
				for (size_t j = 0; j < result.GetCol(); j++)
				{
					result[i][j] = data[GetRow() - j - 1][GetCol() - i - 1];
				}
			}
			break;

		default:
			break;
		}
		return result;
	}

	// 获取子矩阵
	Matrix GetSubMatrix(size_t begin_row, size_t begin_col, size_t sub_row, size_t sub_col)
	{
		Matrix sub_matrix;		// 存储要返回的子矩阵，初始化时为空矩阵
		if (begin_row + sub_row > GetRow() || begin_col + sub_col > GetCol())
		{
			return sub_matrix;	// 如果超出边界返回初始化的空矩阵
		}

		// 如果在边界内则设置子矩阵大小并对子矩阵赋值
		sub_matrix.Resize(sub_row, sub_col);
		for (int i = 0; i < sub_row; i++)
		{
			for (int j = 0; j < sub_col; j++)
			{
				sub_matrix.data[i][j] = data[begin_row + i][begin_col + j];
			}
		}
		return sub_matrix;
	}

	bool IsSame(Matrix mat)
	{
		size_t big_row = GetRow();
		size_t big_col = GetCol();
		size_t small_row = mat.GetRow();
		size_t small_col = mat.GetCol();

		if (big_row != small_row || big_col != small_col)
		{
			return false;
		}

		for (int i = 0; i < big_row; i++)
		{
			for (int j = 0; j < big_col; j++)
			{
				if (data[i][j] != mat[i][j])
					return false;
			}
		}
		return true;
	}
};

void Match(Matrix mat_map, Matrix mat_sur)
{
	for (size_t i = 0; i <= mat_map.GetRow() - 3; i++)
	{
		for (size_t j = 0; j <= mat_map.GetCol() - 3; j++)
		{
			Matrix sub_mat = mat_map.GetSubMatrix(i, j, 3, 3);
			if (sub_mat.IsSame(mat_sur))
			{
				cout << i + 2 << " " << j + 2 << endl;
			}
		}
	}
}

int main()
{
	size_t N, M;
	cin >> N >> M;

	Matrix mat_map(N, M);		// 地图矩阵
	mat_map.Load();

	Matrix mat_sur(3, 3);		// 周围环境矩阵
	mat_sur.Load();

	Match(mat_map, mat_sur);
	for (int i = 1; i <= 3; i++)
	{
		Match(mat_map, mat_sur.Rotate(i));
	}

	return 0;
}


