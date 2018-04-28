#include <cstdio>
#include <cassert>
#include <cstring>
#include <string>
#include <stack>

const int N = 1e5;

bool value[26];
char s[N], ret[N];

bool calc(bool a, bool b, char c) {
  if (c == '|') return a || b;
  if (c == '&') return a && b;
  if (c == '<') return a == b;
  if (c == '=') return !a || b;
  if (c == '#') return a ^ b;
  assert(false);
}

bool evaluate(char s[]) {
  std::stack<char> o;
  std::stack<bool> v;
  int n = strlen(s);
  auto pop = [&]() {
    if (o.top() == '!') {
      v.top() = !v.top();
    } else {
      bool b = v.top(); v.pop();
      bool a = v.top(); v.pop();
      v.push(calc(a, b, o.top()));
    }
    o.pop();
  };
  for (int i = 0; i < n; ++i) {
    if (s[i] >= 'a' && s[i] <= 'j') {
      v.push(value[s[i] - 'a']);
    } else if (s[i] == '(') {
      o.push(s[i]);
    } else if (s[i] == ')') {
      while (o.top() != '(') {
        pop();
      }
      o.pop();
    } else if (s[i] == '&') {
      while (!o.empty() && (o.top() == '&' || o.top() == '!')) {
        pop();
      }
      o.push('&');
    } else if (s[i] == '!') {
      o.push('!');
    } else {
      while (!o.empty() && o.top() != '(') {
        pop();
      }
      o.push(s[i]);
      if (s[i] == '|') i += 1;
      if (s[i] == '<') i += 2;
      if (s[i] == '=') i += 1;
    }
  }
  while (!o.empty()) pop();
  return v.top();
}

int main() {
  scanf("%s", s);
  int n = 0;
  for (int mask = 0; mask < 1024; ++mask) {
    std::string tmp = "";
    for (int i = 0; i < 10; ++i) {
      value[i] = mask >> i & 1;
      if (i) tmp += "&";
      if (value[i]) tmp += i + 'a';
      else tmp += "!" + std::string(1, i + 'a');
    }
    if (evaluate(s)) {
      if (n != 0) {
        ret[n++] = '|';
        ret[n++] = '|';
      }
      for (auto &&c: tmp) ret[n++] = c;
    }
  }
  if (n == 0) {
    puts("!a&a");
    return 0;
  }
  ret[n] = 0;
  puts(ret);
  return 0;
}
