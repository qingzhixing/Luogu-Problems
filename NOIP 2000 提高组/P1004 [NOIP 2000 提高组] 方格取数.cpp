#include <iostream>
using namespace std;

const int MAX_N = 12;

// 上, 左
const int dx[2] = {0, -1};
const int dy[2] = {-1, 0};

int n;
int nums[MAX_N][MAX_N];
/*
 * max_sum[i][j] [k][l]: 第一种情况走到(i,j)，第二种情况走到(k,l)
 *		能达到的最大和
 */
int max_sum[MAX_N][MAX_N][MAX_N][MAX_N];

int main()
{
	cin >> n;
	while (1)
	{
		int x, y, val;
		cin >> x >> y >> val;
		if (x == y && y == val && val == 0)
			break;
		nums[x][y] = val;
	}

	// 方案一
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			// 方案二
			for (int k = 1; k <= n; k++)
			{
				for (int l = 1; l <= n; l++)
				{
					// 两条线总操作数一样才符合题意
					if ((i + j) != (k + l))
						continue;

					// 枚举之前的状态，当前状态由前面最优状态转移过来
					int max_previous = -2147483648;
					for (int direction1 = 0; direction1 <= 1; direction1++)
					{
						for (int direction2 = 0; direction2 <= 1; direction2++)
						{
							int pre_i = i + dx[direction1], pre_j = j + dy[direction1];
							int pre_k = k + dx[direction2], pre_l = l + dy[direction2];
							max_previous = max(max_previous, max_sum[pre_i][pre_j][pre_k][pre_l]);
						}
					}

					max_sum[i][j][k][l] = max_previous + nums[i][j] + nums[k][l];

					/*
					 * 容易证明，当两路齐进时，只有当两条路在同一个单元格时会导致单元格重复计算
					 */
					if (i == k && j == l)
						max_sum[i][j][k][l] -= nums[i][j];
				}
			}
		}
	}

	cout << max_sum[n][n][n][n] << endl;
	return 0;
}