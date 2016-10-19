#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int A[3][3] = {{1,-2,2},{2,-1,2},{2,-2,3}};
const int B[3][3] = {{1,2,2},{2,1,2},{2,2,3}};
const int C[3][3] = {{-1,2,2},{-2,1,2},{-2,2,3}};
//传入{3,4,5}, 枚举所有互素的勾股数对, 改成bfs可能会快一点
LL dfs(int a[3], int n) {
  if (a[0] + a[1] + a[2] >= n) return 0;
  int b[3], d = abs(a[0] - a[1]);
  LL ret = 0;
  if (a[2] % d == 0) ret = (n - 1) / (a[0] + a[1] + a[2]);
  for (int i=0;i<3;++i)b[i]=A[i][0]*a[0]+A[i][1]*a[1]+A[i][2]*a[2];
  ret += dfs(b, n);
  for (int i=0;i<3;++i)b[i]=B[i][0]*a[0]+B[i][1]*a[1]+B[i][2]*a[2];
  ret += dfs(b, n);
  for (int i=0;i<3;++i)b[i]=C[i][0]*a[0]+C[i][1]*a[1]+C[i][2]*a[2];
  ret += dfs(b, n);
  return ret;
}

int main() {
  int st[] = {3, 4, 5};
  cout << dfs(st, 100000000) << endl;
  return 0;
}
