#include <cstdio>
#include <unordered_map>

using int64 = long long;
const int N = 1e6 + 10;

char s[N];

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  int f = 0, g = 0;
  std::unordered_map<int64, int> map;
  scanf("%s", s);
  map[0] = 0;
  int ret = 0;
  for (int i = 0; i < n; ++i) {
    f += s[i] == 'O';
    g += s[i] == 'R';
    int64 v = f - (int64)k * g;
    auto it = map.find(v);
    if (it != map.end()) {
      ret = std::max(ret, i + 1 - it->second);
    } else {
      map[v] = i + 1;
    }
  }
  printf("%d\n", ret);
  return 0;
}
