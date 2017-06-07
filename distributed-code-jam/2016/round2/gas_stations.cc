#include <message.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using ll = long long;

void receive(int);
void send(int);
void put_ll(int, ll);
ll get_ll(int);
void put_int(int, int);
int get_int(int);
void put_char(int, char);
char get_char(int);
void put_vll(int, const std::vector<ll>&);
std::vector<ll> get_vll(int);
void put_vint(int, const std::vector<int>&);
std::vector<int> get_vint(int);
void put_str(int, const std::string &s);
std::string get_str(int);
void put_pll(int, const std::pair<ll, ll>&);
std::pair<ll, ll> get_pll(int);
void put_pii(int, const std::pair<int, int>&);
std::pair<int, int> get_pii(int);

// Algorithm Begin
#include "gas_stations.h"
const int B = 5000000 + 1, N = B + 10, M = 100 + 10;
const int inf = 1e9;

int mx[M], price[N], queue[N];

int main() {
  int nodes = NumberOfNodes();
  int me = MyNodeId();
  int n = GetNumKms() + 1;
  int m = GetTankSize();
  nodes = (n + B - 1) / B;
  if (me >= nodes) return 0;
  int L = me * B, R = std::min(L + B, n);
  mx[me] = inf;
  for (int i = L; i < R; ++i) {
    if (R == n && i == R - 1) price[i - L] = 0;
    else price[i - L] = GetGasPrice(i);
    mx[me] = std::min(mx[me], price[i - L]);
  }
  if (me) {
    receive(me - 1);
    for (int i = 0; i < me; ++i) {
      mx[i] = get_int(me - 1);
    }
  }
  if (me + 1 < nodes) {
    for (int i = 0; i <= me; ++i) {
      put_int(me + 1, mx[i]);
    }
    send(me + 1);
  }
  for (int i = me - 2; i >= 0; --i) {
    mx[i] = std::min(mx[i + 1], mx[i]);
  }
  ll ret = 0;
  if (m + L < R) {
    int h = 0, t = -1;
    for (int i = 0; i < m; ++i) {
      while (h <= t && price[i] <= price[queue[t]]) --t;
      queue[++t] = i;
    }
    for (int i = m; i < R - L; ++i) {
      while (h <= t && queue[h] < i - m) ++h;
      ret += price[queue[h]];
      while (h <= t && price[i] <= price[queue[t]]) --t;
      queue[++t] = i;
    }
  }
  for (int i = 1; i < R - L; ++i) {
    price[i] = std::min(price[i], price[i - 1]);
  }
  int u = std::min(R - 1, L + m - 1), v = std::max(1, L);
  int x = std::max(0, u - m);
  int y = x / B * B + B;
  ll mx1 = inf, mx2 = inf;
  if (x / B + 1 < me) mx1 = mx[x / B + 1];
  for (int i = x; i < y && i < L; ++i) {
    mx1 = std::min(mx1, GetGasPrice(i));
  }
  for (int i = u; i >= v; --i) {
    if (i != L) mx2 = price[i - L - 1];
    else mx2 = inf;
    ret += std::min(mx1, mx2);
    mx1 = std::min(mx1, GetGasPrice(std::max(0, --x)));
  }
  if (me) {
    put_ll(0, ret);
    send(0);
  } else {
    for (int node = 1; node < nodes; ++node) {
      if (1ll * node * B >= n) continue;
      receive(node);
      ret += get_ll(node);
    }
    printf("%lld\n", ret);
  }
  return 0;
}

// Algorithm End

void receive(int node) {
  Receive(node);
}

void send(int node) {
  Send(node);
}

void put_ll(int node, ll value) {
  PutLL(node, value);
}

ll get_ll(int node) {
  return GetLL(node);
}

void put_int(int node, int value) {
  PutInt(node, value);
}

int get_int(int node) {
  return GetInt(node);
}

void put_char(int node, char value) {
  PutChar(node, value);
}

char get_char(int node) {
  return GetChar(node);
}

void put_vll(int node, const std::vector<ll> &v) {
  put_int(node, v.size());
  for (auto &&e: v) put_ll(node, e);
}

std::vector<ll> get_vll(int node) {
  int n = get_int(node);
  std::vector<ll> res(n);
  for (int i = 0; i < n; ++i) res[i] = get_ll(node);
  return res;
}

void put_vint(int node, const std::vector<int> &v) {
  put_int(node, v.size());
  for (auto &&e: v) put_int(node, e);
}

std::vector<int> get_vint(int node) {
  int n = get_int(node);
  std::vector<int> res(n);
  for (int i = 0; i < n; ++i) res[i] = get_int(node);
  return res;
}

void put_str(int node, const std::string &s) {
  put_int(node, s.size());
  for (auto &&c: s) put_char(node, c);
}

std::string get_str(int node) {
  int n = get_int(node);
  std::string res(n, ' ');
  for (int i = 0; i < n; ++i) res[i] = get_char(node);
  return res;
}

void put_pll(int node, const std::pair<ll, ll> &p) {
  put_ll(node, p.first);
  put_ll(node, p.second);
}

std::pair<ll, ll> get_pll(int node) {
  std::pair<ll, ll> res;
  res.first = get_ll(node);
  res.second = get_ll(node);
  return res;
}

void put_pii(int node, const std::pair<int, int> &p) {
  put_int(node, p.first);
  put_int(node, p.second);
}

std::pair<int, int> get_pii(int node) {
  std::pair<int, int> res;
  res.first = get_int(node);
  res.second = get_int(node);
  return res;
}
