/**
 * Source: http://hihocoder.com/problemset/problem/1082
 * Author: Farrell Meng
 * Date: 2017-03-04
 * 
 * #1082 : The Marshtomp has seen it all before
 * Time Limit:1000ms
 * Case Time Limit:1000m
 * Memory Limit:256MB
 * Description
 * 
 * fjxmlhx is fed up with endless marshtomps on the internet. 
 * So he turns to you to write a program to change all occurrence of “marshtomp” 
 * (the name is not case-sensitive)  to “fjxmlhx”.
 * 
 * Input
 * The input contains multiple lines.
 * 
 * Each line is a string which length is no more than 200.
 * 
 * The end of one line don’t connect with the head of the next line.
 * 
 * Output
 * The output contains multiple lines which are the result after the changes in the description.
 * 
 * Sample Input
 * The Marshtomp has seen it all before.
 * marshTomp is beaten by fjxmlhx!
 * AmarshtompB
 * 
 * Sample Output
 * The fjxmlhx has seen it all before.
 * fjxmlhx is beaten by fjxmlhx!
 * AfjxmlhxB
 */

#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

const int Max = 201;
const char Replaced_Str[] = "marshtomp";	// 被替换的字符串
const char Replacing_Str[] = "fjxmlhx";		// 替换成的字符串
void AllLower(char *);						// 全部变小写
int Match(const char *, const char *);		// 匹配字符串
void Replace(char *, const char *, const int, const int);	// 替换字符串

int main()
{
	char str_line[Max];
	while (cin.getline(str_line, Max))		// 获取一行字符串
	{
		char str_line_lower[Max];			// 存放全部小写化的字符串
		strcpy(str_line_lower, str_line);	// 先令str_line_lower = str_line
		AllLower(str_line_lower);			// 全部小写化

		int sub = Match(str_line_lower, Replaced_Str);	// 获取匹配的下标（若匹配成功）
		while (sub != -1)		// 若等于-1没有匹配成功
		{
			Replace(str_line, Replacing_Str, sub, strlen(Replaced_Str));
			strcpy(str_line_lower, str_line);
			AllLower(str_line_lower);
			sub = Match(str_line_lower, Replaced_Str);
		}
		cout << str_line << endl;
	}
	return 0;
}

// 函数接收一个字符串为参数，将字符串的所有字符小写化
void AllLower(char *str)
{
	for (int i = 0; i < strlen(str); ++i)
	{
		str[i] = tolower(str[i]);
	}
}

// 函数接收两个字符串为参数，如果在str1中匹配到str2返回下表，否则返回-1
int Match(const char *str1, const char *str2)
{
	int i = 0, j = 0;
	while (i < strlen(str1) && j < strlen(str2))
	{
		if (str1[i] == str2[j])
		{
			++i;
			++j;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}

	if (j >= strlen(str2))
	{
		return(i - strlen(str2));
	}
	else
	{
		return (-1);
	}
}

// 函数从字符串str的begin_sub下标开始将length长度的部分替换成str_replaceing
void Replace(char *str, const char *str_replaceing,
	const int begin_sub, const int length)
{
	char str_before[Max];
	char str_after[Max];

	strcpy(str_before, str);
	str_before[begin_sub] = '\0';
	strcpy(str_after, str);

	for (int i = 0; i < strlen(str) - begin_sub - length + 1; ++i)
	{
		str_after[i] = str[i + begin_sub + length];
	}

	str_after[strlen(str) - begin_sub - length + 1] = '\0';
	strcat(str_before, str_replaceing);
	strcat(str_before, str_after);
	strcpy(str, str_before);
}