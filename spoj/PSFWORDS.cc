#include <cstdio>
#include <numeric>
#include <map>
#include <vector>

using uint = unsigned int;

const int N = 101;
int n, m;

uint pm[N], sm[N];

int dsu[N + 1], rank[N + 1];
std::vector<std::pair<int&, int>> history;

int find(int x) {
  while (x != dsu[x]) x = dsu[x];
  return x;
}

void change(int &a, int b) {
  history.emplace_back(a, a);
  a = b;
}

void rollback(size_t h) {
  while (history.size() > h) {
    history.back().first = history.back().second;
    history.pop_back();
  }
}

void merge(int a,int b) {
  a = find(a);
  b = find(b);
  if (a == b) return;
  if (rank[a] < rank[b]) {
    std::swap(a, b);
  }
  if (rank[a] == rank[b]) {
    change(rank[a], rank[a] + 1);
  }
  change(dsu[b], a);
}

void combine(int p) {
  for (int i = 0; i < p; ++ i) {
    merge(i, i + p);
  }
}

std::map<std::vector<int>, uint> mem;

std::vector<int> decode(int p, int &cnt) {
  std::vector<int> vec(p);
  std::vector<int> mark(p, -1);
  for (int i = 0; i < p; ++ i) {
    if (mark[find(i)] == -1) {
      mark[find(i)] = i;
      ++cnt;
    }
    vec[i] = mark[find(i)];
  }
  return vec;
}

uint search(int p) {
  int cnt = 0;
  auto vec = decode(p << 1, cnt);
  auto it = mem.find(vec);
  if (it != mem.end()) {
    return it->second;
  }
  uint ret = sm[n - p * 2] * pm[cnt];
  size_t h = history.size();
  for (int i = p + 1; i * 2 <= n; ++ i) {
    combine(i);
    ret -= search(i);
    rollback(h);
  }
  return mem[vec] = ret;
}

uint work() {
  if (m == 1) return n == 1;
  pm[0] = sm[0] = 1;
  for (int i = 1; i <= n; ++ i) {
    pm[i] = pm[i - 1] * m;
    sm[i] = sm[i - 1] + pm[i];
  }
  for (int i = 0; i < n; ++i) {
    dsu[i] = i;
    rank[i] = 0;
  }
  return search(0) - 1;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    mem.clear();
    scanf("%d%d",&n,&m);
    printf("%u\n",work());
  }
  return 0;
}
