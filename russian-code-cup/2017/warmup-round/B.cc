#include <cstdio>
#include <vector>
#include <map>
#include <set>

void output(std::vector<int> &p) {
  printf("%d", (int)p.size());
  for (auto &&e: p) printf(" %d", e);
  puts("");
}

int main() {
  std::vector<int> red, blue, black, yellow, pink;
  int n, m;
  scanf("%d%d", &n, &m);
  std::set<int> ml, mr;
  std::map<int, int> all;
  all[-1] = -1;
  all[n] = n;
  for (int i = 1; i <= m; ++i) {
    int x, y, tx, ty;
    scanf("%d%d", &x, &y);
    --x;
    tx = all.begin()->second + 1;
    ty = ml.count(tx) + 1;
    if (x == tx && y == ty) red.push_back(i);
    ty = !mr.count(tx) + 1;
    if (x == tx && y == ty) blue.push_back(i);
    tx = all.rbegin()->first - 1;
    ty = ml.count(tx) + 1;
    if (x == tx && y == ty) black.push_back(i);
    ty = !mr.count(tx) + 1;
    if (x == tx && y == ty) yellow.push_back(i);
    pink.push_back(i);
    if (y == 1) ml.insert(x);
    else mr.insert(x);
    if (ml.count(x) && mr.count(x)) {
      auto p = all.lower_bound(x);
      auto q = p; --q;
      if (q->second + 1 == x) {
        q->second = x;
        if (x + 1 == p->first) {
          q->second = p->second;
          all.erase(p);
        }
      } else if (x + 1 == p->first) {
        all[x] = p->second;
        all.erase(p);
      } else {
        all[x] = x;
      }
    }
  }
  output(red);
  output(blue);
  output(black);
  output(yellow);
  output(pink);
  return 0;
}
