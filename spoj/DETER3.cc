#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;
const int MAXN = 200 + 10;

int A[MAXN][MAXN], N, P;

void eliminate(int c, int i, int j) {
	if (A[i][c] < A[j][c]) swap(i, j);
	while (A[j][c]) {
		LL q = A[i][c] / A[j][c];
		for (int k = c; k < N; ++ k) {
			LL r = (LL)A[i][k] - q * A[j][k];
			if (abs(r) >= P) r %= P;
			if (r < 0) r += P;
			A[i][k] = r;
		}
		if (A[i][c] < A[j][c]) swap(i, j);
	}
}

int solve() {
	int ret = 1;
	for (int i = 0, j; i < N; ++ i) {
		int r = -1;
		for (j = i; j < N; ++ j) if (A[j][i]) {
			r = j;
			break;
		}
		if (r == -1) return 0;
		if (r != i) {
			for (j = i; j < N; ++ j) swap(A[i][j], A[r][j]);
			ret = -ret;
		}
		for (r = i, j = i + 1; j < N; ++ j) {
			eliminate(i, j, r);
			if (!A[r][i]) r = j;
		}
		if (r != i) {
			for (j = i; j < N; ++ j) swap(A[i][j], A[r][j]);
			ret = -ret;
		}
	}
	for (int i = 0; i < N; ++ i) ret = (LL)ret * A[i][i] % P;
	if (ret < 0) ret += P;
	return ret;
}

int main() {
	while (scanf("%d%d", &N, &P) == 2) {
		for (int i = 0; i < N; ++ i) {
			for (int j = 0; j < N; ++ j) {
				scanf("%d", &A[i][j]);
				if (abs(A[i][j]) > P) A[i][j] %= P;
				if (A[i][j] < 0) A[i][j] += P;
			}
		}
		printf("%d\n", solve());
	}
	return 0;
}
