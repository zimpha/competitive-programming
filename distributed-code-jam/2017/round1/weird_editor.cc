#include "weird_editor.h"
#include <message.h>
#include <bits/stdc++.h>

const int N = 10000000 + 10, mod = 1e9 + 7;
int A[N], cnt[10];

void update(int x[], int y[], int &last) {
  for (int i = 0; i < 10; ++i) if (y[i]) {
    if (i == last) x[last] += y[i];
    else if (i > last) {
      last = i;
      x[last] += y[i];
    }
  }
}

using ll = long long;

ll pow_mod(ll a, ll n, ll mod) {
  ll r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

void mul(ll a[2][2], ll b[2][2]) {
  ll c[2][2];
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      c[i][j] = 0;
      for (int k = 0; k < 2; ++k) {
        c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % mod;
      }
    }
  }
  memcpy(a, c, sizeof(c));
}

ll solve(int n, int x) {
  ll a[2][2] = {{10, x}, {0, 1}};
  ll r[2] = {0, 1};
  if (n == 0) return 0;
  for (; n; n >>= 1) {
    if (n & 1) {
      ll t[2];
      for (int i = 0; i < 2; ++i) {
        t[i] = 0;
        for (int j = 0; j < 2; ++j) {
          t[i] = (t[i] + a[i][j] * r[j]) % mod;
        }
      }
      r[0] = t[0];
      r[1] = t[1];
    }
    mul(a, a);
  }
  return r[0];
}

int main() {
  int n = GetNumberLength();
  int me = MyNodeId();
  int nodes = NumberOfNodes();
  int L = 1ll * n * me / nodes, R = 1ll * n * (me + 1) / nodes;
  for (int i = L; i < R; ++i) {
    A[i - L] = GetDigit(i);
  }
  int last = 0;
  int m = R - L;
  for (int i = m - 1; i >= 0; --i) {
    if (A[i] == last) ++cnt[last];
    else if (A[i] > last) {
      last = A[i];
      cnt[last]++;
    }
  }
  if (me) {
    for (int i = 0; i < 10; ++i) {
      PutInt(0, cnt[i]);
    }
    Send(0);
  } else {
    int new_cnt[10];
    memset(new_cnt, 0, sizeof(new_cnt));
    last = 0;
    for (int node = nodes - 1; node >= 1; --node) {
      int ss[10];
      Receive(node);
      for (int i = 0; i < 10; ++i) {
        ss[i] = GetInt(node);
      }
      update(new_cnt, ss, last);
    }
    update(new_cnt, cnt, last);
    for (int i = 1; i < 10; ++i) n -= new_cnt[i];
    cnt[0] = n;
    for (int i = 1; i < 10; ++i) {
      cnt[i] = cnt[i - 1] + new_cnt[i];
    }
    ll ret = 0;
    for (int i = 1; i < 10; ++i) {
      ret += solve(new_cnt[i], i) * pow_mod(10, cnt[i - 1], mod) % mod;
      ret %= mod;
    }
    printf("%lld\n", ret);
  }
  return 0;
}
