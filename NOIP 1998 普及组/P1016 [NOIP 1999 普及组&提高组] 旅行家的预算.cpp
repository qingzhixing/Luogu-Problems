#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_N = 10;
const double eps = 1e-8; // 用于判断相等，容忍double精度丢失

// position, price
typedef pair<double, double> GasStation;

int main()
{
	double dist; // 目标城市距离
	double capacity;

	int n;		// 加油站数量
	double dpl; // Distance Per Liter

	vector<GasStation> raw_gas_stations;
	vector<GasStation> filtered_gas_stations;

	double P0;

	cin >> dist >> capacity >> dpl >> P0 >> n;

	// 汽车加满油能行驶的最远距离
	const double max_reach = dpl * capacity;

	// 将起点当作距离为 0 的加油站
	raw_gas_stations.push_back({0, P0});
	for (int i = 1; i <= n; i++)
	{
		double gas_position, gas_price;
		cin >> gas_position >> gas_price;
		raw_gas_stations.push_back({gas_position, gas_price});
	}
	// 将终点当作价格为 0 的加油站
	raw_gas_stations.push_back({dist, 0});

	// 给加油站排序
	sort(raw_gas_stations.begin(), raw_gas_stations.end());

	// 过滤加油站信息
	// 起点
	filtered_gas_stations.push_back(raw_gas_stations[0]);
	for (int i = 1; i < raw_gas_stations.size(); i++)
	{
		// 同位置低价最优
		if (abs(raw_gas_stations[i].first - raw_gas_stations[i - 1].first) <= eps)
		{
			continue;
		}

		// 去掉终点之后的加油站
		if ((raw_gas_stations[i].first - dist) > eps)
		{
			continue;
		}

		filtered_gas_stations.push_back(raw_gas_stations[i]);
	}

	// 判断无解
	for (int i = 0; i < filtered_gas_stations.size() - 1; i++)
	{
		if ((filtered_gas_stations[i + 1].first - filtered_gas_stations[i].first) - max_reach > eps)
		{
			cout << "No Solution" << endl;
			return 0;
		}
	}

	// 开始模拟
	int current_idx = 0; // 当前所处加油站的编号
	double cost = 0;
	double remain_reach = 0; // 剩下能够行驶的距离

	// 还没走到
	while (current_idx < (filtered_gas_stations.size() - 1))
	{
		int target_idx = 0;
		bool cheaper = false;	  // 距离内是否有更便宜的
		double best_price = 1000; // 最好的价格

		double current_position = filtered_gas_stations[current_idx].first;
		double current_price = filtered_gas_stations[current_idx].second;

		// 寻找下一个加油站
		for (int i = current_idx + 1; i < filtered_gas_stations.size(); i++)
		{
			double next_position = filtered_gas_stations[i].first;
			double next_price = filtered_gas_stations[i].second;

			// 判断是否在距离内
			if (next_position - current_position > max_reach + eps)
			{
				continue;
			}

			// 距离内有更便宜的，直接先去那边
			if (current_price - next_price > eps)
			{
				cheaper = true;
				best_price = next_price;
				target_idx = i;
				break;
			}

			// 否则去贵中最便宜的一个加油站
			if (best_price > next_price)
			{
				best_price = next_price;
				target_idx = i;
			}
		}

		double target_position = filtered_gas_stations[target_idx].first;
		double target_price = filtered_gas_stations[target_idx].second;
		double reach = target_position - current_position;

		// printf("Next Station: %d\n", target_idx);

		// 如果遇到了更便宜的，则只加到刚好到达
		if (cheaper)
		{
			double need_reach = reach - remain_reach;
			cost += (need_reach / dpl) * current_price;

			current_idx = target_idx;
			remain_reach = 0;
		}
		// 否则加满，然后走到贵的店子中最便宜的那个去
		else
		{
			double need_reach = max_reach - remain_reach;
			cost += (need_reach / dpl) * current_price;

			current_idx = target_idx;
			remain_reach = max_reach - reach;
		}
	}
	printf("%.2f\n", cost);
	return 0;
}