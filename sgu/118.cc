#include <cstdio>

int main() {
	int T; scanf("%d", &T);
	while (T --) {
		int N; scanf("%d", &N);
		int ret = 0, now = 1;
		for (int i = 0; i < N; ++ i) {
			int x; scanf("%d", &x); x %= 9;
			now = now * x % 9;
			ret = (ret + now) % 9;
		}
		if (ret == 0) ret = 9;
		printf("%d\n", ret);
	}
	return 0;
}
