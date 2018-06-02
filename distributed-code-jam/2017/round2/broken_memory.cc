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
using uint64 = unsigned long long;
using pll = std::pair<ll, ll>;

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
#include "broken_memory.h"

const int N = 10000000 + 10, M = 1000;

uint64 hash(uint64 key) {
  key ^= key >> 33;
  key *= 0xff51afd7ed558ccd;
  key ^= key >> 33;
  key *= 0xc4ceb9fe1a85ec53;
  key ^= key >> 33;
  return key;
}

uint64 val[N];

int main() {
  srand(23333);
  int nodes = NumberOfNodes();
  int me = MyNodeId();
  int n = GetLength();
  val[n] = 0;
  for (int i = n - 1; i >= 0; --i) {
    val[i] = hash(GetValue(i)) ^ hash(1ll * i * i + i + 1);
    val[i] += val[i + 1];
  }
  /*
  printf("%d: ", me);
  for (int i = 0; i <= n; ++i) printf("%lld ", (ll)val[i]);
  puts("");
  */
  auto compute = [&] (int mid) {
    return pll(val[0] - val[mid + 1], val[mid + 1] - val[n]);
  };
  auto left_or_right = [&] (pll a, pll b, pll c) {
    if (a.second == b.second || a.second == c.second) return true;
    if (a.first == b.first || a.first == c.first) return false;
    return b.first == c.first;
  };

  int left = 0, right = n - 1;
  for (int it = 0; it < 30; ++it) {
    int mid = (left + right - 1) >> 1;
    if (left == right) mid = left;
    pll my_value = compute(mid);
    // send query to [me + 1, me + 2]
    put_int((me + 1) % nodes, mid);
    send((me + 1) % nodes);
    put_int((me + 2) % nodes, mid);
    send((me + 2) % nodes);
    // recieve from query [me - 1, me - 2]
    receive((me - 1 + nodes) % nodes);
    pll to_send1 = compute(get_int((me - 1 + nodes) % nodes));
    receive((me - 2 + nodes) % nodes);
    pll to_send2 = compute(get_int((me - 2 + nodes) % nodes));
    // send answer to [me - 1, me - 2]
    put_pll((me - 1 + nodes) % nodes, {to_send1.first, to_send1.second});
    send((me - 1 + nodes) % nodes);
    put_pll((me - 2 + nodes) % nodes, {to_send2.first, to_send2.second});
    send((me - 2 + nodes) % nodes);
    // recieve answer from [me + 1, me + 2]
    receive((me + 1) % nodes);
    auto get1 = get_pll((me + 1) % nodes);
    receive((me + 2) % nodes);
    auto get2 = get_pll((me + 2) % nodes);
    if (left == right) continue;
    /*if (me == 0)
    printf("node[%d], [%d %d]: mid = %d, (%lld %lld) (%lld %lld) (%lld %lld), go_left=%d\n", 
        me, left, right, mid, 
        my_value.first, my_value.second,
        get1.first, get1.second,
        get2.first, get2.second,
        int(left_or_right(my_value, get1, get2)));*/
    if (left_or_right(my_value, get1, get2)) right = mid;
    else left = mid + 1;
  }

  if (me) {
    put_int(0, left);
    send(0);
  } else {
    printf("%d", left);
    for (int i = 1; i < nodes; ++i) {
      receive(i);
      printf(" %d", get_int(i));
    }
    puts("");
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
