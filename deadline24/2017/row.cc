#include <algorithm>
#include <cstdio>
#include <vector>
#include <map>
using namespace std;

const int N = 1000000 + 10;

multimap<int, int> mp;
int a[N], b[N], next[N];
int id[N], n;

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    mp.clear();
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
      int x; scanf("%d", &x);
      a[x - 1] = i;
      id[i] = i;
    }
    for (int i = 0; i < n; ++i) {
      int x; scanf("%d", &x);
      b[x - 1] = i;
    }
    std::sort(id, id + n, [&](int x, int y) {
      return a[x] < a[y] || (a[x] == a[y] && b[x] < b[y]);
    });
    std::vector<std::vector<int>> res;
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
      int v = b[id[i]];
      auto it = mp.upper_bound(v);
      if (it == mp.begin()) {
        res.push_back(std::vector<int>());
        res[cnt].push_back(id[i]);
        mp.insert({v, cnt});
        ++cnt;
      } else {
        --it;
        int t = it->second;
        res[it->second].push_back(id[i]);
        mp.erase(it);
        mp.insert({v, t});
      }
    }
    printf("%d\n", cnt);
    for (int i = 0; i < cnt; ++i) {
      printf("%d", (int)res[i].size());
      for (auto &&v: res[i]) {
        printf(" %d", v + 1);
      }
      puts("");
    }
  }
  return 0;
}
