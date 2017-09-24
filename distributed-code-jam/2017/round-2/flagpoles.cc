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
#include "flagpoles.h"

const int B = 10000010;

int main() {
  srand(23333);
  int nodes = NumberOfNodes();
  int me = MyNodeId();
  int n = GetNumFlagpoles() - 1;
  if (n == 0) {
    if (!me) puts("1");
    return 0;
  }
  nodes = (n + B - 1) / B;
  if (me >= nodes) return 0;
  int L = B * me, R = std::min(B * me + B, n);
  ll ls = -1, lv;
  ll rs, rv;
  ll mx = -1;
  ll last;
  ll cnt = 0;
  bool first = true;
  for (int i = L; i < R; ++i) {
    ll v = GetHeight(i) - GetHeight(i + 1);
    if (first) last = v, first = false;
    if (last == v) ++cnt;
    else {
      cnt = 1;
    }
    if (cnt == i - L + 1) ls = cnt, lv = v;
    mx = std::max(mx, cnt);
    last = v;
  }
  mx = std::max(mx, cnt);
  rs = cnt;
  rv = last;
  if (me) {
    put_ll(0, ls);
    put_ll(0, lv);
    put_ll(0, rs);
    put_ll(0, rv);
    put_ll(0, mx);
    send(0);
  } else {
    ll now = R - L;
    for (int node = 1; node < nodes; ++node) {
      receive(node);
      ll tls = get_ll(node);
      ll tlv = get_ll(node);
      ll trs = get_ll(node);
      ll trv = get_ll(node);
      mx = std::max(mx, get_ll(node));
      int l = B * node, r = B * node + B;
      if (r > n) r = n;
      ll len = r - l;
      if (rv == tlv) mx = std::max(mx, rs + tls);
      if (now == ls && lv == tlv) ls += tls;
      if (len == trs && trv == rv) rs += len;
      else rs = trs, rv = trv;
      now += len;
    }
    printf("%lld\n", mx + 1);
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
