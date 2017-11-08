#include <cstdio>

int main() {
	int N; scanf("%d", &N);
	if (N <= 8) puts("0");
	else if (N == 9) puts("8");
	else {
		printf("%d", 72); N -= 10;
		for (int i = 0; i < N; ++ i) printf("0");
		puts("");
	}
	return 0;
}
