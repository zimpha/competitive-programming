#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <vector>

using int64 = long long;
const int mod = 998244353;

const int N = 36;

int64 f[2][N][N][N][N][4];
int64 g[2][N][N][N][N][4];

int64 table[4][N] = {
  {0, 0, 1, 9, 55, 290, 1418, 6629, 30091, 133806, 586054, 2537370, 10886566, 46369284, 196323476, 827082029, 474985712, 528106312, 541758386, 595828051, 59377087, 109000449, 755534195, 558578043, 332657763, 629563085, 615306569, 60402678, 105929548, 493601184, 189333986, 389953147, 797915382, 481229189, 420292720, 995685669},
  {0, 0, 0, 0, 14, 149, 1054, 6236, 33398, 167990, 809664, 3784560, 17289420, 77603161, 343494418, 505146499, 529996320, 104095918, 157010208, 882363522, 831488755, 64373852, 112711345, 506652314, 870754501, 821145751, 732198884, 233150578, 986070399, 294233090, 811118170, 134746385, 677094360, 849899135, 465153584, 953448507},
  {0, 0, 0, 0, 3, 98, 1074, 8245, 52812, 303340, 1621010, 8232983, 40276667, 191487706, 890245676, 72391037, 327327922, 491153491, 686836892, 258624519, 437178178, 365152019, 305651067, 66360168, 507909062, 381762652, 749979052, 351446733, 647281286, 461133580, 629992197, 904426876, 591298333, 918672977, 515344802, 954187223},
  {0, 0, 0, 0, 0, 21, 484, 5430, 44472, 304997, 1867456, 10573956, 56564788, 289885815, 438658583, 946463028, 822984448, 341838670, 633606596, 893811591, 27160201, 979478338, 875209020, 580102669, 528317334, 663671805, 285229136, 454142107, 887552094, 642070688, 437542901, 898440781, 100405302, 511509010, 392851051, 161580714}
};

void add(int64 &x, int64 y) {
  if ((x += y) >= mod) x -= mod;
}

int64 pow_mod(int64 a, int64 n) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

using i64 = long long;

int mod_inv(int a, int mod) {
  int b = mod, s = 1, t = 0, old_a = a;
  while (b) {
    int q = a / b;
    std::swap(a %= b, b);
    std::swap(s -= t * q, t);
  }
  if (a != 1) {
    fprintf(stderr,
        "Error: %d^{-1} mod %d does not exist.\n\n", old_a, mod);
    assert(0);
  }
  return s < 0 ? s + mod : s;
}

std::vector<int> extended(int n,
    const std::vector< std::vector<int> >& coeffs, const std::vector<int>& terms, int mod) {

  std::vector<int> ret(std::max<int>(n + 1, terms.size()));
  copy(terms.begin(), terms.end(), ret.begin());
  const int order = coeffs.size() - 1;
  const int deg = coeffs[0].size() - 1;
  assert((int) terms.size() >= order);
  for (int m = terms.size(); m <= n; ++m) {
    int s = 0;
    for (int i = 1; i <= order; ++i) {
      int k = m - i, t = ret[k];
      for (int d = 0; d <= deg; ++d) {
        s = (s + i64(t) * coeffs[i][d]) % mod;
        t = i64(t) * k % mod;
      }
    }
    int denom = 0, mpow = 1;
    for (int d = 0; d <= deg; ++d) {
      denom = (denom + i64(mpow) * coeffs[0][d]) % mod;
      mpow = i64(mpow) * m % mod;
    }
    ret[m] = i64(mod - s) * mod_inv(denom, mod) % mod;
  }
  return ret;
}

std::vector< std::vector<int> > find_recurrence_relation(
    const std::vector<int>& terms, const int deg, const int mod, bool verify=true) {

  const int n = terms.size();
  const int B = (n + 2) / (deg + 2); // number of blocks
  const int C = B * (deg + 1); // number of columns
  const int R = n - (B - 1); // number of rows
  assert(B >= 2); assert(R >= C - 1);

  auto mul = [mod] (int a, int b) { return i64(a) * b % mod; };
  auto fixed = [mod] (int a) { return (a %= mod) < 0 ? a + mod : a; };
  auto error = [] (int order, int deg) {
    fprintf(stderr,
        "Error: Could not find a recurrence relation "
        "of order <= %d and degree <= %d.\n\n",
        order, deg);
    assert(0);
  };

  std::vector< std::vector<int> > mat(R, std::vector<int>(C));
  for (int y = 0; y < R; ++y) {
    for (int b = 0; b < B; ++b) {
      for (int d = 0, v = fixed(terms[y + b]); d <= deg; ++d) {
        mat[y][b * (deg + 1) + d] = v;
        v = mul(v, y + b);
      }
    }
  }

  int rank = 0;
  for (int x = 0; x < C; ++x) {
    int pivot = -1;
    for (int y = rank; y < R; ++y) if (mat[y][x] != 0) {
      pivot = y; break;
    }
    if (pivot < 0) break;
    if (pivot != rank) swap(mat[rank], mat[pivot]);
    int inv = mod_inv(mat[rank][x], mod);
    for (int x2 = x; x2 < C; ++x2) mat[rank][x2] = mul(mat[rank][x2], inv);
    for (int y = rank + 1; y < R; ++y) if (mat[y][x]) {
      int c = mod - mat[y][x];
      for (int x2 = x; x2 < C; ++x2) {
        mat[y][x2] = (i64(mat[y][x2]) + i64(c) * mat[rank][x2]) % mod;
      }
    }
    ++rank;
  }

  if (rank == C) error(B - 1, deg);

  for (int y = rank - 1; y >= 0; --y) if (mat[y][rank]) {
    assert(mat[y][y] == 1);
    int c = mod - mat[y][rank];
    for (int y2 = 0; y2 < y; ++y2) {
      mat[y2][rank] = (mat[y2][rank] + i64(c) * mat[y2][y]) % mod;
    }
  }

  int order = rank / (deg + 1);
  std::vector< std::vector<int> > ret(order + 1, std::vector<int>(deg + 1));
  ret[0][rank % (deg + 1)] = 1;
  for (int y = rank - 1; y >= 0; --y) {
    int k = order - y / (deg + 1), d = y % (deg + 1);
    ret[k][d] = (mod - mat[y][rank]) % mod;
  }

  if (verify) {
    auto extended_terms = extended(n - 1, ret,
        std::vector<int>(terms.begin(), terms.begin() + order), mod);
    for (int i = 0; i < (int) terms.size(); ++i) {
      if (fixed(terms[i] - extended_terms[i]) != 0) error(B - 1, deg);
    }
  }

    auto verbose = [&] {
    int last = verify ? n - 1 : order + R - 1;
    fprintf(stderr,
      "[ Found a recurrence relation ]\n"
      "- order %d\n"
      "- degree %d\n"
      "- verified up to a(%d) (number of non-trivial terms: %d)\n",
      order, deg, last, (last + 1) - ((deg + 2) * (order + 1) - 2)
    );
    fprintf(stderr, "{\n");
    for (int k = 0; k <= order; ++k) {
      fprintf(stderr, "  {");
      for (int d = 0; d <= deg; ++d) {
        if (d) fprintf(stderr, ", ");
        fprintf(stderr, "%d", ret[k][d] <= mod / 2 ? ret[k][d] : ret[k][d] - mod);
      }
      fprintf(stderr, "}%s\n", k == order ? "" : ",");
    }
    fprintf(stderr, "}\n\n");
  };
  //verbose();

  return ret;
}

int main() {
  /*f[1][0][0][0][0][0] = 1;
  g[1][0][0][0][0][0] = 0;
  int now = 1, next = 0;
  for (int n = 1; n < N; ++n) {
    memset(f[next], 0, sizeof(f[next]));
    memset(g[next], 0, sizeof(g[next]));
    for (int i1 = 0; i1 <= n; ++i1) {
      for (int i2 = i1; i2 <= n; ++i2) {
        for (int i3 = i2; i3 <= n; ++i3) {
          for (int i4 = i3; i4 <= n; ++i4) {
            for (int x = 0; x <= 3; ++x) {
              auto vf = f[now][i1][i2][i3][i4][x], vg = g[now][i1][i2][i3][i4][x];
              if (!vf) continue;
              add(table[n][x], vg);
              for (int p = 0; p <= n; ++p) {
                static int u[10]; int k = 0, y = x;
                for (int i = 1; i <= 4 && i <= p; ++i) u[k++] = p + 1;
                if (i1) y += i1 <= p, u[k++] = i1 <= p ? i1 : i1 + 1;
                if (i2) y += i2 <= p, u[k++] = i2 <= p ? i2 : i2 + 1;
                if (i3) y += i3 <= p, u[k++] = i3 <= p ? i3 : i3 + 1;
                if (i4) y += i4 <= p, u[k++] = i4 <= p ? i4 : i4 + 1;
                std::sort(u, u + k);
                std::reverse(u, u + k);
                while (k < 4) u[k++] = 0;
                int j1 = u[k - 1], j2 = u[k - 2], j3 = u[k - 3], j4 = u[k - 4];
                if (y <= 3) {
                  add(f[next][j1][j2][j3][j4][y], vf);
                  add(g[next][j1][j2][j3][j4][y], (vg + (int64)vf * (n - p)) % mod);
                }
              }
            }
          }
        }
      }
    }
    std::swap(now, next);
  }*/
  int n, m;
  scanf("%d%d", &n, &m);
  if (n < N) printf("%lld\n", table[m][n]);
  else {
    std::vector<int> terms;
    int zero = 0;
    for (int i = 1; i < N; ++i) {
      if (table[m][i]) terms.push_back(table[m][i]);
      else ++zero;
    }
    auto coeffs = find_recurrence_relation(terms, 4, mod);
    auto extended_terms = extended(n, coeffs, terms, mod);
    printf("%d\n", extended_terms[n - zero - 1]);
  }
  return 0;
}
