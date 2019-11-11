#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstdint>

using int64 = long long;

struct BitVector {
  using uint = uint32_t;
  std::vector<uint> blocks, ranktable;
  int len, blocks_len, count;
  BitVector(int n = 0) {init(n);}
  void set(int i) {blocks[i >> 5] |= 1 << (i & 31);}
  bool get(int i) const {return blocks[i >> 5] >> (i & 31) & 1;}
  void init(int n) {
    len = n;
    blocks_len = (len + 31) / 32 + 1;
    blocks.assign(blocks_len, 0);
  }
  void build() {
    count = 0;
    if (len == 0) return;
    ranktable.assign(blocks_len + 1, 0);
    for (int i = 0; i < blocks_len; ++i) {
      ranktable[i] = count;
      count += popcount(blocks[i]);
    }
    ranktable[blocks_len] = count;
  }
  int rank(int p) const {// number of 1s in [0, p)
    int idx = p >> 5;
    return ranktable[idx] + popcount(blocks[idx] & (1u << (p & 31)) - 1);
  }
  int rank(bool b, int p) const {return b ? rank(p) : p - rank(p);}
  int rank(bool b, int l, int r) const {return rank(b, r) - rank(b, l);}
 private:
  static inline int popcount(uint x) {
    x = x - ((x >> 1) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    return ((x + (x >> 4) & 0xF0F0F0F) * 0x1010101) >> 24;
  }
};

struct WaveletMatrix {
  using value_t = unsigned int;
  int height, len;
  value_t maxval;
  std::vector<BitVector> B;
  std::vector<int> mids;
  WaveletMatrix() {init({});}
  void init(const std::vector<value_t> &data) {
    len = data.size();
    maxval = len ? *std::max_element(data.begin(), data.end()) : 0;
    for (height = 1; maxval >> 1 >> (height - 1); ++height);
    B.assign(height, BitVector(len));
    mids.assign(height, 0);
    std::vector<value_t> now(data), next(len);
    for (int i = 0; i < height; ++i) {
      for (int j = 0; j < len; ++j) {
        mids[i] += (now[j] >> (height - 1 - i) & 1) == 0;
      }
      BitVector &bv = B[i];
      int zero = 0, one = mids[i];
      for (int j = 0; j < len; ++j) {
        bool b = now[j] >> (height - 1 - i) & 1;
        if (b) next.at(one++) = now[j], bv.set(j);
        else next.at(zero++) = now[j];
      }
      bv.build();
      next.swap(now);
    }
  }
  value_t get(int p) const {
    value_t ret = 0;
    for (int i = 0; i < height; ++i) {
      const BitVector &bv = B[i];
      bool dir = bv.get(p);
      ret = ret << 1 | dir;
      p = bv.rank(dir, p);
      if (dir) p += mids[i];
    }
    return ret;
  }
  // k-th element in position [left, right)
  value_t quantile(int left, int right, int k) const {
    if(k < 0 || right - left <= k) { return -1; }
    value_t val = 0;
    for(int i = 0; i < height; i ++) {
      const BitVector &bv = B[i];
      int count = bv.rank(true, left, right);
      bool dir = k < count;
      val = val << 1 | (dir ? 1 : 0);
      if(!dir) k -= count;
      left = bv.rank(dir, left), right = bv.rank(dir, right);
      if(dir) left += mids[i], right += mids[i];
    }
    return val;
  }
  // number of element less/greater than val in position [left, right), return the rank?
  int rank_all(value_t val, int left, int right, int &res_lt, int &res_gt) const {
    if(val > maxval) {
      res_lt = right - left;
      res_gt = 0;
      return 0;
    }
    res_lt = res_gt = 0;
    for(int i = 0; i < height; ++i) {
      const BitVector &bv = B[i];
      bool dir = val >> (height - i - 1) & 1;
      int leftcount = bv.rank(dir, left), rightcount = bv.rank(dir, right);
      (dir ? res_lt : res_gt) += (right - left) - (rightcount - leftcount);
      left = leftcount, right = rightcount;
      if(dir) left += mids[i], right += mids[i];
    }
    return right - left;
  }
} wm;

const int N = 4000 + 10;

char grid[N][N];
short up[N][N], down[N][N];
short bound[N];
WaveletMatrix::value_t a[N];
int b[N];

int main() {
  int n, m, L, p;
  scanf("%d%d%d%d", &n, &m, &L, &p);
  for (int i = 0; i < p; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    --x, --y;
    grid[x][y] = 1;
  }
  memset(bound, 0, sizeof(bound));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (grid[i][j]) bound[j] = 0;
      else bound[j]++;
      up[i][j] = bound[j];
    }
  }
  memset(bound, 0, sizeof(bound));
  for (int i = n - 1; i >= 0; --i) {
    for (int j = 0; j < m; ++j) {
      if (grid[i][j]) bound[j] = 0;
      else bound[j]++;
      down[i][j] = bound[j];
    }
  }
  memset(bound, 0, sizeof(bound));
  for (int j = 0; j < m; ++j) {
    for (int i = 0; i < n; ++i) {
      if (grid[i][j]) bound[i] = 0;
      else bound[i]++;
      up[i][j] = std::min(up[i][j], bound[i]);
    }
  }
  memset(bound, 0, sizeof(bound));
  for (int j = m - 1; j >= 0; --j) {
    for (int i = 0; i < n; ++i) {
      if (grid[i][j]) bound[i] = 0;
      else bound[i]++;
      down[i][j] = std::min(down[i][j], bound[i]);
    }
  }
  int64 ret = 0;
  for (int d = n - 1; d >= -(m - 1); --d) {
    int s = 0;
    for (int i = 0; i < n; ++i) {
      int j = i - d;
      if (j >= 0 && j < m) {
        a[s] = down[i][j] + s;
        b[s++] = up[i][j];
      }
    }
    if (s <= 2) continue;
    wm.init({a, a + s});
    for (int i = 0; i < s; ++i) {
      int l = std::max(0, i + 1 - b[i]), r = std::min(i - (L - 1), s - 1);
      if (l > r) continue;
      int lt = 0, gt = 0;
      wm.rank_all(i, l, r + 1, lt, gt);
      ret += gt;
    }
  }
  printf("%lld\n", ret);
  return 0;
}
