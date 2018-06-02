#include <message.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <string>
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
#include "number_bases.h"

const int N = 1e6 + 10;

int A[N], B[N], C[N];

bool check(int b, int n, int &carry) {
  for (int i = 0; i < n; ++i) {
    if (A[i] >= b || C[i] >= b || B[i] >= b) return false;
    int x = A[i] + B[i] + carry;
    if (C[i] != x % b) return false;
    carry = x / b;
  }
  return true;
}

int main() {
  srand(23333);
  int nodes = NumberOfNodes();
  int me = MyNodeId();
  int n = GetLength();
  nodes = (n + N - 1) / N;
  if (me >= nodes) return 0;
  int L = me * N, R = std::min(L + N, n);
  int nn = R - L;
  int base = -1, invalid = 0;
  for (int i = L; i < R; ++i) {
    A[i - L] = GetDigitX(i);
    B[i - L] = GetDigitY(i);
    C[i - L] = GetDigitZ(i);
  }
  for (int i = 0; i < nn && !invalid && base == -1; ++i) {
    if (A[i] + B[i] < C[i]) {
      invalid = 1;
    } else if (A[i] + B[i] > C[i]) {
      base = A[i] + B[i] - C[i];
    }
  }
  if (me) {
    put_int(0, base);
    put_int(0, invalid);
    send(0);
  } else {
    for (int node = 1; node < nodes; ++node) {
      receive(node);
      int t_base = get_int(node);
      int t_invalid = get_int(node);
      if (base != -1) continue;
      if (invalid) continue;
      invalid |= t_invalid;
      base = t_base;
    }
    for (int node = 1; node < nodes; ++node) {
      put_int(node, base);
      put_int(node, invalid);
      send(node);
    }
  }
  if (me) {
    receive(0);
    base = get_int(0);
    invalid = get_int(0);
  }
  //printf("%d %d\n", (int)invalid, base);
  if (invalid) {
    if (!me) puts("IMPOSSIBLE");
    return 0;
  } else if (base == -1) {
    if (!me) puts("NON-UNIQUE");
    return 0;
  }
  int c0 = 0, c1 = 1;
  int f0 = check(base, nn, c0);
  int f1 = check(base, nn, c1);
  int valid = true;
  int send = 0;
  int carry = 0;
  if (me) {
    receive(me - 1);
    carry = get_int(me - 1);
    valid &= get_int(me - 1);
  }
  if (carry) send = c1, valid &= f1;
  else send = c0, valid &= f0;
  if (me + 1 != nodes) {
    put_int(me + 1, send);
    put_int(me + 1, valid);
    ::send(me + 1);
  } else if (me + 1 == nodes) {
    if (valid && send == 0) printf("%d\n", base);
    else puts("IMPOSSIBLE");
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
