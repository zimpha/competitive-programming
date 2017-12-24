#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define lson (rt<<1)
#define rson (rt<<1|1)
#define mid ((l+r)>>1)
using namespace std;
typedef long long LL;
const int MAXN = 100000 + 10;

struct Node {
	int l, r, rm, mx, cov;
	LL sum;
	void MarkCover(int v) {
		rm = mx = v; cov = 1;
		sum = (LL)v * (r - l);
	}
} T[MAXN << 2];

struct Cube {
	int x, y, z;
	bool operator < (const Cube &rhs) const {
		return z > rhs.z;
	}
	void read() {
		scanf("%d%d%d", &x, &y, &z);
	}
} cube[MAXN];

void build(int rt, int l, int r) {
	T[rt].l = l; T[rt].r = r;
	T[rt].sum = T[rt].rm = T[rt].mx = T[rt].cov = 0;
	if (l + 1 == r) return;
	build(lson, l, mid);
	build(rson, mid, r);
}

inline void Update(int rt) {
	T[rt].rm = T[rson].rm;
	T[rt].sum = T[lson].sum + T[rson].sum;
	T[rt].mx = max(T[lson].mx, T[rson].mx);
}

inline void PushDown(int rt) {
	if (T[rt].cov) {
		T[lson].MarkCover(T[rt].mx);
		T[rson].MarkCover(T[rt].mx);
		T[rt].cov = 0;
	}
}

void Modify(int rt, int l, int r, int L, int R, int v) {
	if (T[rt].rm >= v) return;
	if (L <= l && R >= r && T[rt].mx <= v) {
		T[rt].MarkCover(v);
		return;
	}
	PushDown(rt);
	if (L < mid) Modify(lson, l, mid, L, R, v);
	if (R > mid) Modify(rson, mid, r, L, R, v);
	Update(rt);
}

int main() {
	int N, M;
	while (scanf("%d%d", &N, &M) == 2 && N) {
		build(1, 0, M);
		for (int i = 0; i < N; ++ i) cube[i].read();
		sort(cube, cube + N); cube[N].z = 0;
		LL ret = 0;
		for (int i = 0; i < N; ++ i) {
			if (cube[i].x) Modify(1, 0, M, 0, cube[i].x, cube[i].y);
			ret += T[1].sum * (cube[i].z - cube[i + 1].z);
		}
		printf("%lld\n", (LL)M * M * M - ret);
	}
	return 0;
}
