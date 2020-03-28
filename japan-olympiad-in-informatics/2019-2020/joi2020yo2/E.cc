#include <cstdio>
#include <array>
#include <vector>

using int64 = long long;

const int N = 2e5 + 10;
const int mod = 1e9 + 7;

const int add[3][3] = {
  {0, 0, 2},
  {0, 1, 1},
  {2, 1, 2}
};

const int sub[3][3] = {
  {0, 1, 0},
  {1, 1, 2},
  {0, 2, 2}
};

const int mul[3][3] = {
  {0, 2, 1},
  {2, 1, 0},
  {1, 0, 2}
};

using Value = std::array<int64, 3>;

Value opt(char op, const Value &a, const Value &b) {
  Value c{};
  for (int x = 0; x < 3; ++x) for (int y = 0; y < 3; ++y) {
    int z = mul[x][y];
    if (op == '+') z = add[x][y];
    else if (op == '-') z = sub[x][y];
    (c[z] += a[x] * b[y]) %= mod;
  }
  return c;
}

char s[N];

int main() {
  int n;
  scanf("%d%s", &n, s);
  std::vector<char> op;
  std::vector<Value> stack;
  for (int i = 0; i < n; ++i) {
    if (s[i] == '+' || s[i] == '-' || s[i] == ')') {
      while (!op.empty() && op.back() != '(') {
        auto b = stack.back(); stack.pop_back();
        auto a = stack.back(); stack.pop_back();
        auto c = opt(op.back(), a, b);
        stack.push_back(c);
        op.pop_back();
      }
      if (s[i] == ')') op.pop_back();
      else op.push_back(s[i]);
    } else if (s[i] == '*') {
      while (!op.empty() && op.back() == '*') {
        auto b = stack.back(); stack.pop_back();
        auto a = stack.back(); stack.pop_back();
        auto c = opt(op.back(), a, b);
        stack.push_back(c);
        op.pop_back();
      }
      op.push_back(s[i]);
    } else if (s[i] == '(') {
      op.push_back(s[i]);
    } else {
      Value v{};
      if (s[i] == 'R') v[0] = 1;
      else if (s[i] == 'S') v[1] = 1;
      else if (s[i] == 'P') v[2] = 1;
      else v[0] = v[1] = v[2] = 1;
      stack.push_back(v);
    }
  }
  while (!op.empty()) {
    auto b = stack.back(); stack.pop_back();
    auto a = stack.back(); stack.pop_back();
    auto c = opt(op.back(), a, b);
    stack.push_back(c);
    op.pop_back();
  }
  scanf("%s", s);
  if (s[0] == 'R') printf("%lld\n", stack[0][0]);
  else if (s[0] == 'S') printf("%lld\n", stack[0][1]);
  else printf("%lld\n", stack[0][2]);
  return 0;
}
