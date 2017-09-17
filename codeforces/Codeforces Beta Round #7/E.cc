#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cassert>
#include <map>

const int N = 200;

std::map<std::string, int> state;
int dp[N][N];

int calc(int l, int r, const std::vector<int> &tokens) {
  if (l + 1 == r) return dp[l][r] = tokens[l];
  if (dp[l][r]) return dp[l][r];
  int k = l + 1;
  for (int i = l + 1; i < r; i += 2) {
    if (tokens[k] > 6 || tokens[i] < 7) k = i;
  }
  calc(l, k, tokens);
  calc(k + 1, r, tokens);
  if (dp[l][k] == 2 || dp[k + 1][r] == 2) return dp[l][r] = 2;
  else if (tokens[k] == 5) return dp[l][r] = 3;
  else if (tokens[k] == 6) {
    if (dp[k + 1][r] == 3) return dp[l][r] = 2;
    else return dp[l][r] = 3;
  } else if (tokens[k] == 7) {
    if (dp[l][k] == 3 || dp[k + 1][r] == 3) return dp[l][r] = 2;
    else return dp[l][r] = 4;
  } else if (tokens[k] == 8) {
    if (dp[l][k] == 3 || dp[k + 1][r] == 3 || dp[k + 1][r] == 4) return dp[l][r] = 2;
    else return dp[l][r] = 4;
  }
  assert(false);
}

bool is_var(char c) {
  return (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z');
}

int solve(int l, int r, const std::string &line) {
  std::vector<int> tokens;
  std::string now;
  int dep = 0, last = -1;
  for (int i = l; i <= r; ++i) {
    if (i < r && is_var(line[i])) now += line[i];
    else {
      if (now != "" && dep == 0) {
        if (state.count(now)) tokens.push_back(state[now]);
        else tokens.push_back(1);
      }
      now = "";
    }
    if (i == r) break;
    if (line[i] == '(') {
      if (dep == 0) last = i + 1;
      dep++;
    }
    if (line[i] == ')') {
      dep--;
      if (dep == 0) {
        int tmp = solve(last, i, line);
        if (tmp != 2) tmp = 1;
        tokens.push_back(tmp);
      }
    }
    if (dep == 0 && line[i] == '+') tokens.push_back(5);
    if (dep == 0 && line[i] == '-') tokens.push_back(6);
    if (dep == 0 && line[i] == '*') tokens.push_back(7);
    if (dep == 0 && line[i] == '/') tokens.push_back(8);
  }
  memset(dp, 0, sizeof(dp));
  return calc(0, tokens.size(), tokens);
}

int main() {
  int n;
  std::cin >> n;
  for (int i = 0; i <= n; ++i) {
    std::string line, token, name;
    if (!i) std::getline(std::cin, line);
    std::getline(std::cin, line);
    std::stringstream sin(line);
    line = "";
    if (i < n) {
      sin >> token;
      if (token.size() == 1) sin >> token;
      sin >> name;
    }
    while (sin >> token) line += token;
    state[name] = solve(0, line.size(), line);
  }
  if (state[""] != 2) std::cout << "OK" << std::endl;
  else std::cout << "Suspicious" << std::endl;
  return 0;
}