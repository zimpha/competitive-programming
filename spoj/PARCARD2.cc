#include <cmath>
#include <cstdio>
#include <algorithm>

using int64 = long long;

constexpr int double_prec = 53;
constexpr double pi = 3.141592653589793238462643;
constexpr double inv_log2 = 1.44269504088896340735992468 + 1e-12;
constexpr double hrr_a = 1.1143183348516376904 + 1e-12; // 44*pi^2/(225*sqrt(3))
constexpr double hrr_b = 0.0592384391754448833 + 1e-12; // pi*sqrt(2)/75
constexpr double hrr_c = 2.5650996603237281911 + 1e-12; // pi*sqrt(2/3)
constexpr double hrr_d = 1.2424533248940001551 + 1e-12; // log(2) + log(3)/2

constexpr int64 lookup[128] = {
  1, 1, 2, 3, 5, 7, 11, 15, 22, 30, 42, 56, 77, 101, 135, 
  176, 231, 297, 385, 490, 627, 792, 1002, 1255, 1575, 1958, 
  2436, 3010, 3718, 4565, 5604, 6842, 8349, 10143, 12310, 14883, 
  17977, 21637, 26015, 31185, 37338, 44583, 53174, 63261, 75175, 
  89134, 105558, 124754, 147273, 173525, 204226, 239943, 281589, 
  329931, 386155, 451276, 526823, 614154, 715220, 831820, 966467, 
  1121505, 1300156, 1505499, 1741630, 2012558, 2323520, 2679689, 
  3087735, 3554345, 4087968, 4697205, 5392783, 6185689, 7089500, 
  8118264, 9289091, 10619863, 12132164, 13848650, 15796476, 18004327, 
  20506255, 23338469, 26543660, 30167357, 34262962, 38887673, 
  44108109, 49995925, 56634173, 64112359, 72533807, 82010177, 
  92669720, 104651419, 118114304, 133230930, 150198136, 169229875, 
  190569292, 214481126, 241265379, 271248950, 304801365, 342325709, 
  384276336, 431149389, 483502844, 541946240, 607163746, 679903203, 
  761002156, 851376628, 952050665, 1064144451, 1188908248, 1327710076, 
  1482074143, 1653668665, 1844349560, 2056148051, 2291320912, 
  2552338241, 2841940500, 3163127352, 3519222692, 3913864295
};

void number_of_partitions(int n) {
  auto log_sinh = [](double x) {
    if (x > 4) return x;
    else return log(x) + x * x / 6;
  };

  auto remainder_bound = [&](double n, double terms) {
    return hrr_a / sqrt(terms) + hrr_b * sqrt(terms / (n - 1)) * sinh(hrr_c * sqrt(n)/terms);
  };

  auto remainder_bound_log2 = [&] (double n, double N) {
    double t1 = log(hrr_a) - 0.5 * log(N);
    double t2 = log(hrr_b) + 0.5 * (log(N) - log(n - 1)) + log_sinh(hrr_c * sqrt(n) / N);
    return (std::max(t1, t2) + 1) * inv_log2;
  };

  auto partitions_needed_terms = [&] (int n) {
    int ret = 1;
    for (; remainder_bound_log2(n, ret) > 10; ++ret);
    for (; remainder_bound(n, ret) > (n > 1500 ? 0.25 : 1); ++ret);
    return ret;
  };

  if (n < 128) {
    printf("%lld\n", lookup[n]);
    return;
  }
  int N = partitions_needed_terms(n);
  int prec = remainder_bound_log2(n, 1) + 2 * (32 - __builtin_clz(N)) + 32;
  prec = std::max(prec, double_prec);
  printf("%d\n", prec);
}

int main() {
  int n;
  scanf("%d", &n);
  number_of_partitions(n);
  return 0;
}
