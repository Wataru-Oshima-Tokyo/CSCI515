#ifndef PRINT_HPP
#define PRINT_HPP

#include "Statement.h"


class Print : public Statement {
  public:
    Print(int line_number, const Expression* argument) : line_number(line_number), argument(argument){}
    virtual void execute() const;
    virtual ~Print();
  private:
    int line_number;
    const Expression* argument;
};

#endif