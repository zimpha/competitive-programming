#include <bits/stdc++.h>

const int N = 1000000 + 10, M = 1000000 + 10;

int sum[N], nx[N];
int l[M], r[M], ret[M];
int a[N], n, m;

struct event_t {
  int pos, type, idx;
  event_t() {}
  event_t(int pos, int type, int idx): pos(pos), type(type), idx(idx) {}
  bool operator < (const event_t &rhs) const {
    return pos < rhs.pos || (pos == rhs.pos && type < rhs.type);
  }
};

int u[N];
void add(int x, int v) {
  for (; x <= n; x += ~x & x + 1) u[x] ^= v;
}
int get(int x, int r = 0) {
  for (; x >= 0; x -= ~x & x + 1) r ^= u[x];
  return r;
}

void run() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", a + i);
  }
  sum[n] = 0;
  for (int i = n - 1; i >= 0; --i) {
    sum[i] = sum[i + 1] ^ a[i];
  }
  std::map<int, int> pos;
  for (int i = n - 1; i >= 0; --i) {
    if (!pos.count(a[i])) pos[a[i]] = -1;
    nx[i] = pos[a[i]];
    pos[a[i]] = i;
  }
  scanf("%d", &m);
  std::vector<event_t> ev;
  for (int i = 0; i < m; ++i) {
    scanf("%d%d", l + i, r + i);
    l[i]--, r[i]--;
    ret[i] = sum[l[i]] ^ sum[r[i] + 1];
    ev.push_back(event_t(l[i], -1, i));
  }
  for (int i = 0; i < n; ++i) {
    ev.push_back(event_t(i, 0, i));
  }
  std::sort(ev.begin(), ev.end());
  for (int i = 0; i < n; ++i) u[i] = 0;
  for (auto &&e: pos) {
    add(e.second, e.first);
  }
  for (auto &&e: ev) {
    if (e.type == 0) {
      if (nx[e.idx] != -1) {
        add(nx[e.idx], a[e.idx]);
      }
    } else {
      ret[e.idx] ^= get(r[e.idx]) ^ get(l[e.idx] - 1);
    }
  }
  for (int i = 0; i < m; ++i) {
    printf("%d\n", ret[i]);
  }
}

int main() {
  run();
  return 0;
}
