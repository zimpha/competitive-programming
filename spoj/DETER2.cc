#include <cstdio>
#include <cstring>

const int MAXN = 1000000 + 10;
const int MOD = 1000003;

int vis[MAXN], A[MAXN];
int f[MAXN], p[MAXN], T, N, M, K, cas;

int pow_mod(int a, int n) {
	int ret = 1;
	for (; n; n >>= 1) {
		if (n & 1) ret = (long long)ret * a % MOD;
		a = (long long)a * a % MOD;
	}
	return ret;
}

void sieve() {
	M = 0;
	for (int i = 2; i < MAXN; ++ i) {
		if (!vis[i]) p[M ++] = i;
		for (int j = 0; j < M && i * p[j] < MAXN; ++ j) {
			vis[i * p[j]] = true;
			if (i % p[j] == 0) break;
		}
	}
}

int main() {
	sieve();
	scanf("%d", &T);
	for (cas = 1; cas <= T; ++ cas) {
		scanf("%d%d", &N, &K);
		K %= (MOD - 1);
		memset(f, 0, sizeof(int) * (N + 1)); f[1] = 1;
		for (int i = 2; i <= N; ++ i) {
			if (!f[i]) {
				A[i] = pow_mod(i, K), f[i] = A[i] - 1;
				if (f[i] < 0) f[i] += MOD;
			}
			for (int j = 0, t; j < M && (t = i * p[j]) <= N; ++ j) {
				if (i % p[j] == 0) {
					f[t] = (long long)f[i] * A[p[j]] % MOD;
					break;
				}
				else {
					f[t] = (long long)f[i] * (A[p[j]] - 1 + MOD) % MOD;
				}
			}
		}
		int ret = 1;
		for (int i = 1; i <= N; ++ i) ret = (long long)ret * f[i] % MOD;
		printf("%d\n", ret);
	}
	return 0;
}
