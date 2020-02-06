#include <stdio.h>
#include <string.h>

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

template<typename T>
std::string to_string(const T & exp) {
  std::stringstream ss;
  ss << exp;
  return ss.str();
}

class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
 private:
  long num;

 public:
  NumExpression(long val) : num(val) {}
  std::string toString() const { return to_string<long>(num); }
  virtual ~NumExpression() {}
};

class pmmd {
 private:
  Expression * leftHS;
  Expression * rightHS;

 public:
  pmmd(Expression * lhs, Expression * rhs) : leftHS(lhs), rightHS(rhs) {}
  std::string toStringLeft() const { return "(" + leftHS->toString(); }
  std::string toStringRight() const { return rightHS->toString() + ")"; }

  ~pmmd() {
    delete leftHS;
    delete rightHS;
  }
};

class PlusExpression : public Expression, public pmmd {
 public:
  PlusExpression(Expression * lhs, Expression * rhs) : pmmd(lhs, rhs) {}
  std::string toString() const { return toStringLeft() + " + " + toStringRight(); }
  virtual ~PlusExpression() {}
};
