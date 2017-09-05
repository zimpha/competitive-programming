#include <bits/stdc++.h>
using LL = long long;

const int N = 2000 + 10;

struct point {
  int x, y, w;
  bool operator < (const point &rhs) const {
    return x < rhs.x;
  }
};

struct query {
  int x1, y1, x2, y2;
  long long ans;
};

std::vector<query> ask;
std::vector<int> ql[N];
std::vector<point> gar[N];
int n, m, k;

struct event_t {
  int pos, type, idx;
  bool operator < (const event_t &rhs) const {
    return pos < rhs.pos || (pos == rhs.pos && type < rhs.type);
  }
};

LL u[N];
void add(int x, int v) {
  for (; x <= m; x += ~x & x + 1) u[x] += v;
}
LL get(int x, LL r = 0) {
  for (; x >= 0; x -= ~x & x + 1) r += u[x];
  return r;
}

void solve(int src) {
  std::vector<point> &p = gar[src];
  std::vector<event_t> ev;
  for (size_t i = 0; i < p.size(); ++i) {
    ev.push_back((event_t){p[i].x, -1, (int)i});
  }
  for (auto &&i: ql[src]) {
    ev.push_back((event_t){ask[i].x1 - 1, 0, i});
    ev.push_back((event_t){ask[i].x2, 1, i});
  }
  std::sort(ev.begin(), ev.end());
  for (int i = 0; i <= m; ++i) u[i] = 0;
  for (auto &&e: ev) {
    int i = e.idx;
    if (e.type == -1) {
      add(p[i].y, p[i].w);
    } else {
      int l = ask[i].y1, r = ask[i].y2;
      LL val = get(r) - get(l - 1);
      if (e.type == 0) ask[i].ans -= val;
      else ask[i].ans += val;
    }
  }
}

void run() {
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 0; i < k; ++i) {
    int len;
    scanf("%d", &len);
    while (len--) {
      int x, y, w;
      scanf("%d%d%d", &x, &y, &w);
      gar[i].push_back((point){x, y, w});
    }
  }
  std::vector<bool> flag(k, true);
  int q;
  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    char op[20];
    scanf("%s", op);
    if (op[0] == 'A') {
      int x1, y1, x2, y2;
      scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
      for (int j = 0; j < k; ++j) {
        if (flag[j]) ql[j].push_back(ask.size());
      }
      ask.push_back((query){x1, y1, x2, y2, 0});
    } else {
      int x;
      scanf("%d", &x);
      if (flag[x - 1]) flag[x - 1] = false;
      else flag[x - 1] = true;
    }
  }
  for (int i = 0; i < k; ++i) solve(i);
  for (auto &&x: ask) printf("%lld\n", x.ans);
}

int main() {
  run();
  return 0;
}
