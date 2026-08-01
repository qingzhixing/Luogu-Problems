#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string str;

bool right_of_equal = false;
int read = 0;					 // 已读入的数字
bool positive = true;			 // 数字的符号
bool coefficient_omitted = true; // 用于提交系数时判断系数是否被省略

int coefficient = 0; // 未知数总系数
int constant = 0;	 // 总常数

char unknown_char; // 未知数符号

void commit_constant()
{
	constant += read * ((positive ^ right_of_equal) ? 1 : -1);
	read = 0;
	positive = true;
	coefficient_omitted = true;
}

void commit_coefficient()
{
	if (coefficient_omitted)
	{
		read = 1;
	}
	coefficient += read * ((positive ^ right_of_equal) ? 1 : -1);
	read = 0;
	positive = true;
	coefficient_omitted = true;
}

int main()
{
	cin >> str;

	for (auto ch : str)
	{
		// 如果遇到的是符号则提交常数
		if (ch == '+' || ch == '-')
		{
			commit_constant();
			positive = (ch == '+');
			continue;
		}

		// 如果遇到 = 也提交常数, 并置位 right_of_equal
		if (ch == '=')
		{
			commit_constant();
			right_of_equal = true;
			continue;
		}

		// 如果遇到数字则读入
		if (isdigit(ch))
		{
			read = read * 10 + ch - '0';
			coefficient_omitted = false;
			continue;
		}

		// 遇到未知数则提交系数 并设置未知数符号
		commit_coefficient();
		unknown_char = ch;
		continue;
	}

	// 最后还要提交最后面没提交的数字
	commit_constant();

	double ans = -1.0 * (double)constant / (double)coefficient;

	// 排除 -0.000
	if (ans == 0.0)
	{
		ans = 0.0;
	}

	printf("%c=%.3f", unknown_char, ans);
	return 0;
}