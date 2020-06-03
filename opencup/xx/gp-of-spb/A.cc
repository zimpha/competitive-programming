#include <cstdio>
#include <mod>

using int64 = long long;

int64 pow_mod(int64 a, int64 n, int64 mod) {
  int64 r = 1;
}

std::vector<int64> interpolation(const int64 x[], const int64 y[], int n, int mod){
  std::vector<int64> u(y, y + n), ret(n), sum(n);
  ret[0] = u[0], sum[0] = 1;
  for (int i = 1; i < n; ++i) {
    for (int j = n - 1; j >= i; --j) {
      u[j] = (u[j] - u[j - 1]) / (x[j] - x[j - i]);
    }
    for (int j = i; j; --j) {
      sum[j] = -sum[j] * x[i - 1] + sum[j - 1];
      ret[j] += sum[j] * u[i];
    }
    sum[0] = -sum[0] * x[i - 1];
    ret[0] += sum[0] * u[i];
  }
  return ret;
}

int main() {
  int mod;
  scanf("%d", &mod);
  return 0;
}
