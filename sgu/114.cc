#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int MAXN = 100000 + 10;

struct Node {
	int x, p;
	void read() {
		scanf("%d%d", &x, &p);
	}
	bool operator < (const Node &rhs) const {
		return x < rhs.x;
	}
} city[MAXN];

int main() {
	int N, sum = 0; scanf("%d", &N);
	for (int i = 0; i < N; ++ i) city[i].read(), sum += city[i].p;
	sort(city, city + N); sum /= 2;
	for (int i = 0, now = 0; i < N; ++ i) {
		now += city[i].p;
		if (now >= sum) {
			printf("%d\n", city[i].x);
			break;
		}
	}
	return 0;
}
