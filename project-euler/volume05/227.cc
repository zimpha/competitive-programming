#include <bits/stdc++.h>

typedef double flt;
const int N = 100;
const flt eps= 1e-12;
bool gauss(flt a[][N],flt b[],int n){
  for(int k=0,i,j,s;k<n;++k){
    for(s=k,i=k+1;i<n;++i)
      if(fabs(a[i][k])>fabs(a[s][k]))s=i;
    if(fabs(a[s][k])<eps)return false;
    if(s!=k){
      std::swap(b[s],b[k]);
      for(i=k;i<n;++i)std::swap(a[s][i],a[k][i]);
    }
    for(j=k+1;j<n;++j){
      flt t=-a[j][k]/a[k][k];
      b[j]+=b[k]*t;
      for(i=k+1;i<n;++i)a[j][i]+=t*a[k][i];
    }
  }
  for(int i=n-1;i>=0;--i){
    b[i]/=a[i][i];
    for(int j=0;j<i;++j)b[j]-=a[j][i]*b[i];
  }
  return 1;
}

flt run(int n) {
  flt A[N][N], B[N];
  memset(A, 0, sizeof(A));
  memset(B, 0, sizeof(B));
  A[0][0] = 1;
  for (int i = 1; i <= n / 2; ++i) {
    A[i][i] += 1;
    for (int x = 1; x <= 6; ++x) {
      for (int y = 1; y <= 6; ++y) {
        int d = i;
        if (x == 1) ++d;
        else if (x == 6) --d;
        if (y == 1) --d;
        else if (y == 6) ++d;
        if (d < 0) d += n;
        d = std::min(d, n - d);
        A[i][d] -= 1.0 / 36;
        B[i] += 1.0 / 36;
      }
    }
  }
  if (!gauss(A, B, n / 2 + 1)) return -1;
  return B[n / 2];
}

int main() {
  std::cout.precision(6);
  std::cout << std::fixed << run(100) << std::endl;
  return 0;
}
