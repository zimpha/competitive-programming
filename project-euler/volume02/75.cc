#include <bits/stdc++.h>
using namespace std;

const int A[3][3] = {{1,-2,2},{2,-1,2},{2,-2,3}};
const int B[3][3] = {{1,2,2},{2,1,2},{2,2,3}};
const int C[3][3] = {{-1,2,2},{-2,1,2},{-2,2,3}};

vector<int> cnt;
int L;

void dfs(int a[3]) {
  if (a[0] + a[1] + a[2] > L) return;
  int s = a[0] + a[1] + a[2];
  for (int i = s; i <= L; i += s) cnt[i] ++;
  int b[3];
  for (int i=0;i<3;++i)b[i]=A[i][0]*a[0]+A[i][1]*a[1]+A[i][2]*a[2];
  dfs(b);
  for (int i=0;i<3;++i)b[i]=B[i][0]*a[0]+B[i][1]*a[1]+B[i][2]*a[2];
  dfs(b);
  for (int i=0;i<3;++i)b[i]=C[i][0]*a[0]+C[i][1]*a[1]+C[i][2]*a[2];
  dfs(b);
}

int main() {
  L = 1500000;
  cnt.assign(L + 1, 0);
  int a[] = {3, 4, 5};
  dfs(a);
  int ret(0);
  for (int i = 1; i <= L; ++ i) ret += cnt[i] == 1;
  cout << ret << endl;
  return 0;
}
