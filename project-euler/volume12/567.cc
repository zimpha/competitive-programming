#include <bits/stdc++.h>

//http://math.stackexchange.com/questions/627432/sum-of-reciprocals-of-binomial-coefficients-sum-limits-k-0n-1-dfrac1
double run(int n) {
  // JA(n) = \sum_{k=1}^{n}\frac{\binom{n}{k}}{k2^n}=JA(n-1)/2+1/n-1/(n2^n)
  // JB(n) = \sum_{k=1}^{n}\frac{1}{k\binom{n}{k}}=JB(n-1)/2+1/n
  double ja = 0.5, jb = 1.0, pw = 0.5, ret = 0;
  for (int i = 1; i <= n; ++i) {
    ret += ja + jb;
    pw *= 0.5;
    ja = 0.5 * ja + 1.0 / (i + 1) - 1.0 / (i + 1) * pw;
    jb = 0.5 * jb + 1.0 / (i + 1);
  }
  return ret;
}

int main() {
  std::cout.precision(20);
  std::cout << run(6) << std::endl;
  std::cout << run(123456789) << std::endl;
  return 0;
}

