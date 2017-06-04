#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

using ll = long long;

const int N = 18;

char d[N][20];
ll upp, target, pw[N];
int n;

std::string trans(ll x) {
  std::string s(n, ' ');
  for (int i = 0; i < n; ++i) {
    s[i] = d[i][x % 10];
    x /= 10;
  }
  return s;
}

ll solve(ll x, ll y) {
  ll bound = std::min(upp - x, upp - y);
  ll ret = 0;
  for (int i = 0; i < n && ret < bound; ++i) {
    for (int it = 0; it < 10 && ret < bound; ++it) {
      ll rx = x % pw[i], ry = y % pw[i], delta;
      if (rx < ry) delta = pw[i] - ry;
      else delta = pw[i] - rx;
      delta = std::min(delta, bound - ret);
      x += delta;
      y += delta;
      ret += delta;
      if (ret == bound || trans(x) != trans(y)) return ret;
    }
  }
  return bound;
}

int main() {
  pw[0] = 1;
  for (int i = 1; i < N; ++i) {
    pw[i] = pw[i - 1] * 10;
  }
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d%lld", &n, &target);
    upp = 1;
    for (int i = n - 1; i >= 0; --i) {
      upp = upp * 10;
      scanf("%s", d[i]);
    }
    std::vector<ll> candidate;
    for (int i = 0; i < n; ++i) {
      ll u = target / pw[i], v = target % pw[i];
      for (int d = 0; d < 10; ++d) {
        ll x = (u / 10 * 10 + d) * pw[i] + v;
        if (x != target && trans(x) == trans(target)) {
          candidate.push_back(x);
        }
      }
    }
    ll ret = 0;
    for (auto &&x: candidate) {
      //printf("%lld %lld\n", x, solve(target, x));
      ret = std::max(ret, solve(target, x));
    }
    printf("%lld\n", ret);
  }
  return 0;
}
