#include <stddef.h>

#include <exception>
#include <utility>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  template<typename k, typename v>
  class TreeNode {
   public:
    std::pair<k, v> p;
    TreeNode * left;
    TreeNode * right;
    TreeNode(std::pair<K, V> newp) : p(newp), left(NULL), right(NULL) {}
    TreeNode(std::pair<K, V> newp, TreeNode * l, TreeNode * r) :
        p(newp),
        left(l),
        right(r) {}
  };

  TreeNode<K, V> * root;
  TreeNode<K, V> * add(TreeNode<K, V> * cur, const K & key, const V & value) {
    if (cur == NULL) {
      K newKey = key;
      V newVal = value;
      std::pair<K, V> newp(newKey, newVal);
      cur = new TreeNode<K, V>(newp);
    }
    else {
      if (key == cur->p.first) {
        cur->p.second = value;
      }
      else if (key < cur->p.first) {
        cur->left = add(cur->left, key, value);
      }
      else {
        cur->right = add(cur->right, key, value);
      }
    }
    return cur;
  }

  TreeNode<K, V> * lookup(TreeNode<K, V> * cur, const K & key) const
      throw(std::invalid_argument) {
    if (cur == NULL) {
      throw std::invalid_argument("Key not found!");
    }
    else {
      if (key == cur->p.first) {
        return cur;
      }
      else if (key < cur->p.first) {
        return lookup(cur->left, key);
      }
      else {
        return lookup(cur->right, key);
      }
    }
  }

  std::pair<K, V> findReplace(TreeNode<K, V> * goal) {
    TreeNode<K, V> * rep = goal->right;
    while (rep->left != NULL) {
      rep = rep->left;
    }
    return rep->p;
  }

  TreeNode<K, V> * remove(TreeNode<K, V> * cur, const K & key) {
    if (key < cur->p.first) {
      cur->left = remove(cur->left, key);
      return cur;
    }
    else if (key > cur->p.first) {
      cur->right = remove(cur->right, key);
      return cur;
    }
    else {
      if (cur->left == NULL) {
        TreeNode<K, V> * temp = cur->right;
        delete cur;
        return temp;
      }
      else if (cur->right == NULL) {
        TreeNode<K, V> * temp = cur->left;
        delete cur;
        return temp;
      }
      else {
        std::pair<K, V> replace = findReplace(cur);
        root = remove(root, replace.first);
        cur->p = replace;
        return cur;
      }
    }
  }

  void deleteAll(TreeNode<K, V> * root) {
    if (root == NULL) {
      return;
    }
    deleteAll(root->left);
    deleteAll(root->right);
    delete root;
  }

  TreeNode<K, V> * copy(TreeNode<K, V> * cur, TreeNode<K, V> * rhsCur) {
    if (rhsCur == NULL) {
      return cur;
    }
    cur = new TreeNode<K, V>(rhsCur->p);
    cur->left = copy(cur->left, rhsCur->left);
    cur->right = copy(cur->right, rhsCur->right);
    return cur;
  }

 public:
  BstMap() : root(NULL) {}
  BstMap(const BstMap<K, V> & rhs) : root(NULL) { root = copy(root, rhs.root); }
  BstMap<K, V> & operator=(const BstMap<K, V> & rhs) {
    if (this != &rhs) {
      TreeNode<K, V> * temp = NULL;
      temp = copy(temp, rhs.root);
      deleteAll(root);
      root = temp;
    }
    return *this;
  }
  void add(const K & key, const V & value) { root = add(root, key, value); }
  const V & lookup(const K & key) const throw(std::invalid_argument) {
    TreeNode<K, V> * goal = lookup(root, key);
    return goal->p.second;
  }
  void remove(const K & key) { root = remove(root, key); }
  ~BstMap<K, V>() { deleteAll(root); }
};
