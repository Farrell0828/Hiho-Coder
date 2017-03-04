/**
 * Source: http://hihocoder.com/problemset/problem/1000
 * Author: Farrell Meng
 * Date: 2017-03-04
 * 
 * #1000 : A + B
 * Time Limit:1000ms
 * Case Time Limit:1000ms
 * Memory Limit:256MB
 * Description
 * Calculate A + B.
 * 
 * Input
 * Input contains multiple test cases¡£
 * Each test case contains two integers: A(1 ¡Ü A ¡Ü 100) and B(1 ¡Ü B ¡Ü 100).
 * 
 * Output
 * For each test case output the sum A + B.
 * 
 * Sample Input
 * 1 2
 * 3 4
 * Sample Output
 * 3
 * 7
 */

#include <iostream>
int main()
{
	using namespace std;
	double a, b;
	while (cin >> a >> b)
	{
		cout << a + b << endl;
	}
	return 0;
}