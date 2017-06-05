#include "query_of_death.h"
#include <message.h>
#include <bits/stdc++.h>

int main() {
  int n = GetLength();
  int me = MyNodeId();
  int nodes = NumberOfNodes();
  int L = 1ll * n * me / nodes, R = 1ll * n * (me + 1) / nodes;
  bool broken = false;
  int broken_id = -1, broken_node = 0;
  int sum = 0;
  for (int i = L; i < R; ++i) {
    int a = GetValue(i);
    for (int it = 0; it < 10; ++it) {
      int b = GetValue(i);
      if (a != b) {
        broken = true;
        broken_id = i;
        broken_node = me;
        break;
      }
    }
    if (broken) break;
    sum += a;
  }

  if (broken) {
    PutInt(0, broken_node);
    PutInt(0, broken_id);
    Send(0);
  } else {
    PutInt(0, -1);
    PutInt(0, -1);
    Send(0);
  }
  if (!me) {
    for (int node = 0; node < nodes; ++node) {
      Receive(node);
      int x = GetInt(node);
      int y = GetInt(node);
      if (x != -1) {
        broken_node = node;
        broken_id = y;
      }
    }
  }
  if (!me) {
    for (int node = 0; node < nodes; ++node) {
      PutInt(node, broken_node);
      PutInt(node, broken_id);
      Send(node);
    }
  }
  Receive(0);
  broken_node = GetInt(0);
  broken_id = GetInt(0);
  int target = 0;
  for (; target < nodes; ++target) {
    if (target != broken_node) break;
  }
  //printf("%d %d %d %d %d %d\n", L, R, sum, broken_node, broken_id, target);
  if (target == me) {
    int L = 1ll * n * broken_node / nodes, R = 1ll * n * (broken_node + 1) / nodes;
    for (int i = L; i < broken_id; ++i) sum += GetValue(i);
    for (int i = broken_id + 1; i < R; ++i) sum += GetValue(i);
    sum += GetValue(broken_id);
  }
  int ret = broken ? 0 : sum;
  if (me) {
    PutInt(0, broken);
    if (broken) PutInt(0, broken_id);
    else PutInt(0, sum);
    Send(0);
  } else {
    for (int node = 1; node < nodes; ++node) {
      Receive(node);
      bool flag = GetInt(node);
      if (flag) {
        broken_node = node;
        broken_id = GetInt(node);
      } else{
        ret += GetInt(node);
      }
    }
    printf("%d\n", ret);
  }
  return 0;
}
