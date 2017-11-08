#include <cstdio>

int pow_mod(int a, int n, int p) {
	int ret = 1;
	for (a %= p; n; n >>= 1) {
		if (n & 1) ret = ret * a % p;
		a = a * a % p;
	}
	return ret;
}

int main() {
	int ret = 0, N, M, K;
	scanf("%d%d%d", &N, &M, &K);
	for (int i = 0; i < N; ++ i) {
		int x; scanf("%d", &x);
		ret += (pow_mod(x, M, K) == 0);
	}
	printf("%d\n", ret);
	return 0;
}
