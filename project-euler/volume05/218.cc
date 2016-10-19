#include <bits/stdc++.h>

using LL = long long;

const int A[3][3] = {{1,-2,2},{2,-1,2},{2,-2,3}};
const int B[3][3] = {{1,2,2},{2,1,2},{2,2,3}};
const int C[3][3] = {{-1,2,2},{-2,1,2},{-2,2,3}};

int dfs(int a[3]) {
  int b[3];
  int u = a[0], v = a[1], t = a[2];
  if (t > 1e8) return 0;
  int ret = 0;
  if (u < v) std::swap(u, v);
  if ((u ^ v) & 1) {
    ret = 1;
    LL x = 1ll * u * v;
    LL y = 1ll * u * u - 1ll * v * v;
    if ((x % 84) * (y % 84) % 84 == 0) {
      ret = 0;
    }
  }
  for (int i=0;i<3;++i)b[i]=A[i][0]*a[0]+A[i][1]*a[1]+A[i][2]*a[2];
  ret += dfs(b);
  for (int i=0;i<3;++i)b[i]=B[i][0]*a[0]+B[i][1]*a[1]+B[i][2]*a[2];
  ret += dfs(b);
  for (int i=0;i<3;++i)b[i]=C[i][0]*a[0]+C[i][1]*a[1]+C[i][2]*a[2];
  ret += dfs(b);
  return ret;
}

int main() {
  int a[] = {3, 4, 5};
  std::cout << dfs(a) << std::endl;
  return 0;
}
