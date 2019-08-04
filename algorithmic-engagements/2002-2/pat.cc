#include <cstdio>
#include <map>

int main() {
  int n;
  scanf("%d", &n);
  std::map<int, int> cnt;
  for (int i = 0; i < n; ++i) {
    int x;
    scanf("%d", &x);
    cnt[x]++;
  }
  int ret = 0;
  while (!cnt.empty()) {
    auto v = *cnt.begin();
    cnt.erase(cnt.begin());
    if (v.second & 1) ++ret;
    if (v.second > 1) cnt[v.first * 2] += v.second / 2;
  }
  printf("%d\n", ret);
  return 0;
}
