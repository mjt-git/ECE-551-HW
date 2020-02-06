#include "node.h"

void help(Node * n, BitString b, std::map<unsigned, BitString> & theMap) {
  if (n->sym != NO_SYM) {
    theMap.insert(std::pair<unsigned, BitString>(n->sym, b));
  }
  else {
    BitString leftB = b.plusZero();
    help(n->left, leftB, theMap);
    BitString rightB = b.plusOne();
    help(n->right, rightB, theMap);
  }
}

void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  help(this, b, theMap);
}
