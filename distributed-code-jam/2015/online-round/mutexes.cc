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
#include "mutexes.h"

const int N = 40000 + 10, M = 401, S = 100000 + 10;

int A[N], B[N];
bool mux[2][S];
int n, m, cnt;

void add(int i, int v) {
  mux[i][v] = true;
  if (mux[i ^ 1][v]) ++cnt;
}

void del(int i, int v) {
  mux[i][v] = false;
  if (mux[i ^ 1][v]) --cnt;
}

int main() {
  srand(23333);
  int nodes = NumberOfNodes();
  int me = MyNodeId();
  n = NumberOfOperations(0);
  m = NumberOfOperations(1);
  //nodes = n / M + 1;
  //if (me >= nodes) return 0;
  int s = n + m;
  for (int i = 0; i < n; ++i) {
    A[i] = GetOperation(0, i);
  }
  for (int i = 0; i < m; ++i) {
    B[i] = GetOperation(1, i);
  }
  int L = me * n / nodes, R = (me + 1) * n / nodes;
  int ret = s + 1;
  for (int i = 0; i < L; ++i) {
    if (A[i] > 0) add(0, A[i]);
    else del(0, -A[i]);
  }
  for (int j = 0; j < m; ++j) {
    for (int i = L; i < R; ++i) {
      if (A[i] > 0 && B[j] > 0) {
        if (mux[0][B[j]] && mux[1][A[i]] && !cnt) {
          ret = std::min(ret, i + j + 2);
        }
      }
      if (A[i] > 0) add(0, A[i]);
      else del(0, -A[i]);
    }
    for (int i = R - 1; i >= L; --i) {
      if (A[i] > 0) del(0, A[i]);
      else add(0, -A[i]);
    }
    if (B[j] > 0) add(1, B[j]);
    else del(1, -B[j]);
  }
  if (me) {
    put_int(0, ret);
    send(0);
  } else {
    for (int node = 1; node < nodes; ++node) {
      receive(node);
      int tmp = get_int(node);
      ret = std::min(ret, tmp);
    }
    if (ret > s) puts("OK");
    else printf("%d\n", ret);
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
