#include <cstdio>
#include <cassert>
#include <cstring>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <functional>

inline bool random(int a, int b) {return rand() % (a + b) < a;}

const int N = 200000 + 10;

int type[256];
char s[N], buffer[N];
int total = 0;

template<typename T>
std::pair<T*, T*> split(T *o, int n) {
  T *l = 0, *r = 0;
  if (!o) return {l, r};
  int ls = o->l ? o->l->sz : 0;
  if (n <= ls) {
    std::tie(l, o->l) = split(o->l, n);
    r = o;
  } else {
    std::tie(o->r, r) = split(o->r, n - ls - 1);
    l = o;
  }
  o->update();
  return {l, r};
}

template<typename T>
T* merge(T *l, T *r) {
  if (!l || !r) return l ? l : r;
  if (random(l->sz, r->sz)) {
    l->r = merge(l->r, r);
    return l->update();
  } else {
    r->l = merge(l, r->l);
    return r->update();
  }
}

void get_source() {
  char c;
  while ((c = getchar()) != '@');
  scanf("%[^@]", s);
  c = getchar();
}

struct char_t {
  char c;
  int sz;
  char_t *l, *r;
  char_t() {}
  char_t(char c): c(c), sz(1), l(0), r(0) {}
  char_t* update() {
    sz = 1;
    if (l) sz += l->sz;
    if (r) sz += r->sz;
    return this;
  }
};

struct token_t {
  char_t *root;
  bool space, newline, sub;

  token_t(): root(0), space(0), newline(0), sub(0) {}
  token_t(char_t *other): root(other), space(0), newline(0), sub(0) {}
  token_t(char *l, char *r): root(build(l, r - 1)), space(0), newline(0), sub(0) {}

  static char_t *build(char *l, char *r) {
    if (l > r) return 0;
    char *m = l + (r - l) / 2;
    char_t *o = new char_t(*m);
    o->l = build(l, m - 1);
    o->r = build(m + 1, r);
    return o->update();
  }
  int size() const {
    return root->sz;
  }
  std::pair<token_t, token_t> split(int n) {
    assert(n <= root->sz);
    char_t *a, *b;
    std::tie(a, b) = ::split(root, n);
    return {token_t(a), token_t(b)};
  }
  void append(token_t &rhs) {
    root = merge(root, rhs.root);
  }
  int first() const {
    char ret = 0;
    for (char_t *o = root; o; o = o->l) {
      ret = o->c;
    }
    return ret;
  }
  static char token[N];
  void dfs(char_t *o, int &m) const {
    if (!o) return;
    dfs(o->l, m);
    token[m++] = o->c;
    dfs(o->r, m);
  }
  std::string get(int l, int r) {// [l, r]
    char_t *a, *b, *c;
    std::tie(b, c) = ::split(root, r);
    std::tie(a, b) = ::split(b, l - 1);
    int m = 0;
    dfs(b, m);
    root = merge(a, merge(b, c));
    return std::string(token, token + m);
  }
  std::string to_str() const {
    int m = 0;
    dfs(root, m);
    return std::string(token, token + m);
  }
  bool is_semicolon() const {
    return root->sz == 1 && root->c == ';';
  }
  bool is_else() const {
    if (root->sz > 4) return false;
    return to_str() == "else";
  }
  bool is_key() const {
    if (root->sz > 5) return false;
    std::string value = to_str();
    return value == "if" || value == "for" || value == "while" || value == "do";
  }
  bool is_blank() const {
    return type[first()] == 2;
  }
};

char token_t::token[N];

std::vector<token_t> tokens;

void prepare() {
  memset(type, -1, sizeof(type));
  // Identifier
  for (int i = 0; i < 26; ++i) {
    type['a' + i] = type['A' + i] = 0;
  }
  for (int i = 0; i < 10; ++i) {
    type['0' + i] = 0;
  }
  type['['] = type[']'] = type['.'] = type['_'] = 0;
  // Binary operator
  type['+'] = type['-'] = type['*'] = type['/'] = 1;
  type['<'] = type['>'] = type['='] = type['&'] = type['|'] = 1;
  // blanks
  type[' '] = type['\n'] = 2;
  // curly brackets
  type['}'] = type['{'] = 3;
  // round brackets
  type['('] = type[')'] = 4;
  // comma
  type[','] = 5;
  // semicolon
  type[';'] = 6;
}

bool add_space(const token_t &s, const token_t &t) {
  int sf = s.first(), tf = t.first();
  if (tf == '}' || sf == '{') return false;
  if (s.is_key() && tf == '(') return true;
  if (type[sf] == 1) return type[tf] != 1 && tf != ';';
  else if (sf == ',') return tf != ',' && tf != ')';
  else if (sf == '}') return tf != ',' && tf != ')' && tf != ';';
  else if (sf == '(') return type[tf] == 1;
  else if (sf == ')') return tf != ',' && tf != ')' && tf != ';';
  else if (sf == ';') return tf != ',' && tf != ')';
  else return tf != ',' && tf != '(' && tf != ')' && tf != ';';
}

void preprocess(int n) {
  tokens.clear();
  char *token = buffer;
  for (int i = 0, j; i < n; ) {
    if (type[(int)s[i]] == 0 || type[(int)s[i]] == 2) {
      for (j = i; j < n && type[(int)s[j]] == type[(int)s[i]]; ++j);
      tokens.emplace_back(s + i, s + j);
      i = j;
    } else {
      tokens.emplace_back(s + i, s + i + 1);
      ++i;
    }
  }
  for (size_t i = 0, j = 0; i < tokens.size(); ++i) {
    if (tokens[i].is_blank()) continue;
    j = std::max(j, i + 1);
    while (j < tokens.size() && tokens[j].is_blank()) ++j;
    if (j == tokens.size() || tokens[j].first() == '}') {
      tokens[i].newline = true;
    } else if (tokens[i].first() == '{') {
      tokens[i].newline = true;
    } else if (tokens[i].first() == '}') {
      tokens[i].newline = !tokens[j].is_semicolon() && !tokens[j].is_else();
    }
    if (!tokens[i].newline) {
      tokens[i].space = add_space(tokens[i], tokens[j]);
    }
    tokens[i].sub = false;
    if (j != tokens.size() && tokens[j].first() == '}') {
      tokens[i].sub = true;
    }
  }
}

void parse(int upp) {
  int m = 0, lines = 0;
  int round = 0, indent = 0;
  while (tokens.back().is_blank()) tokens.pop_back();
  for (size_t j = 0; j < tokens.size(); ++j) {
    token_t &token = tokens[j];
    if (token.is_blank()) continue;
    char c = token.first();
    if (c == '(') round = std::min(round + 1, 4);
    else if (c == ')') round = std::max(round - 1, 0);
    else if (c == '{') indent += 2, round = 0;
    else if (c == '}') indent = std::max(0, indent - 2), round = 0;
    bool newline = token.newline;
    if (c == ';') newline |= round == 0;
    lines += newline;
    if (m < upp) {
      auto value = token.to_str();
      for (auto &&c: value) {
        if (m < upp) buffer[m++] = c;
      }
    }
    if (newline) {
      if (m < upp) buffer[m++] = '\n';
      if (j + 1 != tokens.size()) {
        int space = indent;
        if (token.sub) space -= 2;
        for (int i = 0; i < space && m < upp; ++i) {
          buffer[m++] = ' ';
        }
      }
    } else {
      if (m < upp && token.space) buffer[m++] = ' ';
    }
  }
  buffer[m] = 0;
  printf("%d @%s@\n", lines, buffer);
}

struct node {
  node *l, *r;
  int sz;
  std::pair<int, int> go[5];
  int curly_sum, indent;
  int nonblank;
  int sum, out, lines;
  token_t value;
  void append(const token_t &token) {
    int c = token.first();
    if (c == ';' && token.newline) c = '!';
    if (c == '(') {
      for (int i = 0; i < 5; ++i) {
        go[i].first = std::min(go[i].first + 1, 4);
      }
    } else if (c == ')') {
      for (int i = 0; i < 5; ++i) {
        go[i].first = std::max(go[i].first - 1, 0);
      }
    } else if (c == ';') {
      for (int i = 0; i < 5; ++i) {
        if (go[i].first == 0) go[i].second += 1;
      }
    } else if (c == '{') {
      for (int i = 0; i < 5; ++i) go[i].first = 0;
      curly_sum += 1;
      indent += 1;
    } else if (c == '}') {
      for (int i = 0; i < 5; ++i) go[i].first = 0;
      curly_sum -= 1;
      indent = std::max(0, indent - 1);
    }
    indent = std::max(0, indent);
    sz += 1;
    sum += token.size();
    nonblank += type[c] != 2;
    lines += token.newline;
    if (!token.is_blank()) {
      out += token.size() + token.space;
    }
  }
  void append(node *o) {
    sz += o->sz;
    for (int i = 0; i < 5; ++i) {
      go[i].second += o->go[go[i].first].second;
      go[i].first = o->go[go[i].first].first;
    }
    curly_sum += o->curly_sum;
    indent = std::max(o->indent, indent + o->curly_sum);
    indent = std::max(indent, 0);
    nonblank += o->nonblank;
    lines += o->lines;
    sum += o->sum;
    out += o->out;
  }
  node* update() {
    node tmp;
    memset(&tmp, 0, sizeof(tmp));
    for (int i = 0; i < 5; ++i) {
      tmp.go[i].first = i;
    }
    if (l) tmp = *l;
    tmp.append(value);
    if (r) tmp.append(r);
    tmp.l = l;
    tmp.r = r;
    tmp.value = value;
    *this = tmp;
    return this;
  }
} mem[N * 6], *top, *root;

node* new_node(const token_t &token) {
  memset(top, 0, sizeof(*top));
  for (int i = 0; i < 5; ++i) {
    top->go[i].first = i;
  }
  top->append(token);
  top->value = token;
  return top++;
}

node* build(int l, int r) {
  if (l > r) return 0;
  int m = (l + r) >> 1;
  node *o = new_node(tokens[m]);
  o->l = build(l, m - 1);
  o->r = build(m + 1, r);
  return o->update();
}

node* kth(node *o, int k) {
  int ls = o->l ? o->l->sz : 0;
  if (ls + 1 == k) return o;
  else if (k <= ls) return kth(o->l, k);
  else return kth(o->r, k - ls - 1);
}

node *first_nonblank(node *o) {
  if (kth(o, 1)->value.is_blank()) return kth(o, 2);
  else return kth(o, 1);
}

node* merge2(node *a, node *b) {
  int size_a = a ? a->sz : 0;
  int size_b = b ? b->sz : 0;
  node *x, *y;
  std::tie(a, x) = split(a, std::max(0, size_a - 3));
  std::tie(y, b) = split(b, std::min(3, size_b));
  std::vector<token_t> px, py;
  for (int i = 1; x && i <= x->sz; ++i) {
    token_t &token = kth(x, i)->value;
    token.space = token.newline = 0;
    px.push_back(token);
  }
  for (int i = 1; y && i <= y->sz; ++i) {
    token_t &token = kth(y, i)->value;
    token.space = token.newline = 0;
    py.push_back(token);
  }
  std::reverse(py.begin(), py.end());
  if (x && y) {
    int type_x = type[px.back().first()];
    int type_y = type[py.back().first()];
    if (type_x == type_y && (type_x == 0 || type_x == 2)) {
      px.back().append(py.back());
      py.pop_back();
    }
  }
  while (py.size()) {
    px.push_back(py.back());
    py.pop_back();
  }
  for (size_t i = 0, j = 0; i < px.size(); ++i) {
    int c = px[i].first();
    if (type[c] == 2) continue;
    j = std::max(j, i + 1);
    while (j < px.size() && px[j].is_blank()) ++j;
    if (j == px.size()) {
      if (c == '{' || !b || b->nonblank == 0) px[i].newline = true;
      if (b && b->nonblank) {
        const token_t &token = first_nonblank(b)->value;
        px[i].space = add_space(px[i], token);
        if (token.first() == '}') px[i].newline = true;
        else if (c == '{') px[i].newline = true;
        else if (c == '}') px[i].newline = !token.is_semicolon() && !token.is_else();
      }
    } else if (px[j].first() == '}') {
      px[i].newline = true;
    } else if (c == '{') {
      px[i].newline = true;
    } else if (c == '}') {
      px[i].newline = !px[j].is_semicolon() && !px[j].is_else();
    }
    if (j != px.size()) {
      px[i].space = add_space(px[i], px[j]);
    }
  }
  for (auto &&e: px) {
    a = merge(a, new_node(e));
  }
  return merge(a, b);
}

int find_sep(node *o, int n) {// last position sum <= n
  if (!o || !n) return 0;
  int ls = o->l ? o->l->sum : 0, ms = o->value.size();
  if (n <= ls) return find_sep(o->l, n);
  else if (n < ls + ms) return o->l ? o->l->sz : 0;
  else return (o->l ? o->l->sz : 0) + 1 + find_sep(o->r, n - ls - ms);
}

std::pair<node*, node*> split2(node *o, int n) {
  node *a, *b, *c;
  int p = find_sep(o, n);
  std::tie(a, b) = split(o, p);
  n -= a ? a->sum : 0;
  if (!n) return {a, b};
  std::tie(b, c) = split(b, 1);
  token_t x, y;
  std::tie(x, y) = b->value.split(n);
  return {merge(a, new_node(x)), merge(new_node(y), c)};
}

int total_lines(node *o) {
  return !o ? 0 : o->lines + o->go[0].second;
}

void solve_add() {
  int p;
  scanf("%d", &p);
  get_source();
  preprocess(strlen(s));
  node *c = build(0, tokens.size() - 1);
  node *a, *b;
  std::tie(a, b) = split2(root, p - 1);
  a = merge2(a, c);
  root = merge2(a, b);
  total += strlen(s);
  assert((root ? root->sum : 0) == total);
  printf("%d\n", total_lines(root));
}

void solve_del() {
  int p, k;
  scanf("%d%d", &p, &k);
  total -= k;
  node *a, *b, *c;
  std::tie(a, b) = split2(root, p - 1);
  std::tie(b, c) = split2(b, k);
  root = merge2(a, c);
  assert((root ? root->sum : 0) == total);
  printf("%d\n", total_lines(root));
}

int find_sep2(node *o, int n) {// last position out <= n
  if (!o || !n) return 0;
  int ls = o->l ? o->l->out : 0, ms = o->value.size() + o->value.space;
  if (o->value.is_blank()) ms = 0;
  if (n <= ls) return find_sep2(o->l, n);
  else if (n < ls + ms) return o->l ? o->l->sz : 0;
  else return (o->l ? o->l->sz : 0) + 1 + find_sep2(o->r, n - ls - o->out);
}

int out_sum(node *o, int n) {
  if (!o || !n) return 0;
  int ls = o->l ? o->l->sz : 0, ms = o->value.size() + o->value.space;
  if (o->value.is_blank()) ms = 0;
  if (n <= ls) return out_sum(o->l, n);
  else return (o->l ? o->l->out : 0) + ms + out_sum(o->r, n - ls - 1);
}

void resolve(node *o, int s, int t, int &m) {
  if (s >= t || o->out <= s) return;
  int p = find_sep2(o, s);
  int now = out_sum(o, p);
  for (p++; p <= o->sz; ++p) {
    token_t &token = kth(o, p)->value;
    if (token.is_blank()) continue;
    int st = now, ed = now + token.size() + token.space;
    now = ed;
    if (s >= ed) continue;
    if (st >= t) break;
    int a = std::max(s, st), b = std::min(t, ed);
    int l = a - st + 1, r = b - st;
    std::string value = token.get(l, r);
    for (auto &&c: value) buffer[m++] = c;
    if (b == ed && token.space && p != o->sz) buffer[m++] = ' ';
  }
}

void solve_get() {
  int r, p, k;
  scanf("%d%d%d", &r, &p, &k);
  --p;
  if (r > total_lines(root)) {
    puts("@@");
    return;
  }
  auto find = [&](int line) {
    int left = 0, right = root->sz;
    while (left < right) {
      int mid = (left + right - 1) >> 1;
      node *a, *b;
      std::tie(a, b) = split(root, mid);
      if (total_lines(a) >= line) right = mid;
      else left = mid + 1;
      root = merge(a, b);
    }
    return left;
  };
  int st = find(r - 1), ed = find(r);
  node *a, *b, *c;
  std::tie(b, c) = split(root, ed);
  std::tie(a, b) = split(b, st);
  int indent = a ? a->indent * 2 : 0;
  if (first_nonblank(b)->value.first() == '}') indent -= 2;
  if (indent < 0) indent = 0;
  int m = 0, rest = k;
  if (indent > p) {
    for (int i = 0; i < k && i < indent - p; ++i) {
      buffer[m++] = ' ';
    }
    rest -= m;
  }
  p = std::max(0, p - indent);
  resolve(b, p, p + rest, m);
  while (m < k) buffer[m++] = '#';
  buffer[m] = 0;
  printf("@%s@\n", buffer);
  root = merge(a, merge(b, c));
}

int main() {
  top = mem;
  prepare();
  get_source();
  preprocess(strlen(s));
  total += strlen(s);
  root = build(0, tokens.size() - 1);
  parse(100000);
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    static char opt[10];
    scanf("%s", opt);
    if (opt[0] == 'a') solve_add();
    else if (opt[0] == 'd') solve_del();
    else solve_get();
  }
  return 0;
}
