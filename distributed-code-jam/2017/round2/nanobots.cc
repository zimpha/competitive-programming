#include <message.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>

using ll = long long;
using int64 = long long;

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
#include "nanobots.h"

const int mod = 1e9 + 7, N = 1e5;

int get_range(int c, int n) {
  int left = 1, right = n;
  if (Experiment(c, right) == 'T') return n;
  if (Experiment(c, left) == 'E') return 0;
  while (left < right) {
    int mid = (left + right + 1) >> 1;
    if (Experiment(c, mid) == 'T') left = mid;
    else right = mid - 1;
  }
  return left;
}

int main() {
  srand(23333);
  int nodes = NumberOfNodes();
  int me = MyNodeId();
  int64 n = GetRange();
  std::vector<int64> ends;
  const int splits = nodes * (N + 1);
  int64 len = (n + splits - 1) / splits;
  for (int64 i = 0; i < n; i += len) {
    ends.emplace_back(i);
  }
  std::random_shuffle(ends.begin(), ends.end());
  std::vector<int64> my_ends;
  for (int i = 0; i < ends.size(); ++i) {
    if (i % nodes == me) my_ends.emplace_back(ends[i]);
  }

  auto query = [&](int64 x, int64 y) {
    return Experiment(x + 1, y + 1) == 'T';
  };
  
  int64 ret = 0;
  for (auto &&l : my_ends) {
    int64 r = std::min(l + len, n);
    for (; l < r; ) {
      if (!query(l, 0)) break;
      int64 left = 0, right = n - 1;
      while (left < right) {
        int64 mid = (left + right + 1) >> 1;
        if (query(l, mid)) left = mid;
        else right = mid - 1;
      }
      int64 height = left;
      left = l, right = r - 1;
      while (left < right) {
        int64 mid = (left + right + 1) >> 1;
        if (query(mid, height)) left = mid;
        else right = mid - 1;
      }
      int64 width = left - l;
      ret += (height + 1) % mod * ((width + 1) % mod) % mod;
      l = left + 1;
    }
    ret %= mod;
  }
  if (me) {
    put_ll(0, ret);
    send(0);
  } else {
    for (int i = 1; i < nodes; ++i) {
      receive(i);
      ret += get_ll(i);
      ret %= mod;
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
