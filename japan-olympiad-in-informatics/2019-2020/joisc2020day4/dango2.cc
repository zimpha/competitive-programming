#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 1000;

char s[N][N];
int belong[N][N];

bool is_dango(char a, char b, char c) {
  return (a == 'P' && b == 'W' && c == 'G') || (a == 'G' && b == 'W' && c == 'P');
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%s", s[i]);
    for (int j = 0; j < m; ++j) belong[i][j] = -1;
  }
  std::vector<std::vector<int>> dango;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (s[i][j] == 'W') continue;
      if (i + 3 <= n && is_dango(s[i][j], s[i + 1][j], s[i + 2][j])) {
        dango.push_back({i * m + j, (i + 1) * m + j, (i + 2) * m + j, 0});
      }
      if (j + 3 <= m && is_dango(s[i][j], s[i][j + 1], s[i][j + 2])) {
        dango.push_back({i * m + j, i * m + j + 1, i * m + j + 2, 1});
      }
      if (i + 3 <= n && j + 3 <= m && is_dango(s[i][j], s[i + 1][j + 1], s[i + 2][j + 2])) {
        dango.push_back({i * m + j, (i + 1) * m + j + 1, (i + 2) * m + j + 2, 2});
      }
      if (i + 3 <= n && j - 2 >= 0 && is_dango(s[i][j], s[i + 1][j - 1], s[i + 2][j - 2])) {
        dango.push_back({i * m + j, (i + 1) * m + j - 1, (i + 2) * m + j - 2, 3});
      }
    }
  }
  std::vector<int> mark(dango.size());
  auto put = [&](int p) {
    mark[p] ^= 1;
    for (int i = 0; i < 3; ++i) {
      int u = dango[p][i];
      int x = u / m, y = u % m;
      belong[x][y] = p;
    }
  };

  auto del = [&](int p) {
    mark[p] ^= 1;
    for (int i = 0; i < 3; ++i) {
      int u = dango[p][i];
      int x = u / m, y = u % m;
      belong[x][y] = -1;
    }
  };

  int cnt = 0, last = -1;
  // 47220, 41980, 51390, 19120, 48620, 46500
  const int bound = 48620;
  for (int it = 0; it < 1000000 && cnt < bound; ++it) {
    std::vector<int> candidate;
    for (size_t i = 0; i < dango.size(); ++i) {
      if (!mark[i]) candidate.push_back(i);
    }
    std::random_shuffle(candidate.begin(), candidate.end());
    for (auto p: candidate) {
      int x = dango[p][0] / m, y = dango[p][0] % m;
      if (belong[x][y] == p) continue;
      std::vector<int> bs;
      for (int i = 0; i < 3; ++i) {
        int u = dango[p][i];
        int x = u / m, y = u % m;
        if (belong[x][y] != -1) bs.push_back(belong[x][y]);
      }
      std::sort(bs.begin(), bs.end());
      bs.erase(std::unique(bs.begin(), bs.end()), bs.end());
      if (bs.size() >= 2) {
        if (last == -1 || it - last < 1000) continue;
      }
      for (auto &x: bs) del(x), --cnt;
      if (bs.empty()) last = it;
      ++cnt; put(p);
    }
    if (it % 1000 == 0) fprintf(stderr, "it=%d cnt=%d\n", it, cnt);
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) if (belong[i][j] != -1) {
      int p = belong[i][j];
      int x = dango[p][1] / m, y = dango[p][1] % m;
      int t = dango[p][3];
      s[x][y] = "|-\\/"[t];
    }
  }
  for (int i = 0; i < n; ++i) puts(s[i]);
  fprintf(stderr, "%d\n", cnt);
  return 0;
}
