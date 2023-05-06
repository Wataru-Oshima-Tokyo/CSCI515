//File: Expression.h
#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "types_and_ops.h"
#include "Scope_manager.h"
#include "Game_object.h"
#include <memory>
class Constant;
class Expression {
  public:
    Expression():evaluated_constant(nullptr) {}
    virtual const Constant* evaluate() const=0;
    virtual GPL::Type type() const=0;
    virtual ~Expression();
    virtual std::string get_name() const;
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

class Unary_operator : public Expression {
  public:
    Unary_operator(const Expression* value) :value(value) {}
    virtual const Constant* evaluate() const=0;
    virtual ~Unary_operator() { delete value;}
  protected:
    const Expression* value;
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

class Minus : public Binary_operator {
  public:
    Minus(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class Divide : public Binary_operator {
  public:
    Divide(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class Modulus : public Binary_operator {
  public:
    Modulus(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class OR : public Binary_operator {
  public:
    OR(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class AND : public Binary_operator {
  public:
    AND(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};



class LESS : public Binary_operator {
  public:
    LESS(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};


class LESS_EQUAL : public Binary_operator {
  public:
    LESS_EQUAL(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class GREATER : public Binary_operator {
  public:
    GREATER(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class GREATER_EQUAL : public Binary_operator {
  public:
    GREATER_EQUAL(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};




class EQUAL : public Binary_operator {
  public:
    EQUAL(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class NOT_EQUAL : public Binary_operator {
  public:
    NOT_EQUAL(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};


class NEGATIVE : public Unary_operator {
  public:
    NEGATIVE(const Expression* value) : Unary_operator(value){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class NOT : public Unary_operator {
  public:
    NOT(const Expression* value) : Unary_operator(value){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};


class SIN : public Unary_operator {
  public:
    SIN(const Expression* value) : Unary_operator(value){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class COS : public Unary_operator {
  public:
    COS(const Expression* value) : Unary_operator(value){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class TAN : public Unary_operator {
  public:
    TAN(const Expression* value) : Unary_operator(value){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class ASIN : public Unary_operator {
  public:
    ASIN(const Expression* value) : Unary_operator(value){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class ACOS : public Unary_operator {
  public:
    ACOS(const Expression* value) : Unary_operator(value){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class ATAN : public Unary_operator {
  public:
    ATAN(const Expression* value) : Unary_operator(value){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};


class SQRT : public Unary_operator {
  public:
    SQRT(const Expression* value) : Unary_operator(value){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class ABS : public Unary_operator {
  public:
    ABS(const Expression* value) : Unary_operator(value){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class FLOOR : public Unary_operator {
  public:
    FLOOR(const Expression* value) : Unary_operator(value){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class RANDOM : public Unary_operator {
  public:
    RANDOM(const Expression* value) : Unary_operator(value){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};



class Near : public Binary_operator {
  public:
      Near(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
      virtual const Constant* evaluate() const;
      virtual GPL::Type type() const;
};

class Touches : public Binary_operator {
  public:
      Touches(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
      virtual const Constant* evaluate() const;
      virtual GPL::Type type() const;
};


#endif
