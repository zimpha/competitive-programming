#include <cstdio>
#include <cstring>
#include <vector>
#include <map>

using int64 = long long;

const int N = 2e6 + 10, M = 22, mod = 1e9 + 7;

std::vector<bool> tao[2][M];
std::vector<bool> taop[2][M];
char s[N];
std::map<int64, int> cnt[64];
int64 n;

int64 pow_mod(int64 a, int64 n) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

std::vector<bool> operator + (const std::vector<bool> &a, const std::vector<bool> &b) {
  std::vector<bool> c(a.size() + b.size());
  for (size_t i = 0; i < a.size(); ++i) c[i] = a[i];
  for (size_t i = 0; i < b.size(); ++i) c[i + a.size()] = b[i];
  return c;
}

void slow() {
  for (int i = 0; i < (1 << n); ++i) cnt[i].clear();
  for (int i = 0; i < (1 << n); ++i) {
    int64 s = 0;
    for (int j = i; j < (1 << n); ++j) {
      s = s * 2 + __builtin_popcount(j) % 2;
      cnt[j - i][s]++;
    }
  }
  int m = strlen(s);
  int64 w = 0;
  for (int i = 0; i < m; ++i) {
    w = w * 2 + s[i] - 'a';
  }
  int occ = cnt[m - 1][w];
  if (occ == 0) puts("-1");
  else {
    int ways = 0;
    for (int i = 0; i < (1 << n); ++i) {
      for (auto &e: cnt[i]) ways += e.second == occ;
    }
    printf("%d %d\n", occ, ways);
  }
}

struct TaoNode;
struct SigmaNode;

struct Node {
  Node(int level, bool inverted): level(level), inverted(inverted) {}
  virtual const std::vector<bool>& get_str(int e) const = 0;
  virtual Node* go(int e) = 0;
  virtual int type() const = 0;

  int length(int e) const { return get_str(e).size(); }
  Node* walk(int &e, int &pos, int c) {
    if (e == -1) e = c, pos = 1;
    else if (c != get_str(e)[pos]) return NULL;
    else ++pos;
    if (pos == length(e)) {
      auto ret = go(e);
      e = -1; pos = 0;
      return ret;
    }
    return this;
  }

  std::pair<int64, int> occ() const { // (2^x - (-1)^x) / 3 - y
    int64 x = n - level + 1, y = 0;
    if (x == 1) ++x;
    if ((n - level) % 2 == 0 && !(type() == 0 && !inverted)) y = 1;
    return {x, y};
  }

  int level;
  int inverted;
};

Node* tao_node[2][M];
Node* sigma_node[2][M];

struct TaoNode: public Node {
  TaoNode(int level, bool inverted): Node(level, inverted) {}
  const std::vector<bool>& get_str(int e) const {
    if (level == 0) return tao[e][inverted ^ e ^ 1];
    else if (level != n - 2) return tao[e][level - (inverted ^ e ^ 1)];
    else {
      if (inverted) return tao[e][level + e];
      else return taop[e][level + 1 + e];
    }
  }
  int type() const { return 0; }
  Node* go(int e);
};

struct SigmaNode: public Node {
  SigmaNode(int level, bool inverted): Node(level, inverted) {}
  const std::vector<bool>& get_str(int e) const {
    if (level != n - 2) {
      if (inverted == e) return tao[e][level - 1];
      else return taop[e][level];
    } else {
      if (inverted) {
        if (e == 0) {
          static std::vector<bool> ret[M];
          if (ret[level].empty()) ret[level] = taop[0][level] + tao[1][level + 1];
          return ret[level];
        } else return tao[1][level - 1];
      } else {
        if (e == 0) {
          static std::vector<bool> ret[M];
          if (ret[level].empty()) ret[level] = tao[0][level - 1] + tao[1][level + 1];
          return ret[level];
        } else return taop[e][level];
      }
    }
  }
  int type() const { return 1; }
  Node* go(int e);
};

Node* TaoNode::go(int e) {
  if (level == 0) {
    if (inverted) {
      if (e == 0) return tao_node[1][1];
      else return tao_node[0][2];
    } else {
      if (e == 0) return tao_node[1][2];
      else return tao_node[0][1];
    }
  } else if (level != n - 2) {
    if (inverted ^ e) return tao_node[inverted][level + 1];
    else return sigma_node[inverted][level + 1];
  } else {
    return tao_node[0][n];
  }
}

Node* SigmaNode::go(int e) {
  if (level != n - 2) return tao_node[e][level + 1];
  else return tao_node[0][n];
}

void prepare() {
  for (int i = 0; i < M; ++i) {
    tao_node[0][i] = new TaoNode(i, false);
    tao_node[1][i] = new TaoNode(i, true);
    tao[0][i].resize(1 << i); tao[1][i].resize(1 << i);
    for (int j = 0; j < (1 << i); ++j) tao[0][i][j] = __builtin_popcount(j) % 2;
    for (int j = 0; j < (1 << i); ++j) tao[1][i][j] = tao[0][i][j] ^ 1;
  }
  for (int i = 2; i < M; ++i) {
    sigma_node[0][i] = new SigmaNode(i, false);
    sigma_node[1][i] = new SigmaNode(i, true);
    int offset = 1 << (i - 2);
    taop[0][i].resize(3 * offset); taop[1][i].resize(3 * offset);
    for (int j = 0; j < offset; ++j) taop[1][i][j] = tao[1][i - 2][j];
    for (int j = 0; j < offset * 2; ++j) taop[1][i][j + offset] = tao[1][i - 1][j];
    for (int j = 0; j < offset * 3; ++j) taop[0][i][j] = taop[1][i][j] ^ 1;
  }
}

void solve(int cas) {
  Node* o = tao_node[s[0] == 'b'][0];
  int e = -1, pos = 0;
  for (int i = 1; s[i]; ++i) {
    o = o->walk(e, pos, s[i] - 'a');
    if (o == NULL) break;
  }
  if (o == NULL) {
    puts("-1");
    return;
  }
  int64 occ = 0, cnt = 0;
  Node *end = o;
  if (e != -1) end = o->go(e);
  if (end->level == 0) {
    occ = pow_mod(2, n - 1), cnt = 2;
  } else {
    auto ret = end->occ();
    occ = (pow_mod(2, ret.first) - pow_mod(mod - 1, ret.first) + mod) % mod;
    occ = occ * pow_mod(3, mod - 2) % mod;
    occ = (occ - ret.second + mod) % mod;
    for (int inverted = 0; inverted < 2; ++inverted) {
      for (int i = 0; i <= end->level && i <= n - 2; ++i) {
        Node* p = tao_node[inverted][i];
        if (i && p->occ() == ret) cnt += pow_mod(2, i - 1);
        for (int e = 0; e < 2; ++e) if (p->go(e)->occ() == ret) {
          auto s = p->get_str(e);
          cnt += (i ? pow_mod(2, i - 1) : 1) * (s.size() - 1) % mod;
        }
      }
      for (int i = 2; i <= end->level && i <= n - 2; ++i) {
        Node* p = sigma_node[inverted][i];
        if (p->occ() == ret) cnt += pow_mod(2, i - 2);
        for (int e = 0; e < 2; ++e) if (p->go(e)->occ() == ret) {
          auto s = p->get_str(e);
          cnt += pow_mod(2, i - 2) * (s.size() - 1) % mod;
        }
      }
    }
    if (end->level == n) cnt += pow_mod(2, n - 1) + pow_mod(2, n - 2);
  }
  printf("%lld %lld\n", occ, cnt % mod);
}

int main() {
  prepare();
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%lld%s", &n, s);
    if (n <= 5) slow();
    else solve(cas);
  }
  return 0;
}

