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
#include "kolakoski.h"
#include <cassert>

const int N = 100000000, B = 20;

ll extand[1 << B];
ll bits[1 << B];
unsigned int mask[30];
unsigned int s[N];
unsigned int m;

int get(unsigned int p) {
  return s[p >> 5] >> (p & 31) & 1;
}

void set(unsigned int p, int o) {
  int x = p >> 5, y = p & 31;
  unsigned int v = (s[x] >> y & 1) << y;
  s[x] ^= v;
  s[x] |= o << y;
}

unsigned int get_from(unsigned int p) {
  int x = p >> 5, y = p & 31;
  unsigned int r = s[x] >> y;
  if (32 - y >= B) return r & mask[B];
  else return (r | ((s[x + 1] & mask[y + B - 32]) << (32 - y))) & mask[B];
}

void set_from(unsigned int p, int l, ll v) {
  int x = p >> 5, y = p & 31;
  if (l <= 32 - y) {
    s[x] |= v << y;
  } else {
    ll u = v >> (32 - y) << (32 - y);
    s[x] |= (v ^ u) << y;
    l -= 32 - y;
    u >>= 32 - y;
    while (l >= 32) {
      s[++x] = u;
      u >>= 32;
      l -= 32;
    }
    s[x + 1] = u;
  }
}

void prepare() {
  for (int mask = 0; mask < (1 << B); ++mask) {
    ll v = 0, s = 0;
    for (int i = 0; i < B; ++i) {
      int e = 1 + (mask >> i & 1);
      while (e--) v |= ll(i & 1) << (s++);
    }
    extand[mask] = v;
    bits[mask] = s;
  }
  m = 0;
  set(0, 0); set(1, 1);
  for (int i = 0; i < 60; ++i) {
    int e = 1 + get(i);
    while (e--) set(m++, i & 1);
  }
  m = 0;
  for (unsigned int i = 0; m < 3000000000ll; i += 20) {
    int v = get_from(i);
    set_from(m, bits[v], extand[v]);
    m += bits[v];
  }
}

int main() {
  for (int i = 0; i < 30; ++i) mask[i] = (1 << i) - 1;
  prepare();
  int nodes = NumberOfNodes();
  int me = MyNodeId();
  ll n = GetIndex();
  ll L = 1ll * me * n / nodes, R = 1ll * (me + 1) * n / nodes;
  ll ret = 0;
  for (ll i = L; i < R; ++i) {
    ret += (get(i) + 1) * GetMultiplier(i);
  }
  if (me) {
    put_ll(0, ret);
    send(0);
  } else {
    for (int node = 1; node < nodes; ++node) {
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
