#include <cstdio>
#include <cassert>
#include <algorithm>

using i64 = long long;

struct Position {
  i64 x, y;
  i64 dis;
};

std::pair<i64, i64> next_pos(int k, i64 x, i64 y) {
  i64 w = 1 << k;
  assert(w != x && w != y);
  if (x < w && y < w) return {w - y, x};
  if (x > w && y < w) return {y, w - (x - w)};
  if (x < w && y > w) return {x, y - w};
  return {x - w, y - w};
}

std::pair<i64, i64> cur_pos(int k, i64 x, i64 y, int quarter) {
  i64 w = 1 << k;
  if (quarter == 0) {
    return {y, w - x};
  }
  if (quarter == 1) {
    return {2 * w - y, x};
  }
  if (quarter == 2) {
    return {x, y + w};
  }
  return {x + w, y + w};
}

void dfs(int k, i64 x, i64 y, Position *path) {
  if (k == 0) {
    path[k] = {x, y - 1, 1};
    return;
  }
  i64 w = 1 << k;
  i64 dis = 0;
  if (x != w && y != w) {
    int quarter = 2 * (y > w) + (x > w);
    auto next = next_pos(k, x, y);
    dfs(k - 1, next.first, next.second, path);
    auto cur = cur_pos(k, path[k - 1].x, path[k - 1].y, quarter);
    dis += path[k - 1].dis;
    x = cur.first;
    y = cur.second;
  }
  if (y == w || (x == w && y < w)) {
    path[k] = {w, 0, dis + std::abs(x - w) + y};
  } else if (x == w) {
    path[k] = {w, w * 2, dis + w * 2 - y};
  } else {
    path[k] = {x, y, dis};
  }
}

Position paths[34], patht[34];

i64 border(i64 len, i64 x, i64 y) {
  if (y == 0) return x;
  else if (x == len - 1) return len - 1 + y;
  else if (y == len - 1) return (len - 1) * 3 - x;
  else return (len - 1) * 4 - y;
}

i64 get_dis(int k, i64 xs, i64 ys, i64 xt, i64 yt) {
  i64 w = 1 << k;
  i64 ret = 0;
  if (xs == w && ys > w && xt == w && yt > w) return std::abs(yt - ys);
  if (ys == w && yt == w && xs > 0 && xt > 0 && xs < w * 2 && xt < w * 2) return std::abs(xs - xt);
  if (ys == w && xs > 0 && xs < w * 2) ret += std::abs(xs - w), xs = w;
  if (yt == w && xt > 0 && xt < w * 2) ret += std::abs(xt - w), xt = w;
  if (xs == w && ys <= w && xt == w && yt <= w) return std::abs(yt - ys) + ret;
  if (xs == w) {
    if (ys <= w) ret += ys, ys = 0;
    else ret += w * 2 - ys, ys = w * 2;
  }
  if (xt == w) {
    if (yt <= w) ret += yt, yt = 0;
    else ret += w * 2 - yt, yt = w * 2;
  }
  // now two points are on the border
  i64 ps = border(w * 2 + 1, xs, ys);
  i64 pt = border(w * 2 + 1, xt, yt);
  if (ps > pt) std::swap(ps, pt);
  return ret + std::min(pt - ps, w * 8 - (pt - ps));
}

i64 solve(int k, i64 xs, i64 ys, i64 xt, i64 yt) {
  if (k == 0) return 0;
  i64 w = 1 << k;
  int quarter_s = 2 * (ys > w) + (xs > w);
  int quarter_t = 2 * (yt > w) + (xt > w);
  i64 ret = 0;
  // save the original position
  i64 oxs = xs, oys = ys, oxt = xt, oyt = yt;
  if (xs != w && ys != w) {
    ret += paths[k - 1].dis;
    auto cur = cur_pos(k, paths[k - 1].x, paths[k - 1].y, quarter_s);
    xs = cur.first;
    ys = cur.second;
  }
  if (xt != w && yt != w) {
    ret += patht[k - 1].dis;
    auto cur = cur_pos(k, patht[k - 1].x, patht[k - 1].y, quarter_t);
    xt = cur.first;
    yt = cur.second;
  }
  if (xs != xt || ys != yt || oxs == w || oxt == w || oys == w || oyt == w || quarter_s != quarter_t) {
    return ret + get_dis(k, xs, ys, xt, yt);
  }
  auto next_s = next_pos(k, oxs, oys);
  auto next_t = next_pos(k, oxt, oyt);
  return solve(k - 1, next_s.first, next_s.second, next_t.first, next_t.second);
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int k, xs, ys, xt, yt;
    scanf("%d%d%d%d%d", &k, &xs, &ys, &xt, &yt);
    dfs(k, xs, ys, paths);
    dfs(k, xt, yt, patht);
    printf("%lld\n", solve(k, xs, ys, xt, yt));
  }
  return 0;
}
