#include <cstdio>
#include <cstring>
#include <functional>
#include <numeric>
#include <algorithm>

const int N = 200000 + 10;

using pii = std::pair<int, int>;

struct Max {
  int operator() (int a, int b) const {
    return std::max(a, b);
  }
};

struct Min {
  int operator() (int a, int b) const {
    return std::min(a, b);
  }
};

struct RMQ {
  int mx[N][20], lg[N];
  std::function<int(int, int)> fun;
  void init(int n, int a[], std::function<int(int, int)> f) {
    fun = f;
    for (int i = -(lg[0] = -1); i < n; ++ i) lg[i] = lg[i >> 1] + 1;
    for (int i = 0; i < n; ++ i) mx[i][0] = a[i];
    for (int i, j = 1; (1 << j) <= n; ++ j) {
      for (i = 0; i + (1 << j) <= n; ++ i) {
        mx[i][j] = fun(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
      }
    }
  }
  int ask(int a, int b) {// a <= b
    int k = lg[b - a + 1];
    return fun(mx[a][k], mx[b - (1 << k) + 1][k]);
  }
};

char s[N];
int u[N];
int ret, len;
pii B, D;

namespace sa {
  int cnt[N], tr[2][N], ts[N];
  int sa[N], rk[N], ht[N], n;
  RMQ saRMQ, htRMQ;

  void construct(char *s, int n, int m=256) {
    int i,j,k,*x=tr[0],*y=tr[1];
    memset(cnt,0,sizeof(cnt[0])*m); for (i=0;i<n;++i) cnt[s[i]]++;
    std::partial_sum(cnt,cnt+m,cnt); for (i=0;i<n;++i) rk[i]=cnt[s[i]]-1;
    for (k=1;k<=n;k<<=1) {
      for (i=0;i<n;++i) x[i]=rk[i],y[i]=i+k<n?rk[i+k]+1:0;
      std::fill(cnt,cnt+n+1,0); for (i=0;i<n;++i) cnt[y[i]]++;
      std::partial_sum(cnt,cnt+n+1,cnt); for (i=n-1;i>=0;--i) ts[--cnt[y[i]]]=i;
      std::fill(cnt,cnt+n+1,0); for (i=0;i<n;++i) cnt[x[i]]++;
      std::partial_sum(cnt,cnt+n+1,cnt); for (i=n-1;i>=0;--i) sa[--cnt[x[ts[i]]]]=ts[i];
      for (i=rk[sa[0]]=0;i+1<n;++i) {
        rk[sa[i+1]]=rk[sa[i]]+(x[sa[i]]!=x[sa[i+1]]||y[sa[i]]!=y[sa[i+1]]);
      }
    }
  }
  void get_height(char *s, int n) {
    for (int i=0,l=0,j;i<n;++i) {
      if (!rk[i]) continue;
      for (j=sa[rk[i]-1];i+l<n&&j+l<n&&s[i+l]==s[j+l];) l++;
      ht[rk[i]]=l; if (l) l--;
    }
  }
  void manacher(char *s, int *u, int n) {// O(N)
    n<<=1; memset(u,0,sizeof(u[0])*n);
    for (int i=0,j=0,k;i<n;i+=k,j=std::max(j-k,0)) {
      while (i>=j&&i+j+1<n&&s[(i-j)>>1]==s[(i+j+1)>>1]) ++j;
      for (u[i]=j,k=1;i>=k&&u[i]>=k&&u[i-k]!=u[i]-k;++k) {
        u[i+k]=std::min(u[i-k],u[i]-k);
      }
    }
  }
  pii get(int p, int lim) {//[lim, n)
    pii s(0, -1), t(0, -1); p = rk[p];
    int left = 0, right = p - 1;
    while (left < right) {
      int mid = (left + right + 1) >> 1;
      if (saRMQ.ask(mid, p) >= lim) left = mid;
      else right = mid - 1;
    }
    if (saRMQ.ask(left, p) >= lim) s = pii(htRMQ.ask(left + 1, p), sa[left]);
    left = p + 1, right = n - 1;
    while (left < right) {
      int mid = (left + right) >> 1;
      if (saRMQ.ask(p, mid) >= lim) right = mid;
      else left = mid + 1;
    }
    if (saRMQ.ask(p, left) >= lim) t = pii(htRMQ.ask(p + 1, left), sa[left]);
    return max(s, t);
  }

  void solve(char *s, int op = 0) {
    n = strlen(s);
    manacher(s, u, len);
    construct(s, n); get_height(s, n);
    htRMQ.init(n, ht, Min());
    saRMQ.init(n, sa, Max());
    for (int i = 0; i < len * 2; ++ i) if (u[i]) {
      int d = u[i] / 2, l, r, s, t;
      if (i & 1) {// even length
        l = i / 2 - d + 1, r = i / 2 + d;
      }
      else {// odd length
        l = i / 2 - d, r = i / 2 + d;
      }
      pii tp = get(r + 1, n - l);
      if (tp.first == 0) s = t = -1;
      else {
        s = n - tp.first - tp.second;
        t = n - tp.second - 1;
        r += tp.first;
      }
      if (tp.first * 2 + u[i] > ret) {
        ret = tp.first * 2 + u[i];
        if (op && s != -1) s = len - s - 1, t = len - t - 1;
        if (op) l = len - l - 1, r = len - r - 1;
        if (op) std::swap(s, r), std::swap(t, l);
        B = pii(s, t); D = pii(l, r);
      }
    }
  }
}

int main() {
  scanf("%s", s); len = strlen(s);
  s[len] = '$';
  for (int i = 0; i < len; ++ i) s[i + 1 + len] = s[len - i - 1];
  sa::solve(s);
  std::reverse(s, s + len);
  for (int i = 0; i < len; ++ i) s[i + 1 + len] = s[len - i - 1];
  sa::solve(s, 1);
  printf("%d\n", ret);
  if (B.first != -1) B.first ++, B.second ++;
  if (D.first != -1) D.first ++, D.second ++;
  printf("%d %d\n", B.first, B.second);
  printf("%d %d\n", D.first, D.second);
  return 0;
}
