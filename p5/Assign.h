#ifndef ASSIGN_HPP
#define ASSIGN_HPP
#include "Statement.h"
class Assign : public Statement {
  public:
    Assign(const Variable* lhs, const Expression* rhs) : lhs(lhs), rhs(rhs){}
    virtual void execute() const;
    virtual ~Assign();
  private:
    const Variable* lhs;
    const Expression* rhs;
};
#endif 