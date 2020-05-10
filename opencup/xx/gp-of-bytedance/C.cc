#include <cctype>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

const int N = (1 << 20) + 10;
const int B = 16;

using int64 = long long;

int64 table[B][B][1 << B], table_cnt[B][B];
int64 segs[B][1 << B];
int64 zero_segs[B], segs_cnt[B];
int new_mask[B][1 << B];
int cnt[N][B], last[B], occ[B];
int n, base, m;
char s[N];

int char2int(char c) {
  return isdigit(c) ? c - '0' : 10 + c - 'a';
}

void fwt(int64 *f, int n) {
  for (int i = 1; i < n; i <<= 1) {
    for (int j = 0, t = i << 1; j < n; j += t) {
      for(int k = j, b = j + i; k < b; ++k) {
        f[k + i] += f[k];
      }
    }
  }
}

int main() {
  scanf("%d%d%d%s", &n, &m, &base, s + 1);
  for (int i = 1, j; i <= n; ++i) {
    occ[char2int(s[i])]++;
    if (s[i] == '0') {
      for (j = i; j <= n && s[j] == '0'; ++j);
      zero_segs[0] += int64(j - i) * (j - i + 1) / 2;
      i = j - 1;
    } else {
      int l = i - 1, r = i + 1;
      while (l >= 1 && s[l] == '0') --l;
      while (r <= n && s[r] == '0') ++r;
      zero_segs[char2int(s[i])] += int64(i - l) * (r - i);
    }
  }
  const int mod = base - 1, ms = 1 << base;
  memset(last, -1, sizeof(last));
  std::vector<std::pair<int, int>> pos = {{0, -1}};
  pos.reserve(base);
  cnt[0][0] = 1;
  for (int i = 1, sum = 0; i <= n; ++i) {
    for (int j = 0; j < base; ++j) cnt[i][j] = cnt[i - 1][j];
    int o = char2int(s[i]);
    sum = (sum + o) % mod;
    cnt[i][sum]++;
    if (last[o] != -1) {
      pos.erase(std::find(pos.begin(), pos.end(), std::make_pair(last[o], o)));
    }
    pos.insert(pos.begin(), std::make_pair(i, o));
    last[o] = i;
    int mask = 0;
    for (size_t j = 0; j + 1 < pos.size(); ++j) {
      mask ^= 1 << pos[j].second;
      int r = pos[j].first - 1, l = pos[j + 1].first - 1, dr = sum;
      for (int k = 0; k < mod; ++k) {
        segs[dr][mask] += cnt[r][k] - (l >= 0 ? cnt[l][k] : 0);
        segs_cnt[dr] += cnt[r][k] - (l >= 0 ? cnt[l][k] : 0);
        dr -= 1; if (dr < 0) dr += mod;
      }
    }
  }

  // prepare
  for (int delta = 1; delta < mod; ++delta) {
    for (int mask = 0; mask < ms; ++mask) {
      int ret = 0;
      for (int x = 0; x < base; ++x) if (mask >> x & 1) {
        int d = (delta + x) % mod;
        ret |= 1 << d;
        if (d == 0) ret |= 1 << mod;
      }
      new_mask[delta][mask] = ret;
    }
  }
  for (int src = 0; src < mod; ++src) for (int tar = 0; tar < mod; ++tar) {
    if (src == tar) continue;
    int delta = (tar - src + mod) % mod;
    for (int mask = 0; mask < (1 << base); ++mask) if (segs[src][mask]) {
      table[src][tar][new_mask[delta][mask]] += segs[src][mask];
      table_cnt[src][tar] += segs[src][mask];
    }
    fwt(table[src][tar], ms);
  }

  // solve queries
  for (int i = 0; i < m; ++i) {
    char x[20], a[20];
    scanf("%s%s", x, a);
    int tar = char2int(x[0]), mask = 0;
    for (int j = 0; a[j]; ++j) {
      mask |= 1 << char2int(a[j]);
    }
    int64 ret = 0;
    if (tar == 0) {
      ret = zero_segs[0];
      if (mask & 1) {
        for (int i = 1; i < base; ++i) ret += zero_segs[i];
      }
    } else {
      tar %= mod;
      ret = segs_cnt[tar];
      if (tar == 0 && (~mask >> (base - 1) & 1)) ret -= zero_segs[0];
      for (int src = 0; src < mod; ++src) if (src != tar) {
        ret += table_cnt[src][tar] - table[src][tar][(~mask) & (ms - 1)];
      }
      if (tar == 0 && (mask & 1) && (~mask >> (base - 1) & 1)) {
        for (int i = 1; i < mod; ++i) if (zero_segs[i]) {
          ret -= zero_segs[i];
          if (mask >> (mod - i) & 1) ret += zero_segs[i] - occ[i];
        }
      }
    }
    printf("%lld\n", ret);
  }
  return 0;
}
