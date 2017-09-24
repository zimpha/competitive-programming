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
#include "broken_memory.h"

const int N = 10000000 + 10, M = 1000;

ll val[N];

int main() {
  srand(23333);
  int nodes = NumberOfNodes();
  int me = MyNodeId();
  int n = GetLength();
  val[n] = 0;
  for (int i = n - 1; i >= 0; --i) {
    val[i] = GetValue(i) + 1ll * i * i + i + 1;
    val[i] ^= val[i + 1];
  }
  int left = 0, right = n - 1;
  std::pair<int, int> rg[M];
  std::pair<ll, ll> hs[M], ts[M][3];

  auto get_ok = [](std::pair<ll, ll> v[3]) -> std::pair<ll, ll> {
    std::sort(v, v + 3);
    if (v[0].first == v[1].first) {
      return {v[0].first, -1};
    }
    if (v[1].first == v[2].first) {
      return {v[1].first, -1};
    }
    if (v[0].second == v[1].second) {
      return {-1, v[0].second};
    }
    if (v[0].second == v[2].second) {
      return {-1, v[0].second};
    }
    if (v[2].second == v[1].second) {
      return {-1, v[2].second};
    }
  };

  auto go = [](std::pair<ll, ll> a, std::pair<ll, ll> ok) {
    if (ok.first == -1) {
      if (a.second == ok.second) return 0;
      else return 1;
    } else {
      if (a.first == ok.first) return 1;
      else return 0;
    }
  };
  int cnt = 0;
  while (true) {
    int mid = (left + right) / 2;
    // [left, mid], [mid + 1, right]
    ll hl = val[left] ^ val[mid + 1];
    ll hr = val[mid + 1] ^ val[right + 1];
    put_pii(0, {left, right});
    put_pll(0, {hl, hr});
    send(0);
    ++cnt;

    if (me <= 2) {
      if (me == 0) {
        std::vector<int> ls(nodes), rs(nodes);
        for (int node = 0; node < nodes; ++node) {
          receive(node);
          rg[node] = get_pii(node);
          hs[node] = get_pll(node);
          ls[node] = rg[node].first;
          rs[node] = rg[node].second;
        }
        for (int i = 1; i < 3; ++i) {
          put_vint(i, ls);
          put_vint(i, rs);
          send(i);
        }
        std::vector<ll> hsl(nodes), hsr(nodes);
        for (int i = 0; i < nodes; ++i) {
          int ms = (ls[i] + rs[i]) / 2;
          hsl[i] = val[ls[i]] ^ val[ms + 1];
          hsr[i] = val[ms + 1] ^ val[rs[i] + 1];
        }
        for (int i = 0; i < nodes; ++i) {
          ts[i][0] = {hsl[i], hsr[i]};
        }
        for (int i = 1; i < 3; ++i) {
          receive(i);
          hsl = get_vll(i);
          hsr = get_vll(i);
          for (int j = 0; j < nodes; ++j) {
            ts[j][i] = {hsl[j], hsr[j]};
          }
        }
        if (cnt >= 1) {
          int t = 4;
          //printf("==%d %d\n", rg[t].first, rg[t].second);
        //  for (int i = 0; i < 3; ++i) {
        //    printf("%lld %lld\n", ts[t][i].first, ts[t][i].second);
        //  }
        }
        std::vector<int> dg(nodes);
        bool all = true;
        std::vector<std::pair<ll, ll>> valid(nodes);
        for (int i = 0; i < nodes; ++i) {
          all &= rg[i].first == rg[i].second;
          valid[i] = get_ok(ts[i]);
        }
        for (int i = 0; i < nodes; ++i) {
          dg[i] = go(hs[i], valid[i]);
          if (all) dg[i] = -1;
          put_int(i, dg[i]);
          send(i);
        }
      } else {
        receive(0);
        std::vector<int> ls = get_vint(0);
        std::vector<int> rs = get_vint(0);
        std::vector<ll> hsl(nodes), hsr(nodes);
        for (int i = 0; i < nodes; ++i) {
          int ms = (ls[i] + rs[i]) / 2;
          hsl[i] = val[ls[i]] ^ val[ms + 1];
          hsr[i] = val[ms + 1] ^ val[rs[i] + 1];
        }
        put_vll(0, hsl);
        put_vll(0, hsr);
        send(0);
      }
    }

    receive(0);
    int flag = get_int(0);
    if (flag == -1) break;
    if (left != right) {
      if (flag == 0) right = mid;
      else left = mid + 1;
    }
    if (cnt == 1) {
      //printf("%d %d\n", left, right);
    }
  }
  put_int(0, left);
  send(0);
  if (!me) {
    for (int node = 0; node < nodes; ++node) {
      receive(node);
      printf("%lld ", get_int(node));
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
