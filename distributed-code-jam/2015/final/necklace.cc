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
#include "necklace.h"
const int N = 3000 + 10, M = 10000 + 10;
std::vector<int> nx[M];
int go[N], msg[N];

int main() {
  srand(23333);
  int nodes = NumberOfNodes();
  int me = MyNodeId();
  int n = GetNecklaceLength();
  int m = GetMessageLength();
  int L = 1ll * me * n / nodes, R = 1ll * (me + 1) * n / nodes;
  for (int i = 0; i < m; ++i) msg[i] = GetMessageElement(i);
  for (int i = 0; i < m; ++i) {
    nx[msg[i]].push_back(i);
    go[i] = 0;
  }
  for (int i = L; i < R; ++i) {
    int o = GetNecklaceElement(i);
    std::vector<int> extanded = nx[o];
    for (auto &&e: nx[o]) ++go[e];
    nx[o].clear();
    for (auto &&e: extanded) {
      if (e + go[e] < m) {
        nx[msg[e + go[e]]].push_back(e);
      }
    }
  }
  for (int i = 0; i < m; ++i) {
    go[i] += i;
  }
  if (me) {
    for (int i = 0; i < m; ++i) {
      put_int(0, go[i]);
    }
    send(0);
  } else {
    static int tg[N << 1];
    for (int node = 1; node < nodes; ++node) {
      receive(node);
      for (int i = 0; i < m * 2; ++i) tg[i] = 0;
      for (int i = 0; i < m; ++i) {
        tg[i + m] = get_int(node);
      }
      for (int i = m - 1; i >= 0; --i) {
        tg[i] = std::max(tg[i << 1], tg[i << 1 | 1]);
      }
      for (int i = m - 1; i >= 0; --i) {
        int l = i, r = go[i] + 1, mx = 0;
        for (l += m, r += m; l < r; l >>= 1, r >>= 1) {
          if (l & 1) mx = std::max(mx, tg[l++]);
          if (r & 1) mx = std::max(mx, tg[--r]);
        }
        if (mx > go[i]) go[i] = mx;
        //printf("%d %d\n", i, mx);
      }
    }
    int ret = 0;
    for (int i = 0; i < m; ++i) {
      ret = std::max(ret, go[i] - i);
    }
    printf("%d\n", ret);
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
