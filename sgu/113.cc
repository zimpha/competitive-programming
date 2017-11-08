#include <cstdio>

int main() {
	int T; scanf("%d", &T);
	while (T --) {
		int N; scanf("%d", &N);
		int cnt = 0;
		for (int i = 2; i * i <= N; ++ i) {
			while (N % i == 0) cnt ++, N /= i;
		}
		if (N > 1) cnt ++;
		if (cnt == 2) puts("Yes");
		else puts("No");
	}
	return 0;
}
