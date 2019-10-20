#include <cstdio>
#include <tuple>
#include <vector>
#include <algorithm>

const int N = 1e6 + 10;

char s[N];
int next[N], col[N], cnt[3];
int n;

int main() {
  scanf("%d%s", &n, s);
  for (int i = 0; i < n; ++i) {
    col[i] = s[i] - '1';
    cnt[col[i]]++;
    next[i] = (i + 1) % n;
  }
  std::vector<std::tuple<int, int, char>> ret;
  int x = 0;
  for (int i = 0; i < n - 3; ++i) {
    if (std::max(cnt[0], std::max(cnt[1], cnt[2])) == n - i) {
      puts("NE");
      return 0;
    }
    while (col[x] == col[next[x]] || (cnt[col[x]] == 1 && cnt[col[next[x]]] == 1)) {
      x = next[x];
    }
    int y = next[x];
    int z = 3 - col[x] - col[y];
    cnt[col[x]]--;
    cnt[col[y]]--;
    cnt[z]++;
    col[x] = z;
    next[x] = next[y];
    ret.emplace_back(x + 1, next[y] + 1, z + '1');
  }
  if (cnt[0] == 1 && cnt[1] == 1) {
    puts("DA");
    for (int i = 0; i < n - 3; ++i) {
      printf("%d %d %c\n", std::get<0>(ret[i]), std::get<1>(ret[i]), std::get<2>(ret[i]));
    }
  } else {
    puts("NE");
  }
  return 0;
}
