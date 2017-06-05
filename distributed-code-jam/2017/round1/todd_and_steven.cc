#include "todd_and_steven.h"
#include <message.h>
#include <bits/stdc++.h>

using ll = long long;
using pii = std::pair<ll, ll>;

const int mod = 1e9 + 7;

int search_odd(int l, int r, ll x) {
  if (GetToddValue(r) < x) return r + 1;
  if (GetToddValue(l) > x) return 0;
  while (l < r) {
    int m = (l + r + 1) >> 1;
    if (GetToddValue(m) < x) l = m;
    else r = m - 1;
  }
  return l + 1;
}

int search_even(int l, int r, ll x) {
  if (GetStevenValue(r) < x) return r + 1;
  if (GetStevenValue(l) > x) return 0;
  while (l < r) {
    int m = (l + r + 1) >> 1;
    if (GetStevenValue(m) < x) l = m;
    else r = m - 1;
  }
  return l + 1;
}

int main() {
  int n = GetToddLength(), m = GetStevenLength();
  int me = MyNodeId();
  int nodes = NumberOfNodes();
  int half = nodes / 2;
  std::vector<pii> all;
  int wo = n / half + !!(n % half);
  for (int i = 0, s = 0; s < n; ++i, s += wo) {
    int t = std::min(s + wo - 1, n - 1);
    all.emplace_back(GetToddValue(t), t);
  }
  int we = m / half + !!(m % half);
  for (int i = 0, s = 0; s < m; ++i, s += we) {
    int t = std::min(s + we - 1, m - 1);
    all.emplace_back(GetStevenValue(t), t);
  }
  std::sort(all.begin(), all.end());
  assert(all.size() <= nodes);
  if (me >= all.size()) return 0;
  std::vector<int> cnt_odd(all.size()), cnt_even(all.size());
  for (size_t i = 0; i < all.size(); ++i) {
    if (all[i].first & 1) {
      cnt_even[i] = search_even(0, m - 1, all[i].first);
      cnt_odd[i] = all[i].second + 1;
    } else {
      cnt_odd[i] = search_odd(0, n - 1, all[i].first);
      cnt_even[i] = all[i].second + 1;
    }
  }
  int lo = 0, ro = 0;
  int le = 0, re = 0;
  int idx = 0;
  if (me == 0) {
    lo = 0, ro = cnt_odd[0];
    le = 0, re = cnt_even[0];
    if (all[0].first & 1) {
      //s = get_odd(0, all[0].second + 1);
      //t = get_even(0, cnt_even[0]);
    } else {
      //s = get_odd(0, cnt_odd[0]);
      //t = get_even(0, all[0].second + 1);
    }
  } else {
    idx = cnt_odd[me - 1] + cnt_even[me - 1];
    lo = cnt_odd[me - 1], ro = cnt_odd[me];
    le = cnt_even[me - 1], re = cnt_even[me];
    //s = get_odd(cnt_odd[me - 1], cnt_odd[me]);
    //t = get_even(cnt_even[me - 1], cnt_even[me]);
  }
  ll ret = 0;
  int i = lo, j = le;
  ll a = -1, b = -1;
  for (; i < ro && j < re; ) {
    if (a == -1) a = GetToddValue(i);
    if (b == -1) b = GetStevenValue(j);
    if (a < b) ret += ((idx++) ^ a), ++i, a = -1;
    else ret += ((idx++) ^ b), ++j, b = -1;
    ret %= mod;
  }
  for (; i < ro; ++i) ret = (ret + ((idx++) ^ GetToddValue(i))) % mod;
  for (; j < re; ++j) ret = (ret + ((idx++) ^ GetStevenValue(j))) % mod;
  if (me) {
    PutLL(0, ret);
    Send(0);
  } else {
    for (int node = 1; node < all.size(); ++node) {
      Receive(node);
      ret += GetLL(node);
    }
    ret %= mod;
    printf("%lld\n", ret);
  }
  return 0;
}
