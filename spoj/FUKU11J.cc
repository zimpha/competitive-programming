#include <algorithm>
#include <queue>
#include <utility>
#include <vector>
#include <iostream>

typedef long long ll;
typedef std::pair<int, int> PI;

const int MAX = 55;
const int INF = 1e9;
int T[MAX][MAX][1 << 10];

struct State {
  int x;
  int y;
  int mask;
  State(int x_, int y_, int mask_) : x(x_), y(y_), mask(mask_) {}
  friend bool operator<(const State &p, const State &q){
    return p.x != q.x ? p.x < q.y : p.y != q.y ? p.y < q.y : p.mask < q.mask;
  }

  friend bool operator>(const State &p, const State &q){
    return q < p;
  }
};

void solve(int N, int M){
  std::vector<int> D(N), E(N), I(N);
  for (int i = 0; i < N - 2; ++i) {
    std::cin >> D[i + 1] >> E[i + 1];
  }
  E[N - 1] = 1000;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < i; ++j) {
      if (E[j] == E[i]) I[i]++;
    }
  }
  std::vector<std::vector<int>> G(N, std::vector<int>(N, -1));
  std::vector<std::vector<int>> H(N, std::vector<int>(N, -1));
  for (int i = 0; i < M; ++i) {
    int a, b, c;
    std::cin >> a >> b >> c; a--, b--;
    if (E[a] >= E[b]) G[b][a] = c;
    if (E[a] <= E[b]) H[a][b] = c;
  }
  for (int i = 0; i < MAX; ++i) {
    for (int j = 0; j < MAX; ++j) {
      std::fill(T[i][j], T[i][j] + (1 << 10), INF);
    }
  }
  
  T[0][0][1] = 0;
  std::priority_queue<std::pair<int, State>> que;
  que.emplace(0, State(0, 0, 1));
  while (!que.empty()){
    int x = que.top().second.x;
    int y = que.top().second.y;
    int mask = que.top().second.mask;
    int cost = -que.top().first;
    que.pop();
    if (cost > T[x][y][mask]) continue;
    if (x == N - 1 && y == N - 1){
      std::cout << cost << std::endl;
      return ;
    }

    if (E[x] <= E[y]){
      for (int z = 0; z < N; ++z) {
        if (H[x][z] != -1){
          int next_cost = cost, next_mask = mask;
          if (E[z] < E[y]){
            next_cost = cost + H[x][z] + D[z];
            next_mask = mask;
          } else if (E[z] > E[y]){
            next_cost = cost + H[x][z] + D[z];
            next_mask = 1 << I[z];
          } else {
            next_cost = cost + H[x][z] + ((mask & (1 << I[z])) ? 0 : D[z]);
            next_mask = mask | (1 << I[z]);
          }

          if (T[z][y][next_mask] > next_cost){
            T[z][y][next_mask] = next_cost;
            que.emplace(-next_cost, State(z, y, next_mask));
          }
        }
      }
    }

    if (E[x] >= E[y]){
      for (int z = 0; z < N; ++z) {
        if (G[y][z] != -1){
          int next_cost = cost, next_mask = mask;
          if (E[z] < E[x]){
            next_cost = cost + G[y][z] + D[z];
            next_mask = mask;
          } else if (E[z] > E[x]){
            next_cost = cost + G[y][z] + D[z];
            next_mask = 1 << I[z];
          } else {
            next_cost = cost + G[y][z] + ((mask & (1 << I[z])) ? 0 : D[z]);
            next_mask = mask | (1 << I[z]);
          }

          if (T[x][z][next_mask] > next_cost){
            T[x][z][next_mask] = next_cost;
            que.emplace(-next_cost, State(x, z, next_mask));
          }
        }
      }
    }
  }
  std::cout << -1 << std::endl;
}

int main(){
  int N, M;
  while (std::cin >> N >> M && N){
    solve(N, M);
  }
  return 0;
}
