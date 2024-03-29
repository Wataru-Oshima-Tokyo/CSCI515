
#ifndef VARIABLE_H
#define VARIABLE_H

#include <cassert>
#include <iostream>
#include <memory>
#include <string>

#include "Constant.h"
#include "Scope_manager.h"
#include "Symbol.h"
#include "error.h"
#include "types_and_ops.h"

class Variable : public Expression {
  public:
    // initialize unused array_index_expression to nullptr
    Variable(const std::string& symbol_name);

    // initialize array_index_expression to index_expr
    Variable(const std::string& symbol_name, const Expression* index_expr);

    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
    virtual ~Variable();

    Variable(const Variable&) = delete;
    Variable& operator=(const Variable&) = delete;
  protected: //allow derived class access

    std::string symbol_name;
    const Expression* array_index_expression;

    //The symbol() function eases access to the symbol
    //use it within Variable's member functions
    std::shared_ptr<Symbol> symbol()
    { return Scope_manager::instance().lookup(symbol_name); }
    std::shared_ptr<Symbol> symbol() const
    { return Scope_manager::instance().lookup(symbol_name); }
};

#endif 