#include <bits/stdc++.h>
#define MP make_pair
using namespace std;

typedef pair<int, int> PII;
typedef long long LL;

const int MAXN = 100005;
const int SIZE = 200005;

struct node {
	int l, r;
};

map<LL, int> Hash;
set<int> pos[SIZE];
set<int>::iterator it1, it2;
node blk[MAXN];
int pre[SIZE];
PII B[MAXN];
LL sum[MAXN], A[MAXN];
int F[MAXN], own[MAXN];
int N, Q, M, L, cnt;

inline void build(int px) {
	int l=blk[px].l, r=blk[px].r;
	for (int i=l; i<r; i++) B[i] = MP(F[i], i);
	sort(B+l, B+r); sum[l] = A[B[l].second];
	for (int i=l+1; i<r; i++) {
	    sum[i]=sum[i-1]+A[B[i].second];
	}
}

inline void change(int x, int v)
{
	int px=own[x]; F[x]=v;
	build(px);
}

int main()
{
    while (scanf("%d", &N) == 1) {
	    for (int i = 0; i < SIZE; i++) {
	        pos[i].clear();
	        pos[i].insert(-1);
	    }
	    for (int i = 0; i < N; ++ i) pre[i] = -1;
	    Hash.clear();
	    L=sqrt(N)+1; M = 0; cnt=0;
	    for (int hax, i=0; i<N; i++) {
		    own[i] = i / L;
		    scanf("%lld", &A[i]);
		    if (Hash.find(A[i]) == Hash.end()) Hash[A[i]] = cnt ++;
		    hax=Hash[A[i]]; F[i] = pre[hax];
		    pos[hax].insert(i);
		    if (i%L==0) {
			    blk[M].l=i; blk[M].r=min(N, i+L);
			    M ++;
		    }
		    pre[hax]=i;
	    }
	    for (int i=0; i<M; i++) build(i);
	    scanf("%d", &Q);
	    while (Q --) {
		    char st[10];
		    int x, px, py, y;
		    int hx, hy, p1, p2;
		    LL ret=0;
		    scanf("%s%d%d", st, &x, &y);
		    if (st[0]=='U') {
			    x --;
			    if (A[x] == y) continue;
			    if (Hash.find(y) == Hash.end()) Hash[y] = cnt++; 
			    hy=Hash[y]; hx=Hash[A[x]];
			    it1 = pos[hx].upper_bound(x);
			    it2 = pos[hx].lower_bound(x);
			    if (it1 != pos[hx].end()) {
				    p1 = *it1;
				    p2 = *(-- it2);
				    change(p1, p2);
			    }
			    pos[hx].erase(x);
			    pos[hy].insert(x);
			    it1 = pos[hy].upper_bound(x);
			    it2 = pos[hy].lower_bound(x);
			    A[x] = y;
			    if (it1 != pos[hy].end()) change(*it1, x);
			    change(x, *(-- it2));
		    }
		    else
		    {
		        if (x > y) swap(x, y);
			    x--, y--; px=own[x], py=own[y];
			    if (px==py) {
				    for (int i=x; i<=y; i++) if (F[i]<x) ret += A[i];
			    }
			    else {
				    for (int i = x; i < blk[px].r; i++) if (F[i]<x) ret+=A[i];
				    for (int i = blk[py].l; i <= y; i++) if (F[i]<x) ret+=A[i];
				    for (int i=px+1; i<py; i++) {
					    int k = lower_bound(B + blk[i].l, B + blk[i].r, MP(x, -1)) - B;
					    if (k != blk[i].l) ret += sum[k-1];
				    }
			    }
			    printf("%lld\n", ret);
		    }
	    }
	}
	return 0;
}

