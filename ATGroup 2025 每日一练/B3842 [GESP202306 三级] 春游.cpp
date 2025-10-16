#include <iostream>
using namespace std;

const int MAX_N = 1010;

int n, m;
bool exist[MAX_N];

int main()
{
	cin >> n >> m;
	while (m--)
	{
		int num;
		cin >> num;

		exist[num] = true;
	}

	bool all_right = true;
	for (int i = 0; i < n; i++)
	{
		if (!exist[i])
		{
			all_right = false;
			cout << i << ' ';
		}
	}

	if (all_right)
	{
		cout << n << endl;
	}
	return 0;
}