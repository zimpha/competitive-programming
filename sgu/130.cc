#include <cstdio>

int main() {
	int k; scanf("%d", &k);
	long long ret = 1;
	for (int i = 1; i <= k; ++ i) ret = ret * (i + k) / i;
	ret = ret / (k + 1);
	printf("%lld %d\n", ret, k + 1);
	return 0;
}
