#include <bits/stdc++.h>

const int N = 250;

double dis[N + 1][N + 1];
double len[N + 1][N + 1];
bool vis[N + 1][N + 1];

int main(){
  for (int i = 0; i <= N; ++i) {
    for (int j = 0; j <= N; ++j) {
      len[i][j] = hypot(i, j);
    }
  }
  double left = 132.5, right = 132.6;
  for (int it = 0; it < 30; ++it) {
    double mid = (left + right) * 0.5;
    for (int i = 0; i <= N; ++i) {
      for (int j = 0; j <= N; ++j) {
        dis[i][j] = 1e30;
        vis[i][j] = false;
      }
    }
		dis[0][N] = 0;
		vis[0][N] = true;
    static std::pair<int, int> Q[N * N];
    Q[0] = {0, N};
    for (int h = 0, t = 1; h < t; ++h) {
      int sx = Q[h].first, sy = Q[h].second;
			for (int x = sx; x <= N; ++x) {
				for (int y = sy; y >= x; --y) {
          if (x * sy - y * sx <= 0) continue;
					double a = (x * sy - y * sx) / 2.0;
          double p = len[x - sx][sy - y];
					double v = mid * p - a;
					if (dis[x][y] > dis[sx][sy] + v) {
						dis[x][y] = dis[sx][sy] + v;
						if (!vis[x][y]) Q[t++] = {x, y};
            vis[x][y] = true;
					}
				}
			}
		}
    double mx = 1e30;
    for (int i = 0; i <= N; ++i) mx = std::min(mx, dis[i][i]);
    printf("%d %.8f %.8f %.8f\n", it + 1, left, right, mx);
		if (mx >= 0) right = mid;
    else left = mid;
	}
	return 0;
}
