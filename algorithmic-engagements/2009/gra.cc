#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

struct Block {
  int col;
  int cnt, len;
  int move;
};

int nim(std::vector<Block> &blocks) {
  int r = 0;
  for (auto &e: blocks) r ^= e.move;
  return r;
}

void move(int p, std::vector<Block> &blocks) {
  int n = blocks.size();
  if (blocks[p].move == 0) {
    blocks[(p - 1 + n) % n].len += blocks[(p - 1 + n) % n].move;
    blocks[(p - 1 + n) % n].move = 0;
  } else {
    blocks[(p + 1) % n].len += blocks[p].move;
    blocks[p].move = 0;
  }
}

char solve(std::vector<Block> &blocks) {
  int n = blocks.size();
  bool single[2] = {1, 1};
  for (auto &e: blocks) {
    single[e.col] &= e.cnt == 1;
  }
  // all single blocks => tie
  if (single[0] && single[1]) return 'R';
  // white all single blocks => black win
  if (single[0]) return 'C';
  // black all single blocks => white win
  if (single[1]) return 'B';

  int st = 0;
  while (st < n && blocks[st].cnt == 1) ++st;
  assert(st != n);
  std::vector<Block> tmp = {blocks[st]};
  for (int i = st, j; ; ) {
    for (j = (i + 1) % n; j != st && blocks[j].cnt == 1; j = (j + 1) % n);
    if (blocks[i].col == blocks[j].col) {
      tmp.back().len += blocks[i].move;
      for (i = (i + 1) % n; i != j; i = (i + 1) % n) {
        tmp.back().len += blocks[i].move;
      }
      if (i == st) {
        tmp[0].cnt += tmp.back().cnt;
        tmp[0].len += tmp.back().len;
        tmp.pop_back();
      } else {
        tmp.back().cnt += blocks[i].cnt;
        tmp.back().len += blocks[i].len;
        tmp.back().move = blocks[i].move;
      }
    } else {
      int e = 0;
      for (i = (i + 1) % n; i != j; i = (i + 1) % n) {
        tmp.push_back(blocks[i]);
        tmp.back().cnt++;
        tmp.back().len++;
        if (e == 0) tmp.back().move = 0;
        e ^= 1;
      }
      if (i != st) tmp.push_back(blocks[i]);
    }
    if (i == st) break;
  }
  blocks.swap(tmp);
  n = blocks.size();

  int free_slot[2] = {0, 0};
  int can_free[2] = {0, 0};
  int pos_free[2] = {-1, -1};
  for (int i = 0; i < n; ++i) {
    const auto &e = blocks[i];
    free_slot[e.col] += 3 <= e.cnt && e.cnt < e.len;
    if (3 <= e.cnt && e.cnt == e.len && (e.move || blocks[(i - 1 + n) % n].move)) {
      pos_free[e.col] = i;
      can_free[e.col]++;
    }
  }
  // both have free slots
  if (free_slot[0] && free_slot[1]) return 'R';
  // black has free slots or it can make at least 2 free slots
  if (free_slot[1] || can_free[1] > 1) {
    // white has free slots or it can make at least 1 free slot
    if (free_slot[0] || can_free[0]) return 'R';
    // white has no free slots neither it can make one
    else return 'C';
  }
  assert(!free_slot[1]);
  // black has not free slots neither it can make one
  if (can_free[1] == 0) {
    // white has free slots or it can make at least one
    if (free_slot[0] || can_free[0]) return 'B';
    // white has no free slots neither it can make one, look at nim sum
    else return nim(blocks) ? 'B' : 'C';
  }
  assert(can_free[1] == 1);
  int p = pos_free[1];
  if (blocks[p].move == 0 || blocks[(p - 1 + n) % n].move == 0) { // we can prevent black forming free slot
    move(p, blocks);
    free_slot[0] = free_slot[1] = 0;
    can_free[0] = can_free[1] = 0;
    pos_free[0] = pos_free[1] = -1;
    for (int i = 0; i < n; ++i) {
      const auto &e = blocks[i];
      free_slot[e.col] += 3 <= e.cnt && e.cnt < e.len;
      if (3 <= e.cnt && e.cnt == e.len && (e.move || blocks[(i - 1 + n) % n].move)) {
        pos_free[e.col] = i;
        can_free[e.col]++;
      }
    }
    if (free_slot[0] || can_free[0] > 1) return 'B';
    if (can_free[0] == 1) {
      p = pos_free[0];
      if (blocks[p].move == 0 || blocks[(p - 1 + n) % n].move == 0) { // we can prevent black forming free slot
        move(p, blocks);
        if (nim(blocks)) return 'B';
        else return 'R';
      } else {
        return 'B';
      }
    } else {
      return nim(blocks) ? 'C' : 'B';
    }
  } else { // we can not prevent black forming free slot
    // white has free slots or it can make at least 1 free slot
    if (free_slot[0] || can_free[0]) return 'R';
    else return 'C';
  }
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int s, n, m;
    scanf("%d%d%d", &s, &n, &m);
    std::vector<int> a(n), b(m);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    for (int i = 0; i < m; ++i) scanf("%d", &b[i]);
    if (n + m == s) {
      puts("C");
      continue;
    }
    std::vector<Block> blocks;
    int last = 0;
    for (int i = 0, j = 0; i < n || j < m; ) {
      if (j == m || (i != n && a[i] < b[j])) {
        if (blocks.empty()) {
          last = a[i] - 1;
          blocks.push_back((Block){0, 0, 0, -1});
        }
        if (blocks.back().col == 1) {
          blocks.back().move = a[i] - last - 1;
          blocks.push_back((Block){0, 1, 1, -1});
        } else {
          blocks.back().cnt++;
          blocks.back().len += a[i] - last;
        }
        last = a[i++];
      } else {
        assert(j < m);
        if (blocks.empty()) {
          last = b[j] - 1;
          blocks.push_back((Block){1, 0, 0, -1});
        }
        if (blocks.back().col == 0) {
          blocks.back().move = b[j] - last - 1;
          blocks.push_back((Block){1, 1, 1, -1});
        } else {
          blocks.back().cnt++;
          blocks.back().len += b[j] - last;
        }
        last = b[j++];
      }
    }
    if (blocks[0].col == blocks.back().col) {
      blocks[0].cnt += blocks.back().cnt;
      blocks[0].len += blocks.back().len + s - last + std::min(a[0], b[0]) - 1;
      blocks.pop_back();
    } else {
      blocks.back().move = s - last + std::min(a[0], b[0]) - 1;
    }
    for (auto &e: blocks) {
      s -= e.len + e.move;
    }
    assert(s == 0);
    printf("%c\n", solve(blocks));
  }
  return 0;
}
