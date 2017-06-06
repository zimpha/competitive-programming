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
#include "johnny.h"

const int N = 20000 + 10;
int deg[N];

int main() {
  srand(23333);
  int nodes = NumberOfNodes();
  int me = MyNodeId();
  int n = NumberOfCards();
  memset(deg, 0, sizeof(*deg) * n);
  int L = me * n / nodes, R = (me + 1) * n / nodes;
  for (int i = L; i < R; ++i) {
    for (int j = 0; j < n; ++j) {
      deg[i] += IsBetter(i, j);
    }
  }
  if (me) {
    for (int i = L; i < R; ++i) {
      put_int(0, deg[i]);
    }
    send(0);
  } else {
    for (int node = 1; node < nodes; ++node) {
      int l = node * n / nodes, r = (node + 1) * n / nodes;
      if (l >= r) continue;
      receive(node);
      for (int i = l; i < r; ++i) {
        deg[i] = get_int(node);
      }
    }
    std::sort(deg, deg + n, std::greater<int>());
    int ret = -1, sum = 0;
    for (int i = 0; i + 1 < n; ++i) {
      //printf("%d ", deg[i]);
      sum += deg[i];
      //printf("%d %d %d\n", sum, i * (i + 1) / 2, (i + 1) * (n - i - 1));
      if (sum - i * (i + 1) / 2 == (i + 1) * (n - i - 1)) ret = i;
    }
    if (ret == -1) puts("IMPOSSIBLE");
    else printf("%d\n", std::min(n - 1, ret + 1));
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
