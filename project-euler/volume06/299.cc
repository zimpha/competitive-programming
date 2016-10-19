#include <bits/stdc++.h>

using LL = long long;

const int A[3][3] = {{1,-2,2},{2,-1,2},{2,-2,3}};
const int B[3][3] = {{1,2,2},{2,1,2},{2,2,3}};
const int C[3][3] = {{-1,2,2},{-2,1,2},{-2,2,3}};

int dfs(std::vector<int> a, int upp) {
  std::vector<int> b(3);
  if (a[0] + a[1] > upp) return 0;
  int ret = upp / (a[0] + a[1]);
  for (int i=0;i<3;++i)b[i]=A[i][0]*a[0]+A[i][1]*a[1]+A[i][2]*a[2];
  ret += dfs(b, upp);
  for (int i=0;i<3;++i)b[i]=B[i][0]*a[0]+B[i][1]*a[1]+B[i][2]*a[2];
  ret += dfs(b, upp);
  for (int i=0;i<3;++i)b[i]=C[i][0]*a[0]+C[i][1]*a[1]+C[i][2]*a[2];
  ret += dfs(b, upp);
  return ret;
}

LL run(int upp) {
  // AC \not \parallel BD, P is the intersection of three angular bisectors
  // suppose P is (x, x), the distance to BD is equal to x
  // x = |dx + bx - bd| / sqrt(b^2 + d^2) => x^2(b^2+d^2) = (dx+bx-bd)^2
  LL ret = dfs({3, 4, 5}, upp - 1) * 2;
  // AC \parallel BD, 
  for (int n = 1; n < upp; n += 2) {
    for (int m = 1; m < upp; ++m) {
      if (std::__gcd(n, m) != 1) continue;
      LL bc = 2ll * n * m, c = 1ll * n * n + 2ll * m * m;
      if ((bc + c) * 2 > upp) break;
      ret += (upp - 1) / ((bc + c) * 2);
    }
  }
  return ret;
}

int main() {
  std::cout << run(100) << std::endl;
  std::cout << run(100000) << std::endl;
  std::cout << run(100000000) << std::endl;
  return 0;
}
