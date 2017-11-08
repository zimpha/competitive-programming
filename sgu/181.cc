#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
const int MAXN = 10000;

int X[MAXN], H[MAXN];;

int main() {
	int A, a, b, c, M, k, n;
	scanf("%d%d%d%d%d%d", &A, &a, &b, &c, &M, &k);
	memset(H, -1, sizeof(H));
	X[0] = A;
	for (int i = 1; i <= 2 * M; ++ i) {
		X[i] = a * X[i - 1] % M * X[i - 1] % M + b * X[i - 1] + c;
		X[i] %= M;
		if (H[X[i]] != -1) {
			n = i;
			break;
		}
		H[X[i]] = i;
	}
	int T = n - H[X[n]], st = H[X[n]];
	if (k <= st) printf("%d\n", X[k]);
	else printf("%d", X[st + (k - st) % T]);
	return 0;
}
