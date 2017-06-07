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
#include "rocks.h"

const int N = 10000 + 10;

std::vector<bool> rock[N];
std::vector<int> need_up[N], need_right[N];
std::vector<int> can_up[N], can_right[N];

int main() {
  int nodes = NumberOfNodes();
  int me = MyNodeId();
  int n = GetN();
  int k = GetK();
  if (nodes > n) nodes = n;
  if (me >= nodes) return 0;
  int L = me * n / nodes, R = (me + 1) * n / nodes;
  int m = R - L;
  for (int i = 0; i < n; ++i) {
    rock[i].assign(m + 1, true);
    need_up[i].assign(m + 1, k + 1);
    need_right[i].assign(m + 1, k + 1);
    can_up[i].assign(m + 1, 0);
    can_right[i].assign(m + 1, 0);
  }
  for (int x = 0; x < n; ++x) {
    for (int y = L; y <= R; ++y) {
      rock[x][y - L] = y < n ? IsRock(x, y) : true;
    }
  }
  if (!me) need_up[0][0] = need_right[0][0] = 0;
  for (int y = 0; y < m; ++y) {
    int empty = 0;
    for (int x = n - 1; x >= 0; --x) {
      can_right[x][y] = empty;
      empty += !rock[x][y];
      if (x + k < n) empty -= !rock[x + k][y];
    }
  }
  for (int block = 0; block < nodes; ++block) {
    if (me + 1 < nodes) receive(me + 1);
    int lx = block * n / nodes, rx = (block + 1) * n / nodes;
    for (int x = lx; x < rx; ++x) {
      int empty = (me + 1 == nodes) ? 0 : get_int(me + 1);
      for (int y = m - 1; y >= 0; --y) {
        can_up[x][y] = empty;
        empty += !rock[x][y];
        if (y + L + k < n) empty -= !IsRock(x, y + L + k);
      }
      if (me) put_int(me - 1, empty);
    }
    if (me) send(me - 1);
  }
  for (int block = 0; block < nodes; ++block) {
    if (me) receive(me - 1);
    int lx = block * n / nodes, rx = (block + 1) * n / nodes;
    for (int x = lx; x < rx; ++x) {
      if (me) need_up[x][0] = get_int(me - 1);
      for (int y = 0; y < m; ++y) {
        if (need_up[x][y] <= can_up[x][y]) {
          if (x + 1 < n) need_right[x + 1][y] = rock[x + 1][y];
          if (y + L + 1 < n && need_up[x][y + 1] == k + 1) {
            need_up[x][y + 1] = need_up[x][y] + rock[x][y + 1];
          }
        }
        if (need_right[x][y] <= can_right[x][y]) {
          if (y + L + 1 < n) need_up[x][y + 1] = rock[x][y + 1];
          if (x + 1 < n && need_right[x + 1][y] == k + 1) {
            need_right[x + 1][y] = need_right[x][y] + rock[x + 1][y];
          }
        }
        if (y == m - 1 && me + 1 < nodes) {
          put_int(me + 1, need_up[x][m]);
        }
      }
    }
    if (me + 1 < nodes) send(me + 1);
  }
  if (me + 1 == nodes) {
    if (need_up[n - 1][m - 1] == 0 || need_right[n - 1][m - 1] == 0) {
      puts("YES");
    } else {
      puts("NO");
    }
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
