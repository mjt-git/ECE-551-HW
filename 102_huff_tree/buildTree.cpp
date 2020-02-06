#include "node.h"

Node * buildTree(uint64_t * counts) {
  priority_queue_t pq;

  for (int i = 0; i < 257; i++) {
    if (counts[i] > 0) {
      pq.push(new Node(i, counts[i]));
    }
  }
  while (pq.size() > 1) {
    Node * n1 = pq.top();
    pq.pop();
    Node * n2 = pq.top();
    pq.pop();
    Node * dad = new Node(n1, n2);
    pq.push(dad);
  }
  return pq.top();
}
