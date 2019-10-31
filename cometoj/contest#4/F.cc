#include <cstdio>
#include <cassert>
#include <vector>
#include <map>
#include <algorithm>

using int64 = long long;
using uint64 = unsigned long long;

const int mod = 1e9 + 7;
const int N = 100;

std::vector<std::pair<uint64, uint64>> count[N];

inline uint64 rev(uint64 ns) {
  ns = ((ns & 0xaaaaaaaaaaaaaaaaull) >>  1) | ((ns & 0x5555555555555555ull) <<  1);
  ns = ((ns & 0xccccccccccccccccull) >>  2) | ((ns & 0x3333333333333333ull) <<  2);
  ns = ((ns & 0xf0f0f0f0f0f0f0f0ull) >>  4) | ((ns & 0x0f0f0f0f0f0f0f0full) <<  4);
  ns = ((ns & 0xff00ff00ff00ff00ull) >>  8) | ((ns & 0x00ff00ff00ff00ffull) <<  8);
  ns = ((ns & 0xffff0000ffff0000ull) >> 16) | ((ns & 0x0000ffff0000ffffull) << 16);
  ns = ((ns & 0xffffffff00000000ull) >> 32) | ((ns & 0x00000000ffffffffull) << 32);
  return ns;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) count[i].clear();
    std::vector<int> p(n);
    uint64 candidate = (uint64(1) << n) - 1;
    uint64 mask = candidate;
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
      scanf("%d", &p[i]);
      --p[i];
      if (p[i] == -1) {
        ++cnt;
      } else {
        candidate ^= uint64(1) << p[i];
      }
    }
    if (p[0] == -1) {
      for (int i = 0; i < n; ++i) if (candidate >> i & 1) {
        count[0].emplace_back(uint64(1) << i, uint64(1));
      }
    } else {
      count[0].emplace_back(uint64(1) << p[0], uint64(1));
    }

    int64 ret = 1;
    for (int i = 1; i <= cnt; ++i) {
      ret = ret * i % mod;
    }

    for (int i = 1; i < n; ++i) {
      if (p[i] == -1) {
        for (auto &&e: count[i - 1]) {
          auto s = e.first, ns = rev(s);
          for (uint64 msk = candidate ^ (candidate & s); msk; ) {
            int j = __builtin_ctzll(msk);
            assert(~s >> j & 1);
            uint64 z = (j <= 31) ? (ns >> (63 - 2 * j)) : (ns << (2 * j - 63));
            z &= mask;
            if ((z | s) == s) {
              count[i].emplace_back(s ^ (uint64(1) << j), e.second);
            }
            msk ^= uint64(1) << j;
          }
        }
      } else {
        for (auto &&e: count[i - 1]) {
          auto s = e.first, ns = rev(s);
          if (s >> p[i] & 1) continue;
          ns = (p[i] <= 31) ? (ns >> (63 - 2 * p[i])) : (ns << (2 * p[i] - 63));
          ns &= mask;
          if ((ns | s) == s) {
            count[i].emplace_back(s | (uint64(1) << p[i]), e.second);
          }
        }
      }
      if (count[i].size()) {
        std::sort(count[i].begin(), count[i].end());
        int m = 1;
        for (size_t j = 1; j < count[i].size(); ++j) {
          if (count[i][j].first != count[i][j - 1].first) count[i][m++] = count[i][j];
          else count[i][m - 1].second += count[i][j].second;
        }
        count[i].resize(m);
      }
    }

    for (auto &&e: count[n - 1]) {
      ret -= e.second;
      ret = (ret % mod + mod) % mod;
    }
    printf("%lld\n", ret);
  }
  return 0;
}
