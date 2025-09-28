#include <iostream>
using namespace std;

static const int MAX_N = 30;

/*
 * road[i][j]表示从 (0,0)到(i,j)的路径数
 */
long long road[MAX_N][MAX_N];

int horse_x, horse_y;
int target_x, target_y;

/*
 * @return 是否会被马吃掉或阻挡
 */
bool unreachable(int x, int y)
{
	int dx = abs(x - horse_x);
	int dy = abs(y - horse_y);

	// 阻挡
	if (dx == 0 && dy == 0)
		return true;

	// 被吃掉
	if ((dx + dy) == 3 && dx != 3 && dy != 3)
		return true;

	return false;
}

int main()
{

	cin >> target_x >> target_y;
	cin >> horse_x >> horse_y;

	road[0][0] = 1;
	for (int x = 0; x <= target_x; x++)
	{
		for (int y = 0; y <= target_y; y++)
		{
			if (unreachable(x, y))
				continue;
			if (x)
				road[x][y] += road[x - 1][y];
			if (y)
				road[x][y] += road[x][y - 1];
		}
	}

	cout << road[target_x][target_y] << endl;
	return 0;
}