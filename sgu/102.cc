#include <cstdio>

int main() {
	int N, ret;
	scanf("%d", &N); ret = N;
	for (int i = 2; i * i <= N; ++ i) {
		if (N % i == 0) {
			ret = ret / i * (i - 1);
			while (N % i == 0) N /= i;
		}
	}
	if (N > 1) ret = ret / N * (N - 1);
	printf("%d\n", ret);
	return 0;
}
