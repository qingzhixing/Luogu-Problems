#include <iostream>
using namespace std;

struct Coord
{
	int x, y;

	Coord operator+(const Coord &value) const
	{
		return {x + value.x, y + value.y};
	}
	Coord &operator+=(const Coord &value)
	{
		*this = this->operator+(value);
		return *this;
	}

	Coord operator-(const Coord &value) const
	{
		return {x - value.x, y - value.y};
	}

	Coord &operator-=(const Coord &value)
	{
		*this = this->operator-(value);
		return *this;
	}

	bool operator==(const Coord &value) const
	{
		return x == value.x && y == value.y;
	}
};

// 下 右
const Coord directions[2] = {{1, 0}, {0, 1}};

Coord horse, target, current;

int answer;

/*
 * @return 返回当前坐标是否合格(不会被马吃掉，且没越界)
 */
bool check()
{
	// 越界
	if (current.x > target.x || current.y > target.y)
		return false;

	int dx = current.x - horse.x;
	int dy = current.y - horse.y;

	// 被马吃掉
	if ((abs(dx) + abs(dy) == 3) && (!(abs(dx) == 3 || abs(dy) == 3)))
		return false;

	// 跟马重合
	if (dx == 0 && dy == 0)
		return false;
	return true;
}

void dfs()
{
	if (current == target)
	{
		answer++;
		return;
	}

	for (auto direction_index = 0; direction_index < 2; direction_index++)
	{
		current += directions[direction_index];
		if (check())
		{
			dfs();
		}
		current -= directions[direction_index];
	}
}

int main()
{
	cin >> target.x >> target.y;
	cin >> horse.x >> horse.y;

	dfs();

	cout << answer << endl;
	return 0;
}