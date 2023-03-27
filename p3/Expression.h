//File: Expression.h
#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "types_and_ops.h"
class Constant;
class Expression {
  public:
    Expression():evaluated_constant(nullptr) {}
    virtual const Constant* evaluate() const=0;
    virtual GPL::Type type() const=0;
    virtual ~Expression();
    Expression(const Expression&) = delete;
    Expression& operator=(const Expression&) = delete;
  protected:
    //a wrapper around returned constants
    const Constant* ret(const Constant* new_evald_constant) const;
  private:
    //pointer to evaluate()'s created constant so it can be released
    mutable const Constant* evaluated_constant;
};

class Binary_operator : public Expression {
  public:
    Binary_operator(const Expression* lhs, const Expression* rhs) :lhs(lhs), rhs(rhs) {}
    virtual const Constant* evaluate() const=0;
    virtual ~Binary_operator() { delete lhs; delete rhs; }
  protected:
    const Expression* lhs;
    const Expression* rhs;
};

class Plus : public Binary_operator {
  public:
    Plus(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class Multiply : public Binary_operator {
  public:
    Multiply(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};
#endif
