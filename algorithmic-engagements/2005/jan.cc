#include <vector>
#include <string>
#include <cstring>

/**
 * Duval's Lyndon Factorization Algorithm.
 *
 * the input string s should end with a zero symbol
 * return a list of begins of prime strings
 **/
std::vector<int> duval(char s[]){
  std::vector<int> ret;
  int n = strlen(s) + 1; // zero used here
  int start = 0, mid = 1, cur = 0;
  ret.push_back(0);
  for (int i = 0; i < n; ++i){
    if (s[i] == s[cur]){
      if (++cur == mid) cur = start;
    } else if (s[i] > s[cur]){
      mid = i + 1;
      cur = start;
    } else if (s[i] < s[cur]){
      int temp = mid - start;
      while (start + temp <= i){
        start += temp;
        ret.push_back(start);
      }
      i = cur = start;
      mid = start + 1;
    }
  }
  return ret;
}

const int N = 1e6 + 10;

char s[N];

int main() {
  int n;
  scanf("%d%s", &n, s);
  auto p = duval(s);
  printf("%s=", s);
  for (size_t i = 0; i + 1 < p.size(); ++i) {
    if (i) putchar('+');
    for (int j = p[i]; j < p[i + 1]; ++j) putchar(s[j]);
  }
  puts("");
  return 0;
}
