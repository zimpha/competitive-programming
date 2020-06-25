#include <cmath>
#include <cstdio>
#include <vector>
#include <cassert>
#include <algorithm>

const int N = 2000 + 10;

std::vector<int> edges[N];

class Hopcroft {
public:
  int cnt,pos[N],neg[N]; // pos[]为左侧点所匹配到的右侧点编号
  // neg[]反之，没有匹配到对应的点则为-1
  // 传入左侧点个数n和左侧点至右侧点的边表e[]，返回匹配点对的数量cnt
  int gao(int n, const std::vector<int> e[]){ // 复杂度O(sqrt(n)*m)
    std::fill(pos,pos+n,-1);
    std::fill(neg,neg+n,-1);
    for(int x=cnt=0,y;x<n;x++){
      for(size_t i=0;i<e[x].size();i++){
        if(~neg[y=e[x][i]]) continue;
        pos[neg[y]=x]=y;
        cnt++; break;
      }
    }
    while(true){
      int push=0,pop=0,ok=0;
      std::fill(lx,lx+n,-1);
      std::fill(ly,ly+n,-1);
      for(int x=0;x<n;x++) if(pos[x]<0) lx[q[push++]=x]=0;
      while(push!=pop){
        int x=q[pop++],y;
        for(size_t i=0;i<e[x].size();i++){
          if(~ly[y=e[x][i]]) continue;
          ly[y]=1+lx[x];
          if(~neg[y] && ~lx[neg[y]]) continue;
          if(~neg[y]) lx[q[push++]=neg[y]]=1+ly[y];
          else ok=1;
        }
      }
      if(!ok) return cnt;
      for(int x=0;x<n;x++) if(pos[x]<0 && aug(x,e)) cnt++;
    }
  }
private:
  int lx[N],ly[N],q[N];
  bool aug(int x, const std::vector<int> e[]){
    int c=lx[x]+1,y=lx[x]=-1;
    for(size_t i=0;i<e[x].size();i++) if(ly[y=e[x][i]]==c){
      ly[y]=-1;
      if(~neg[y] && !aug(neg[y],e)) continue;
      pos[neg[y]=x]=y;
      return true;
    }
    return false;
  }
} hk;


int ret[N][N];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    std::vector<std::pair<int, int>> a(k);
    for (int i = 0; i < k; ++i) {
      double x, y;
      scanf("%lf%lf", &x, &y);
      a[i] = {floor(x * 2 + 1e-5), floor(y * 2 + 1e-5)};
    }
    for (int i = 0; i < n * m; ++i) edges[i].clear();
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
      if (i % 2 != j % 2) continue;
      for (int e = 0; e < k; ++e) {
        int ii = a[e].first - i - 1, jj = a[e].second - j - 1;
        if (ii < 0 || ii >= n || jj < 0 || jj >= m) continue;
        assert(ii % 2 != jj % 2);
        edges[i * m + j].push_back(ii * m + jj);
      }
    }
    int cnt = hk.gao(n * m, edges);
    if (cnt * 2 != n * m) puts("NO");
    else {
      for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
        if (i % 2 != j % 2) continue;
        int ii = hk.pos[i * m + j] / m, jj = hk.pos[i * m + j] % m;
        for (int e = 0; e < k; ++e) {
          if (i + ii == a[e].first - 1 && j + jj == a[e].second - 1) {
            ret[i][j] = ret[ii][jj] = e + 1;
            break;
          }
        }
      }
      puts("YES");
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
          printf("%d ", ret[i][j]);
        }
        puts("");
      }
    }
  }
  return 0;
}
