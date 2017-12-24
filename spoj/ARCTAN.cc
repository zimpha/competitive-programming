#include <cstdio>

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		long long A ,n, m; scanf("%lld", &A);
		for (m=A; m>=1; m--) {
			if ((A*A+1)%m==0) break;
		}
		n=(A*A+1)/m;
		printf("%lld\n", A*2+n+m);
	}
	return 0;
}
