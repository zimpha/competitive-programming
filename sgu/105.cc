#include <cstdio>

int main() {
	int N; scanf("%d", &N);
	if (N % 3 == 0) printf("%d\n", N / 3 * 2);
	else printf("%d\n", N / 3 * 2 + N % 3 - 1);
	return 0;
}
