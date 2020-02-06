#include "set.h"

template<typename T>
class BstSet : public Set<T> {
 private:
  template<typename t>
  class TreeNode {
   public:
    t val;
    TreeNode * left;
    TreeNode * right;
    TreeNode(t newVal) : val(newVal), left(NULL), right(NULL) {}
    TreeNode(t newVal, TreeNode * l, TreeNode * r) : val(newVal), left(l), right(r) {}
  };

  TreeNode<T> * root;
  TreeNode<T> * add(TreeNode<T> * cur, const T & key) {
    if (cur == NULL) {
      T newKey = key;
      cur = new TreeNode<T>(newKey);
    }
    else {
      if (key == cur->val) {
        return cur;
      }
      else if (key < cur->val) {
        cur->left = add(cur->left, key);
      }
      else {
        cur->right = add(cur->right, key);
      }
    }
    return cur;
  }

  bool lookup(TreeNode<T> * cur, const T & key) const {
    if (cur == NULL) {
      return false;
    }
    else {
      if (key == cur->val) {
        return true;
      }
      else if (key < cur->val) {
        return lookup(cur->left, key);
      }
      else {
        return lookup(cur->right, key);
      }
    }
  }

  T findReplace(TreeNode<T> * goal) {
    TreeNode<T> * rep = goal->right;
    while (rep->left != NULL) {
      rep = rep->left;
    }
    return rep->val;
  }

  TreeNode<T> * remove(TreeNode<T> * cur, const T & key) {
    if (key < cur->val) {
      cur->left = remove(cur->left, key);
      return cur;
    }
    else if (key > cur->val) {
      cur->right = remove(cur->right, key);
      return cur;
    }
    else {
      if (cur->left == NULL) {
        TreeNode<T> * temp = cur->right;
        delete cur;
        return temp;
      }
      else if (cur->right == NULL) {
        TreeNode<T> * temp = cur->left;
        delete cur;
        return temp;
      }
      else {
        T replace = findReplace(cur);
        root = remove(root, replace);
        cur->val = replace;
        return cur;
      }
    }
  }

  void deleteAll(TreeNode<T> * root) {
    if (root == NULL) {
      return;
    }
    deleteAll(root->left);
    deleteAll(root->right);
    delete root;
  }

  TreeNode<T> * copy(TreeNode<T> * cur, TreeNode<T> * rhsCur) {
    if (rhsCur == NULL) {
      return cur;
    }
    cur = new TreeNode<T>(rhsCur->val);
    cur->left = copy(cur->left, rhsCur->left);
    cur->right = copy(cur->right, rhsCur->right);
    return cur;
  }

 public:
  BstSet() : root(NULL) {}
  BstSet(const BstSet & rhs) : root(NULL) { root = copy(root, rhs.root); }
  BstSet<T> & operator=(const BstSet & rhs) {
    if (this != &rhs) {
      TreeNode<T> * temp = NULL;
      temp = copy(temp, rhs.root);
      deleteAll(root);
      root = temp;
    }
    return *this;
  }
  void add(const T & key) { root = add(root, key); }
  bool contains(const T & key) const { return lookup(root, key); }
  void remove(const T & key) { root = remove(root, key); }
  ~BstSet<T>() { deleteAll(root); }
};
