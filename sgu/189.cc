#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <map>

std::map<std::string, std::string> mem;

struct substr_t {
  std::string name;
  int offset;
  int count;
  substr_t(const std::string &name, int offset, int count):
    name(name), offset(offset), count(count) {}
};

int main() {
  int n, m;
  std::string line;
  std::cin >> n >> m;
  std::getline(std::cin, line);
  for (int i = 0; i < n; ++i) {
    std::getline(std::cin, line);
    std::string name, value;
    int l = line.find('$');
    int r = line.find('=', l);
    for (; l < r; ++l) {
      if (line[l] == ' ' || line[l] == '=') break;
      name += line[l];
    }
    l = line.find('"');
    r = line.find('"', l + 1);
    value = line.substr(l + 1, r - l - 1);
    mem[name] = value;
  }
  for (int i = 0; i < m; ++i) {
    std::getline(std::cin, line);
    std::vector<std::string> tokens;
    std::string token;
    for (auto &&c: line) {
      if (c == ' ' || c == '(' || c == ')' || c == ';' || c == ',') {
        if (!token.empty()) tokens.push_back(token);
        token = "";
      } else if (c == '=') {
        if (!token.empty()) tokens.push_back(token);
        tokens.push_back("=");
        token = "";
      } else {
        token += c;
      }
    }
    auto substr = [&tokens] (size_t p) {
      auto is_number = [](const std::string &s) {
        for (auto &&c: s) {
          if (c != '-' && !isdigit(c)) return false;
        }
        return true;
      };
      std::string &name = tokens[p + 1];
      int len = mem[name].size();
      int offset = std::atoi(tokens[p + 2].c_str());
      int count = len - offset;
      if (offset < 0) offset += len;
      if (p + 3 < tokens.size() && is_number(tokens[p + 3])) {
        count = std::atoi(tokens[p + 3].c_str());
        if (count < 0) count = len - offset + count;
      }
      return substr_t(name, offset, count);
    };
    if (tokens[0] == "print") {
      if (tokens[1] == "substr") {
        auto s = substr(1);
        printf("%s\n", mem[s.name].substr(s.offset, s.count).c_str());
      } else {
        printf("%s\n", mem[tokens[1]].c_str());
      }
    } else if (tokens[0] == "substr") {
      auto s = substr(0);
      int p = 0;
      if (tokens[3] == "=") p = 4;
      else if (tokens[4] == "=") p = 5;
      assert(p != 0);
      if (tokens[p] == "substr") {
        auto t = substr(p);
        mem[s.name].replace(s.offset, s.count, mem[t.name].substr(t.offset, t.count));
      } else {
        mem[s.name].replace(s.offset, s.count, mem[tokens[p]]);
      }
    } else {
      assert(tokens[1] == "=");
      if (tokens[2] == "substr") {
        auto s = substr(2);
        mem[tokens[0]] = mem[s.name].substr(s.offset, s.count);
      } else {
        mem[tokens[0]] = mem[tokens[2]];
      }
    }
  }
  return 0;
}
