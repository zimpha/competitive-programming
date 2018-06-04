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
#include "baby_blocks.h"

int main() {
  srand(23333);
  int nodes = NumberOfNodes();
  int me = MyNodeId();
  int n = GetNumberOfBlocks();
  int block_size = (n + nodes - 1) / nodes;
  nodes = (n + block_size - 1) / block_size;
  //if (!me) printf("%d %d %d\n", nodes, block_size, n);
  assert(nodes * block_size >= n);
  if (me >= nodes) return 0;
  int L = me * block_size, R = std::min(n, L + block_size);
  int64 sum = 0;
  for (int i = L; i < R; ++i) sum += GetBlockWeight(i);
  std::vector<int64> block_sum(nodes);
  put_ll(0, sum);
  send(0);
  if (!me) {
    for (int i = 0; i < nodes; ++i) {
      receive(i);
      block_sum[i] = get_ll(i);
    }
    for (int i = 1; i < nodes; ++i) {
      put_vll(i, block_sum);
      send(i);
    }
  } else {
    receive(0);
    block_sum = get_vll(0);
  }
  // assign [i, j] to each nodes
  if (!me) {
    std::vector<std::pair<int, int>> tasks;
    for (int i = 0; i < nodes; ++i) {
      int64 sumi = 0;
      for (int k = 0; k < i; ++k) sumi += block_sum[k];
      // [sumi + 1, sumi + block_sum[i]]
      for (int j = i; j < nodes; ++j) {
        int64 sumj = 0;
        for (int k = j + 1; k < nodes; ++k) sumj += block_sum[k];
        // [sumj + 1, sumj + block_sum[j]]
        int64 l = std::max(sumi + 1, sumj + 1);
        int64 r = std::min(sumi + block_sum[i], sumj + block_sum[j]);
        if (l <= r) tasks.emplace_back(i, j);
      }
    }
    for (size_t i = 0; i < tasks.size(); ++i) {
      put_pii(i % nodes, tasks[i]);
    }
    for (int i = 0; i < nodes; ++i) {
      put_pii(i, {-1, -1});
      send(i);
    }
  }
  receive(0);
  int64 ret = 0;
  while (true) {
    auto task = get_pii(0);
    if (task.first == -1) break;
    int l1 = block_size * task.first, r1 = std::min(n, l1 + block_size);
    int l2 = block_size * task.second, r2 = std::min(n, l2 + block_size);
    int64 sum1 = 0, sum2 = 0;
    for (int i = 0; i < task.first; ++i) sum1 += block_sum[i];
    for (int i = task.second + 1; i < nodes; ++i) sum2 += block_sum[i];
    sum2 += GetBlockWeight(r2 - 1);
    for (int i = l1, j = r2 - 1; i < r1 && i < j && j >= l2; ++i) {
      sum1 += GetBlockWeight(i);
      while (j - 1 > i && j - 1 >= l2 && sum1 > sum2) {
        sum2 += GetBlockWeight(--j);
      }
      if (sum1 == sum2) ++ret;
    }
  }
  if (me) {
    put_ll(0, ret);
    send(0);
  } else {
    for (int i = 1; i < nodes; ++i) {
      receive(i);
      ret += get_ll(i);
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
