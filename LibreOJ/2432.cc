#include <vector>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <cstdint>
#include <algorithm>

struct FastIO {
  static const int S = 655360;
  char wbuf[S];
  char buf[S];
  int wpos;
  int pos, len;
  bool eof;
  FILE *in;
  FastIO(FILE *_in = stdin) {
    in = _in;
    pos = len = 0;
    wpos = 0;
    eof = false;
  }
  void flush() {
    if (wpos) fwrite(wbuf, 1, wpos, stdout);
    wpos = 0;
  }
  ~FastIO() {
    if (wpos) flush();
  }
  void wchar(char c) {
    if (wpos == S) flush();
    wbuf[wpos++] = c;
  }
  void wuint(unsigned x) {
    static char s[20];
    int m = 0;
    do {
      s[m++] = x % 10 + '0';
      x /= 10;
    } while (x);
    for (int i = m - 1; i >= 0; --i) wchar(s[i]);
  }
  inline int nextChar() {
    if (pos == len)
      pos = 0, len = fread(buf, 1, S, in);
    if (pos == len) {eof = true; return -1;}
    return buf[pos++];
  }
  inline int nextUInt() {
    int c = nextChar(), x = 0;
    while (c <= 32) c = nextChar();
    for (;'0' <= c && c <= '9'; c = nextChar()) x = x * 10 + c - '0';
    return x;
  }
  inline int nextInt() {
    int s = 1, c = nextChar(), x = 0;
    while (c <= 32) c = nextChar();
    if (c == '-') s = -1, c = nextChar();
    for (; '0' <= c && c <= '9'; c = nextChar()) x = x * 10 + c - '0';
    return x * s;
  }
  inline void nextString(char *s) {
    int c = nextChar();
    while (c <= 32) c = nextChar();
    for(; c > 32; c = nextChar()) *s++ = c;
    *s = 0;
  }
} io;

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
    mids.resize(height);
    std::vector<value_t> now(data), next(len);
    for (int i = 0; i < height; ++i) {
      for (int j = 0; j < len; ++j) {
        mids[i] += (now[j] >> (height - 1 - i) & 1) == 0;
      }
      BitVector &bv = B[i];
      int zero = 0, one = mids[i];
      for (int j = 0; j < len; ++j) {
        bool b = now[j] >> (height - 1 - i) & 1;
        if (b) next[one++] = now[j], bv.set(j);
        else next[zero++] = now[j];
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
};

int main() {
  srand(time(NULL));
  int n = io.nextUInt();
  int m = io.nextUInt();
  std::vector<WaveletMatrix::value_t> a(n);
  for (int i = 0; i < n; ++i) a[i] = io.nextUInt();
  auto b = a;
  std::sort(b.begin(), b.end());
  b.erase(std::unique(b.begin(), b.end()), b.end());
  for (int i = 0; i < n; ++i) {
    a[i] = std::lower_bound(b.begin(), b.end(), a[i]) - b.begin();
  }
  WaveletMatrix wm;
  wm.init(a);
  for (int i = 0; i < m; ++i) {
    int l = io.nextUInt();
    int r = io.nextUInt();
    int d = r - l + 1;
    int v = wm.quantile(l - 1, r, d / 2);
    int lt, gt;
    wm.rank_all(v, l - 1, r, lt, gt);
    int eq = d - lt - gt;
    if (eq * 2 > d) io.wuint(b[v]);
    else io.wchar('0');
    io.wchar('\n');
  }
  return 0;
}
