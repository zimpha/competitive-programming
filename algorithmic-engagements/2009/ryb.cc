#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <algorithm>

using uint64 = unsigned long long;

const int N = 1000 + 10, M = 1e4 + 10;
const int seed = 1e9 + 7;

char sea[N][N], s[M];
std::pair<int, char> stack[M];
std::pair<uint64, int> hash[N];
int idx[N][N];

int lcs(std::pair<int, char> *s, int n) {
  std::pair<int, char> ci, cj;
  for (int i = 0, j = 1, k; ;) {
    for (k = 0; k < n; ++k) {
      ci = s[(i + k) % n];
      cj = s[(j + k) % n];
      if (ci != cj) break;
    }
    if (k == n) return std::min(i,j);
    if (ci > cj) i += k + 1,i += i == j;
    else j += k + 1, j += i==j;
  }
  return -1;
}

int main() {
  int h, w;
  scanf("%d%d", &w, &h);
  for (int i = 0, s = 0; i < h; ++i) {
    scanf("%s", sea[i]);
    for (int j = 0; j < w; ++j) {
      if (!j || sea[i][j] != sea[i][j - 1]) ++s;
      if (sea[i][j] == '.') idx[i][j] = s;
    }
  }
  /*
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      printf("%d ", idx[i][j]);
    }
    puts("");
  }*/
  int n;
  scanf("%d", &n);
  std::vector<int> la(n);
  for (int i = 0; i < n; ++i) {
    la[i] = i;
    int x, y, m;
    scanf("%d%d%d%s", &y, &x, &m, s);
    --x, --y;
    int head = 0, tail = -1;
    for (int j = 0; j < m; ++j) {
      if (s[j] == 'E') ++y;
      else if (s[j] == 'W') --y;
      else if (s[j] == 'S') {
        if (head <= tail && stack[tail].first == idx[x][y]) --tail;
        else stack[++tail] = {idx[x][y], 'S'};
        ++x;
      } else {
        --x;
        if (head <= tail && stack[tail].first == idx[x][y]) --tail;
        else stack[++tail] = {idx[x][y], 'N'};
      }
    }
    while (head <= tail && stack[head].first == stack[tail].first) ++head, --tail;
    if (head <= tail) {
      int p = lcs(stack + head, tail - head + 1);
      uint64 val = 0;
      for (int i = 0; i <= tail - head; ++i) {
        int u = (p + i) % (tail - head + 1) + head;
        val = val * seed + stack[u].first;
        val = val * seed + stack[u].second;
      }
      hash[i] = {val, tail - head + 1};
    } else hash[i] = {0, 0};
  }
  std::sort(la.begin(), la.end(), [&](int x, int y) {
    return hash[x] < hash[y];
  });
  std::vector<std::vector<int>> eq;
  for (int i = 0, j; i < n; i = j) {
    eq.emplace_back();
    for (j = i; j < n && hash[la[i]] == hash[la[j]]; ++j) {
      eq.back().push_back(la[j] + 1);
    }
    std::sort(eq.back().begin(), eq.back().end());
  }
  std::sort(eq.begin(), eq.end());
  printf("%d\n", (int)eq.size());
  for (auto &e: eq) {
    for (auto &x: e) printf("%d ", x);
    puts("");
  }
  return 0;
}
