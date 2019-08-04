#include <cmath>
#include <unordered_map>
#include <cstdio>
#include <cassert>
#include <vector>
#include <tuple>
#include <set>
#include <map>
#include <algorithm>

using int64 = long long;

// a + b sqrt{3}
struct Num {
  int64 a, b;
  Num(int64 a = 0, int64 b = 0): a(a), b(b) {}
  double val() const {
    return a + b * sqrt(3);
  }
  bool operator < (const Num &rhs) const {
    return val() < rhs.val();
    return a < rhs.a || (a == rhs.a && b < rhs.b);
  }
  bool operator == (const Num &rhs) const {
    return a == rhs.a && b == rhs.b;
  }

  Num operator + (const Num &rhs) const {
    return Num(a + rhs.a, b + rhs.b);
  }
  Num operator - (const Num &rhs) const {
    return Num(a - rhs.a, b - rhs.b);
  }
  Num operator * (const Num &rhs) const {
    return Num(a * rhs.a + 3 * b * rhs.b, a * rhs.b + b * rhs.a);
  }
};

struct Network {
  std::vector<Num> x, y;
  std::set<std::pair<int, int>> edges;
  std::map<std::pair<Num, Num>, int> idx;
  int n;

  void build() {
    std::vector<int> deg(n);
    for (auto &e: edges) {
      deg[e.first]++;
      deg[e.second]++;
    }
    std::vector<std::vector<int>> go(n);
    for (auto &e: edges) {
      if (deg[e.first] < deg[e.second]) go[e.first].push_back(e.second);
      else go[e.second].push_back(e.first);
    }
    std::vector<int> mark(n), visited(n);
    x.resize(n); y.resize(n);
    std::map<int, std::pair<int, int>> next;
    std::vector<int> queue;
    bool first = true;
    int cnt = 0;
    auto add = [&](int x, int y) {
      auto it = next.find(x);
      if (it == next.end()) {
        next[x] = {y, -1};
      } else {
        it->second.second = y;
      }
    };

    auto enqueue = [&] (int a, int b) {
      if (a < b) queue.push_back(a * n + b);
      else queue.push_back(b * n + a);
    };

    for (int a = 0; a < n; ++a) {
      for (auto &b: go[a]) mark[b] = 1;
      for (auto &b: go[a]) for (auto &c: go[b]) {
        ++cnt;
        if (mark[c]) {
          if (first) {
            x[a] = Num(0, 0), y[a] = Num(0, 0);
            x[b] = Num(128, 0), y[b] = Num(0, 0);
            x[c] = Num(64, 0), y[c] = Num(0, 64);
            visited[a] = visited[b] = visited[c] = 1;
            enqueue(a, b);
            enqueue(a, c);
            enqueue(b, c);
            first = false;
          }
          if (a < b) add(a * n + b, c);
          else add(b * n + a, c);
          if (a < c) add(a * n + c, b);
          else add(c * n + a, b);
          if (b < c) add(b * n + c, a);
          else add(c * n + b, a);
        }
      }
      for (auto &b: go[a]) mark[b] = 0;
    }
    for (size_t i = 0; i < queue.size(); ++i) {
      int a = queue[i] / n, b = queue[i] % n;
      assert(visited[a] && visited[b]);
      assert(a < b);
      auto nx = next[queue[i]];
      if (nx.second != -1) {
        int c1 = nx.first, c2 = nx.second;
        if (visited[c2]) std::swap(c1, c2);
        assert(!visited[c2]);
        assert(visited[c1]);
        x[c2] = x[a] + x[b] - x[c1];
        y[c2] = y[a] + y[b] - y[c1];
        enqueue(b, c2); enqueue(a, c2);
        visited[c2] = 1;
      }
    }
    for (int i = 0; i < n; ++i) {
      idx[{x[i], y[i]}] = i;
    }
  }

  void rotate() {
    for (int i = 0; i < n; ++i) {
      Num xx = x[i] - y[i] * Num(0, 1);
      Num yy = x[i] * Num(0, 1) + y[i];
      assert(xx.a % 2 == 0 && xx.b % 2 == 0);
      assert(yy.a % 2 == 0 && yy.b % 2 == 0);
      x[i].a = xx.a / 2, x[i].b = xx.b / 2;
      y[i].a = yy.a / 2, y[i].b = yy.b / 2;
    }
  }

  void flip() {
    for (int i = 0; i < n; ++i) {
      x[i].a = -x[i].a;
      x[i].b = -x[i].b;
    }
  }
};

Network build() {
  Network net;
  scanf("%d", &net.n);
  for (int i = 0; i < 2 * net.n - 3; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    if (a > b) std::swap(a, b);
    net.edges.emplace(a - 1, b - 1);
  }
  net.build();
  return net;
}

bool check(const Network &a, const Network &b) {
  int n = a.n;
  int pa = -1, pb = -1;
  for (int i = 0; i < n; ++i) {
    if (pa == -1 || (a.x[i] < a.x[pa] || (a.x[i] == a.x[pa] && a.y[i] < a.y[pa]))) pa = i;
  }
  for (int i = 0; i < n; ++i) {
    if (pb == -1 || (b.x[i] < b.x[pb] || (b.x[i] == b.x[pb] && b.y[i] < b.y[pb]))) pb = i;
  }
  auto dx = b.x[pb] - a.x[pa];
  auto dy = b.y[pb] - a.y[pa];
  std::vector<int> map(n);
  for (int i = 0; i < n; ++i) {
    auto x = b.x[i] - dx;
    auto y = b.y[i] - dy;
    if (i == pb) assert(x == a.x[pa] && y == a.y[pa]);
    auto it = a.idx.find({x, y});
    if (it == a.idx.end()) return false;
    map[i] = it->second;
  }
  return true;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    auto net1 = build();
    auto net2 = build();
    if (net1.n != net2.n) {
      puts("NIE");
      continue;
    }
    bool find = false;
    for (int e = 0; e < 2 && !find; ++e) {
      for (int i = 0; i < 6 && !find; ++i) {
        net1.rotate();
        if (check(net2, net1)) find = true;
      }
      net1.flip();
    }
    puts(find ? "TAK" : "NIE");
  }
  return 0;
}
