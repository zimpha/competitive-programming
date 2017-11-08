#include <vector>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int main() {
	int n, a, b; scanf("%d%d%d", &n, &a, &b);
	a %= n; b %= n;
	int x = n / __gcd(n, a), y = n / __gcd(n, b), z = x * y / __gcd(x, y);
	vector<pair<int, int> > ret;
	for (int i = 0; i < z; ++ i) {
		ret.push_back(make_pair(a * i % n, b * i % n));
	}
	sort(ret.begin(), ret.end());
	printf("%d\n", z);
	for (int i = 0; i < z; ++ i)
		printf("%d %d\n", ret[i].first, ret[i].second);
	return 0;
}
