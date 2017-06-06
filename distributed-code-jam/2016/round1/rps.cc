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
#include "rps.h"

bool win(char a, char b) {
  if (a == 'S') return b != 'R';
  if (a == 'R') return b != 'P';
  if (a == 'P') return b != 'S';
}

int main() {
  int nodes = NumberOfNodes();
  int me = MyNodeId();
  int n = GetN();
  int s = 1 << n;
  int B = 1;
  while (B * nodes < s) B *= 2;
  nodes = s / B;
  if (me >= nodes) return 0;
  int L = me * B, R = me * B + B;
  std::vector<char> move(B);
  std::vector<int> id(B);
  for (int i = L; i < R; ++i) {
    id[i - L] = i - L;
    move[i - L] = GetFavoriteMove(i);
  }
  while (B > 1) {
    std::vector<int> rest(B / 2);
    for (int i = 0; i < B; i += 2) {
      char a = move[id[i]], b = move[id[i + 1]];
      if (win(a, b)) rest[i / 2] = id[i];
      else rest[i / 2] = id[i + 1];
    }
    id.swap(rest);
    B /= 2;
  }
  if (me) {
    put_int(0, id[0] + L);
    send(0);
  } else {
    for (int node = 1; node < nodes; ++node) {
      receive(node);
      id.push_back(get_int(node));
    }
    B = nodes;
    while (B > 1) {
      std::vector<int> rest(B / 2);
      for (int i = 0; i < B; i += 2) {
        char a = GetFavoriteMove(id[i]), b = GetFavoriteMove(id[i + 1]);
        if (win(a, b)) rest[i / 2] = id[i];
        else rest[i / 2] = id[i + 1];
      }
      id.swap(rest);
      B /= 2;
    }
    printf("%d\n", id[0]);
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
