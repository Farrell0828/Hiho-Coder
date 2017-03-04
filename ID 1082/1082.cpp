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
 * So he turns to you to write a program to change all occurrence of ��marshtomp�� 
 * (the name is not case-sensitive)  to ��fjxmlhx��.
 * 
 * Input
 * The input contains multiple lines.
 * 
 * Each line is a string which length is no more than 200.
 * 
 * The end of one line don��t connect with the head of the next line.
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
const char Replaced_Str[] = "marshtomp";	// ���滻���ַ���
const char Replacing_Str[] = "fjxmlhx";		// �滻�ɵ��ַ���
void AllLower(char *);						// ȫ����Сд
int Match(const char *, const char *);		// ƥ���ַ���
void Replace(char *, const char *, const int, const int);	// �滻�ַ���

int main()
{
	char str_line[Max];
	while (cin.getline(str_line, Max))		// ��ȡһ���ַ���
	{
		char str_line_lower[Max];			// ���ȫ��Сд�����ַ���
		strcpy(str_line_lower, str_line);	// ����str_line_lower = str_line
		AllLower(str_line_lower);			// ȫ��Сд��

		int sub = Match(str_line_lower, Replaced_Str);	// ��ȡƥ����±꣨��ƥ��ɹ���
		while (sub != -1)		// ������-1û��ƥ��ɹ�
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

// ��������һ���ַ���Ϊ���������ַ����������ַ�Сд��
void AllLower(char *str)
{
	for (int i = 0; i < strlen(str); ++i)
	{
		str[i] = tolower(str[i]);
	}
}

// �������������ַ���Ϊ�����������str1��ƥ�䵽str2�����±����򷵻�-1
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

// �������ַ���str��begin_sub�±꿪ʼ��length���ȵĲ����滻��str_replaceing
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