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
  virtual long evaluate() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
 private:
  long num;

 public:
  NumExpression(long val) : num(val) {}
  std::string toString() const { return to_string<long>(num); }
  long evaluate() const { return num; }
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
  long calc(std::string ope) const {
    if (ope == "+") {
      return leftHS->evaluate() + rightHS->evaluate();
    }
    else if (ope == "-") {
      return leftHS->evaluate() - rightHS->evaluate();
    }
    else if (ope == "*") {
      return leftHS->evaluate() * rightHS->evaluate();
    }
    else if (ope == "/") {
      return leftHS->evaluate() / rightHS->evaluate();
    }
    else {
      return 0;
    }
  }
  ~pmmd() {
    delete leftHS;
    delete rightHS;
  }
};

class PlusExpression : public Expression, public pmmd {
 private:
  std::string ope;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : pmmd(lhs, rhs), ope("+") {}
  std::string toString() const {
    return toStringLeft() + " " + ope + " " + toStringRight();
  }
  long evaluate() const { return calc(ope); }
  virtual ~PlusExpression() {}
};

class MinusExpression : public Expression, public pmmd {
 private:
  std::string ope;

 public:
  MinusExpression(Expression * lhs, Expression * rhs) : pmmd(lhs, rhs), ope("-") {}
  std::string toString() const {
    return toStringLeft() + " " + ope + " " + toStringRight();
  }
  long evaluate() const { return calc(ope); }
  virtual ~MinusExpression() {}
};

class TimesExpression : public Expression, public pmmd {
 private:
  std::string ope;

 public:
  TimesExpression(Expression * lhs, Expression * rhs) : pmmd(lhs, rhs), ope("*") {}
  std::string toString() const {
    return toStringLeft() + " " + ope + " " + toStringRight();
  }
  long evaluate() const { return calc(ope); }

  virtual ~TimesExpression() {}
};

class DivExpression : public Expression, public pmmd {
 private:
  std::string ope;

 public:
  DivExpression(Expression * lhs, Expression * rhs) : pmmd(lhs, rhs), ope("/") {}
  std::string toString() const {
    return toStringLeft() + " " + ope + " " + toStringRight();
  }
  long evaluate() const { return calc(ope); }

  virtual ~DivExpression() {}
};
