#include <cstdio>

const int MAXN = 110;

struct Node {
	int x, y;
};

Node c[MAXN], s[MAXN];
int g[10][10], d[10], n, cnt;

void dfs(int u) {
	for (int v = 0; v <= 6; ++ v) {
		if (g[u][v]) {
			g[u][v] --; g[v][u] --;
			dfs(v);
			s[cnt].x = u; s[cnt].y = v; cnt ++;
		}
	}
}

bool solve() {
	int st = 0; cnt = 0;
	for (int i = 0; i <= 6; ++ i) {
		if (d[i] & 1) cnt ++, st = i;
		else if (d[i] && !st) st = i;
	}
	if (cnt > 2) return false;
	cnt = 0; dfs(st);
	if (cnt < n) return false;
	for (int i = cnt - 1; i >= 0; -- i) {
		for (int j = 0; j < n; ++ j) {
			if (s[i].x == c[j].x && s[i].y == c[j].y) {
				printf("%d +\n", j + 1);
				c[j].x = -1;
				break;
			}
			else if (s[i].x == c[j].y && s[i].y == c[j].x) {
				printf("%d -\n", j + 1);
				c[j].x = -1;
				break;
			}
		}
	}
	return true;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) {
		int a, b; scanf("%d%d", &a, &b);
		g[a][b] ++; g[b][a] ++; d[a] ++; d[b] ++;
		c[i].x = a; c[i].y = b;
	}
	if (!solve())puts("No solution");
	return 0;
}
