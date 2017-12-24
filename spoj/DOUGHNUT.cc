#include <cstdio>
int main() {
	int t, c, k, w;
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d %d", &c, &k, &w);
		if(c*w <= k)
			printf("yes\n");
		else
			printf("no\n");
	}
	return 0;
}
