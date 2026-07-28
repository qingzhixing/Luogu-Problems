#include <iostream>
using namespace std;

void divide(int num)
{
	if (num == 0)
	{
		cout << "0";
		return;
	}

	if (num == 1)
	{
		cout << "2(0)";
		return;
	}

	if (num == 2)
	{
		cout << "2";
		return;
	}

	// 从高位往低位枚举
	bool plus_flag = false;
	for (int digit = 31; digit >= 0; digit--)
	{
		// 能够进入下一层
		if (num >> digit & 1)
		{
			// cout << "<ENTER" << digit << ">";
			if (plus_flag)
			{
				cout << "+";
			}
			else
			{
				plus_flag = true;
			}

			if (digit == 1)
			{
				cout << "2";
				continue;
			}

			cout << "2(";
			divide(digit);
			cout << ")";
		}
	}
}

int main()
{
	int n;
	cin >> n;
	divide(n);
	return 0;
}