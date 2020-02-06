#ifndef _LL_H_
#define _LL_H_
#include <assert.h>

#include <cstdlib>
#include <exception>
#include <iostream>

//YOUR CODE GOES HERE
template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node(const T & n) : data(n), next(NULL), prev(NULL) {}
    Node(const T & n, Node * nex, Node * p) : data(n), next(nex), prev(p) {}
  };

  class exp : std::exception {
    virtual const char * what() const throw() { return "the item does not exist!"; }
  };

  Node * head;
  Node * tail;
  int size;

  Node * remove(const T & item, Node * current) {
    if (current == NULL) {
      return NULL;
    }
    if (current->data == item) {
      Node * temp = current->next;
      delete current;
      size--;
      return temp;
    }
    current->next = remove(item, current->next);
    if (current->next == NULL) {
      tail = current;
    }
    else {
      current->next->prev = current;
    }
    return current;
  }

  void swap(LinkedList & a, LinkedList & b) {
    size_t tempSize = a.size;
    a.size = b.size;
    b.size = tempSize;
    Node * aHead = a.head;
    Node * aTail = a.tail;
    a.head = b.head;
    a.tail = b.tail;
    b.head = aHead;
    b.tail = aTail;
  }

 public:
  LinkedList() : head(NULL), tail(NULL), size(0) {}
  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(rhs.size) {
    if (size > 0) {
      head = new Node(rhs.head->data, NULL, NULL);
      Node * temp = head;
      for (int i = 0; i < size - 1; i++) {
        temp->next = new Node(rhs[i + 1], NULL, temp);
        temp = temp->next;
      }
      tail = temp;
    }
  }
  LinkedList & operator=(const LinkedList & rhs) {
    /*
    if (this != rhs) {
      Node *headTemp, tailTemp;
      headTemp = new Node(rhs.head->data, NULL, NULL);
      Node * temp = headTemp;
      for (size_t i = 0; i < size - 1; i++) {
        temp->next = new Node(rhs[i + 1], NULL, temp);
        temp = temp->next;
      }
      tailTemp = temp;

      // delete current nodes
      Node * deltemp = head;
      for (size_t i = 0; i < size; i++) {
        Node * nextdel = deltemp->next;
        delete deltemp;
        deltemp = nextdel;
      }
      // assign new head, tail
      head = headTemp;
      tail = tailTemp;
      size = rhs.size;
      }*/
    LinkedList temp(rhs);
    swap(temp, *this);
    return *this;
  }

  int getSize() const { return size; }

  void addFront(const T & item) {
    if (size == 0) {
      head = new Node(item, NULL, NULL);
      tail = head;
    }
    else {
      Node * first = new Node(item, head, NULL);
      head->prev = first;
      head = first;
    }
    size++;
  }

  void addBack(const T & item) {
    if (size == 0) {
      head = new Node(item, NULL, NULL);
      tail = head;
    }
    else {
      Node * last = new Node(item, NULL, tail);
      tail->next = last;
      tail = last;
    }
    size++;
  }

  bool remove(const T & item) {
    int preSize = size;
    head = remove(item, head);
    if (size != preSize) {
      return true;
    }
    return false;
  }

  T & operator[](int index) {
    Node * item = head;
    try {
      if (size == 0 || (size > 0 && (index < 0 || index >= size))) {
        throw exp();
      }
    }
    catch (std::exception & e) {
      std::cout << e.what() << "\n";
    }
    // T & ret = head->data;
    for (int i = 0; i < size; i++) {
      if (i == index) {
        // ret = item->data;
        break;
      }
      item = item->next;
    }
    return item->data;
  }

  const T & operator[](int index) const {
    Node * item = head;
    try {
      if (size == 0 || (size > 0 && (index < 0 || index >= size))) {
        throw exp();
      }
    }
    catch (std::exception & e) {
      std::cout << e.what() << "\n";
    }
    // const T ret = head->data;
    for (int i = 0; i < size; i++) {
      if (i == index) {
        // ret = item->data;
        break;
      }
      item = item->next;
    }
    return item->data;
  }

  int find(const T & item) {
    Node * cur = head;
    for (int i = 0; i < size; i++) {
      if (cur->data == item) {
        return i;
      }
      cur = cur->next;
    }
    return -1;
  }

  ~LinkedList() {
    Node * deltemp = head;
    for (int i = 0; i < size; i++) {
      Node * nextdel = deltemp->next;
      delete deltemp;
      deltemp = nextdel;
    }
  }
};

#endif
