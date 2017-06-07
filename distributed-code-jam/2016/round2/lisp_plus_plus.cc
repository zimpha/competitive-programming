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
#include "lisp_plus_plus.h"
using pii = std::pair<int, int>;

pii merge(pii a, pii b) {
  int e = std::min(a.second, b.first);
  return {a.first + b.first - e, a.second + b.second - e};
}

int main() {
  srand(23333);
  int nodes = NumberOfNodes();
  int me = MyNodeId();
  int n = GetLength();
  int L = 1ll * me * n / nodes, R = 1ll * (me + 1) * n / nodes;
  pii a{0, 0}, b{0, 0};
  for (int i = L; i < R; ++i) {
    char c = GetCharacter(i);
    if (c == ')') a = merge(a, {1, 0});
    else a = merge(a, {0, 1});
  }
  if (me) {
    receive(me - 1);
    b = get_pii(me - 1);
  }
  if (me + 1 < nodes) {
    put_pii(me + 1, merge(b, a));
    send(me + 1);
  }
  int ret = -1, ext = -1;
  for (int i = L; i < R; ++i) {
    char c = GetCharacter(i);
    if (c == ')') b = merge(b, {1, 0});
    else b = merge(b, {0, 1});
    if (b.first == 0 && b.second == 0) {
      ret = i;
    }
    if (b.first == 0) ext = i;
  }
  if (me) {
    put_int(0, ret);
    put_int(0, ext);
    send(0);
  } else {
    for (int node = 1; node < nodes; ++node) {
      receive(node);
      int tr = get_int(node);
      int te = get_int(node);
      if (te != -1) ext = te;
      if (tr != -1) ret = tr;
    }
    ret += 1;
    if (ret == n) ext = -1;
    else ext += 1;
    printf("%d\n", ext);
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
