#include "query_of_death.h"
#include <message.h>
#include <cstdio>

int main() {
  int n = GetLength();
  int me = MyNodeId();
  int nodes = NumberOfNodes();
  int L = 1ll * n * me / nodes, R = 1ll * n * (me + 1) / nodes;
  int qod = -1;
  int sum = 0;
  for (int i = L; i < R; ++i) {
    int a = GetValue(i);
    for (int it = 0; it < 20; ++it) {
      int b = GetValue(i);
      if (a != b) {
        qod = i;
        break;
      }
    }
    if (qod != -1) break;
    sum += a;
  }

  PutInt(0, qod);
  PutInt(0, sum);
  Send(0);

  int result = 0, target_node = -1, broken_node;
  if (!me) {
    for (int node = 0; node < nodes; ++node) {
      Receive(node);
      int x = GetInt(node);
      int sum = GetInt(node);
      if (x != -1) {
        broken_node = node;
        qod = x;
      } else {
        result += sum;
      }
    }
  }

  if (!me) {
    for (int node = 1; node < nodes; ++node) {
      if (node != broken_node && target_node == -1) {
        PutInt(node, qod);
        PutInt(node, broken_node);
        target_node = node;
      } else {
        PutInt(node, -1);
        PutInt(node, -1);
      }
      Send(node);
    }
  } else {
    Receive(0);
    qod = GetInt(0);
    broken_node = GetInt(0);
    sum = 0;
    if (qod != -1) {
      int L = 1ll * n * broken_node / nodes;
      int R = 1ll * n * (broken_node + 1) / nodes;
      for (int i = L; i < qod; ++i) sum += GetValue(i);
      for (int i = qod + 1; i < R; ++i) sum += GetValue(i);
      sum += GetValue(qod);
      PutInt(0, sum);
      Send(0);
    }
  }
  if (!me) {
    Receive(target_node);
    result += GetInt(target_node);
    printf("%d\n", result);
  }
  return 0;
}
