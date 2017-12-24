#include <queue>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAXN = 100000 + 10;
bool can[10], vis[MAXN];
char ret[MAXN];
int Q[MAXN][2];
int N, M;

void bfs() {
	int head = 1, tail = 1;
	for (int i = 0; i < N; ++ i) vis[i] = false;
	for (int i = 1; i < 10; ++ i) 
		if (can[i]) {
			vis[i % N] = true;
			Q[tail][0] = i % N;
			Q[tail ++][1] = i;
		}
	for (; head < tail; ++ head) {
		int now = Q[head][0];
		if (now == 0) {
			int m = 0;
			for (; head != 0; head = Q[head][1] / 10) {
				ret[m ++] = '0' + Q[head][1] % 10;
			}
			reverse(ret, ret + m); ret[m] = '\0';
			return;
		}
		for (int i = 0; i < 10; ++ i) {
			if (!can[i]) continue;
			int tmp = (now * 10  + i)% N;
			if (!vis[tmp]) {
				vis[tmp] = true;
				Q[tail][0] = tmp;
				Q[tail ++][1] = head * 10 + i;
			}
		}
	}
}

int main() {
	int cas = 0;
	while (scanf("%d%d", &N, &M) == 2) {
		memset(can, 1, sizeof(can));
		for (int i = 0; i < M; ++ i) {
			int d; scanf("%d", &d); can[d] = false;
		}
		ret[0] = '-'; ret[1] = '1'; ret[2] = '\0';
		bfs();
		printf("Case %d: %s\n", ++ cas, ret);
	}
	return 0;
}
