#include "MyFunc.h"
#include <vector>
#include <numeric>
#include <algorithm>

bool Compare(int type,float n,float m)
{
	switch (type)
	{
	case 0:
		if (n == m) {
			return true;
		}
		break;
	case 1:
		if (n >= m) {
			return true;
		}
		break;
	case 2:
		if (n <= m) {
			return true;
		}
		break;
	case 3:
		if (n > m) {
			return true;
		}
		break;
	case 4:
		if (n < m) {
			return true;
		}
		break;
	default:
		return false;
		break;
	}
	return false;
}

int Weighted_Lottery(std::vector<float>& data)
{
	auto tmp = std::accumulate(data.begin(), data.end(), 0);
	if (tmp == 0) {
		return -1;
	}
		// d‚İ•t‚«’Š‘I
		int n = (rand() % tmp);
		int sum = 0;
	for (auto i = 0; i < data.size(); i++) {
		sum = sum + data[i];
		if (n - sum < 0) {
			return i;
		}
	}
}
