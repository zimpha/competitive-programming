#include <cstdio>
#include <string>
#include <vector>
#include <string>

const int N = 2e6 + 10;

class IncrementalAhoCorasic {
  using iterator = std::vector<std::string>::const_iterator;
  static constexpr int SIGMA = 26;
  struct Node {
    Node *fail;
    Node *next[SIGMA];
    int sum;
    Node() : fail(NULL), next{}, sum(0) { }
  };

public:
  void init(int totalLen) {
    nodes.resize(totalLen);
    nNodes = 0;
    strings.clear();
    roots.clear();
    sizes.clear();
    que.resize(totalLen);
  }

  void insert(const std::string &str) {
    strings.emplace_back(str);
    roots.push_back(nodes.data() + nNodes);
    sizes.push_back(1);
    nNodes += (int)str.size() + 1;
    auto check = [&]() { return sizes.size() > 1 && sizes.end()[-1] == sizes.end()[-2]; };
    if(!check())
      makePMA(strings.end() - 1, strings.end(), roots.back(), que);
    while(check()) {
      int m = sizes.back();
      roots.pop_back();
      sizes.pop_back();
      sizes.back() += m;
      if(!check())
        makePMA(strings.end() - m * 2, strings.end(), roots.back(), que);
    }
  }

  int match(const std::string &str) const {
    int res = 0;
    for (const Node *t : roots) {
      res |= matchPMA(t, str);
      if (res) break;
    }
    return res;
  }

  private:
  static void makePMA(iterator begin, iterator end, Node *nodes, std::vector<Node*> &que) {
    int nNodes = 0;
    Node *root = new(&nodes[nNodes ++]) Node();
    for (auto it = begin; it != end; ++ it) {
      Node *t = root;
      for (char c : *it) {
        Node *&n = t->next[c - 'a'];
        if (n == nullptr) n = new(&nodes[nNodes ++]) Node();
        t = n;
      }
      t->sum = 1;
    }
    int qt = 0;
    for (Node *&n : root->next) {
      if (n != nullptr) {
        n->fail = root;
        que[qt++] = n;
      } else {
        n = root;
      }
    }
    for(int qh = 0; qh != qt; ++ qh) {
      Node *t = que[qh];
      int a = 0;
      for(Node *n : t->next) {
        if(n != nullptr) {
          que[qt ++] = n;
          Node *r = t->fail;
          while(r->next[a] == nullptr)
            r = r->fail;
          n->fail = r->next[a];
          n->sum += r->next[a]->sum;
        }
        ++ a;
      }
    }
  }

  static int matchPMA(const Node *t, const std::string &str) {
    int res = 0;
    for(char c : str) {
      int a = c - 'a';
      while (t->next[a] == nullptr) t = t->fail;
      t = t->next[a];
      res |= t->sum;
      if (res) break;
    }
    return res;
  }


  std::vector<Node> nodes;
  int nNodes;
  std::vector<std::string> strings;
  std::vector<Node*> roots;
  std::vector<int> sizes;
  std::vector<Node*> que;
};

int main() {
  int m;
  scanf("%d", &m);
  IncrementalAhoCorasic iac;
  iac.init(N);
  for (int i = 0; i < m; ++i) {
    int op;
    static char s[N];
    scanf("%d%s", &op, s);
    if (op == 0) iac.insert(s);
    else puts(iac.match(s) ? "YES" : "NO");
  }
  return 0;
}
