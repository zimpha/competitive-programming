#include <cstdio>
#include <vector>
#include <queue>

using int64 = long long;

const int N = 2e5 + 10;
const int mod = 1e9;

char s[N];

struct Group {
  char col;
  std::priority_queue<int> pq;
};

void merge(std::priority_queue<int> &a, std::priority_queue<int> &b) {
  if (a.size() < b.size()) std::swap(a, b);
  while (!b.empty()) {
    a.push(b.top());
    b.pop();
  }
}

int main() {
  int n, m;
  scanf("%d", &n);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  scanf("%d", &m);
  std::vector<int> b(m);
  for (int i = 0; i < m; ++i) scanf("%d", &b[i]);
  scanf("%s", s);
  std::vector<Group> groups;
  for (int i = 0; i < m; ++i) {
    if (i == 0 || s[i] != s[i - 1]) {
      groups.emplace_back();
      groups.back().col = s[i];
    }
    if (groups.back().col == 'B') {
      groups.back().pq.push(b[i]);
    } else {
      groups.back().pq.push(-b[i]);
    }
  }
  int64 last_ans = 0;
  for (int i = 0; i < n; ++i) {
    a[i] = (a[i] + last_ans) % mod;
    std::vector<Group> tg;
    for (auto &group: groups) {
      if (group.col == 'B') group.pq.push(a[i]);
      else group.pq.push(-a[i]);
      a[i] = group.pq.top();
      group.pq.pop();
      if (group.col == 'S') a[i] = -a[i];
      if (!tg.empty() && tg.back().col == group.col) {
        merge(tg.back().pq, group.pq);
      } else if (!tg.empty() && (tg.back().col == 'S' && group.col == 'B' && -tg.back().pq.top() >= group.pq.top())) {
        if (tg.size() >= 2) {
          merge(tg[tg.size() - 2].pq, group.pq);
        } else {
          tg.emplace_back();
          std::swap(tg.back(), group);
          std::swap(tg.back(), tg[tg.size() - 2]);
        }
      } else {
        tg.emplace_back();
        std::swap(tg.back(), group);
      }
    }
    groups.swap(tg);
    last_ans += a[i];
    printf("%lld ", last_ans);
  }
  puts("");
  return 0;
}
