#include <cstdio>
#include <algorithm>

const int N = 100000000;
using ll = long long;
using ii = __int128;

const int p[] = {2, 3, 5, 7, 11, 13, 17, 19};
int S[8][1000];
ii A[N];
int idx[8];

ll calc(ll p, ll c) {
  ll l = 0, r = p * c;
  while (l < r) {
    ll m = (l + r - 1) >> 1;
    ll v = 0;
    for (int i = p; i <= m; i *= p) v += m / i;
    if (v >= c) r = m;
    else l = m + 1;
  }
  return l;
}

void prepare() {
  for (int i = 0; i < 8; ++i) {
    for (int c = 0; c < 1000; ++c) {
      S[i][c] = calc(p[i], c);
    }
  }
}

ll calc(ii n) {
  ll ret = 0;
  for (int i = 0; i < 8; ++i) {
    ll c = 0;
    while (n % p[i] == 0) n /= p[i], ++c;
    ret = std::max<ll>(ret, S[i][c]);
  }
  return ret;
}

int main() {
  prepare();
  A[0] = 1;
  for (int i = 0; i < 8; ++i) idx[i] = 0;
  ll ret = 0;
  for (int i = 1; i < N; ++i) {
    ii mx = A[idx[0]] * p[0];
    for (int i = 1; i < 8; ++i) {
      mx = std::min(mx, A[idx[i]] * p[i]);
    }
    for (int i = 0; i < 8; ++i) {
      if (mx == A[idx[i]] * p[i]) ++idx[i];
    }
    A[i] = mx;
    ret += calc(mx);
  }
  printf("%lld\n", ret);
  return 0;
}
