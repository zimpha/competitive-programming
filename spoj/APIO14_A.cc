#include <bits/stdc++.h>
using namespace std;
// palindrome tree, O(N)
namespace PT {
  static const int MAXN = 300000 + 10, SIGMA = 26;
  struct Node {
    Node* ch[SIGMA], *fa;
    int len, num, cnt; // length of the palindrome, number of the palindrome
  } pool[MAXN], *last;
  int sz; char *s;
  void init(char p[], int n) {
    memset(pool, 0, sizeof(pool[0]) * (n + 10));
    s = p; last = &pool[1]; sz = 2;
    pool[0].len = -1; pool[0].fa = &pool[0];
    pool[1].len = 0; pool[1].fa = &pool[0];
  }
  bool add(int pos) {
    Node *cur = last;
    int curlen = 0, c = s[pos] - 'a';
    while (1) {
      curlen = cur->len;
      if (pos >= 1 + curlen && s[pos - 1 - curlen] == s[pos]) break;
      cur = cur->fa;
    }
    if (cur->ch[c]) return last = cur->ch[c], last->cnt ++, false;
    last = &pool[sz ++]; last->cnt ++;
    last->len = cur->len + 2; cur->ch[c] = last;
    if (last->len == 1) return last->fa = &pool[1], last->num = 1;
    while (1) {
      cur = cur->fa; curlen = cur->len;
      if (pos >= curlen + 1 && s[pos - 1 - curlen] == s[pos]) {
        last->fa = cur->ch[c];
        break;
      }
    }
    last->num = last->fa->num + 1;
    return true;
  }
}

const int MAXN = 300000 + 10;
char s[MAXN];

int main() {
  scanf("%s", s);
  int len = strlen(s);
  PT::init(s, len);
  long long ret = 0;
  for (int i = 0; i < len; ++ i) PT::add(i);
  for (int i = PT::sz - 1; i > 1; -- i) {
    PT::pool[i].fa->cnt += PT::pool[i].cnt;
    ret = max(ret, 1ll * PT::pool[i].len * PT::pool[i].cnt);
  }
  cout << ret << endl;
  return 0;
}
