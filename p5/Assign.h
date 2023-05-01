#ifndef ASSIGN_HPP
#define ASSIGN_HPP
#include "Statement.h"
#include <iostream>
class Assign : public Statement {
  public:
    Assign(const Variable* lhs, const Expression* rhs, bool owns_expressions) : lhs(lhs), rhs(rhs), owns_expressions(owns_expressions) {}
    virtual void execute() const;
    virtual ~Assign();
  private:
    const Variable* lhs;
    const Expression* rhs;
    bool owns_expressions;
};
#endif 