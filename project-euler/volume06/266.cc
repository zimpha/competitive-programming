#include <bits/stdc++.h>

using LL = long long;
using flt = double;

const int p[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181};
const LL M = 10000000000000000ll;

LL run() {
  const int nl = 21, nr = 21;
  flt total = 0;
  static std::pair<flt, LL> val[1 << nl];
  for (int i = 0; i < 42; ++i) total += log(p[i]);
  total *= 0.5;
  for (int msk = 0; msk < (1 << nl); ++msk) {
    flt sum = 0;
    LL prod = 1;
    for (int i = 0; i < nl; ++i) {
      if (msk >> i & 1) {
        sum += log(p[i]);
        prod = prod * p[i] % M;
      }
    }
    val[msk] = {sum, prod};
  }
  std::sort(val, val + (1 << nl));
  flt now = 0;
  LL ret = 1;
  for (int msk = 0; msk < (1 << nr); ++msk) {
    flt sum = 0;
    LL prod = 1;
    for (int i = 0; i < nr; ++i) {
      if (msk >> i & 1) {
        sum += log(p[i + nl]);
        prod = prod * p[i + nl] % M;
      }
    }
    int it = upper_bound(val, val + (1 << nl), std::make_pair(total - sum, 0ll)) - val - 1;
    if (it >= 0 && sum + val[it].first > now) {
      now = sum + val[it].first;
      ret = (__int128)prod * val[it].second % M;
    }
  }
  return ret;
}

int main() {
  std::cout << run() << std::endl;
  return 0;
}

