#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <iostream>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include "Symbol.h"

class Symbol_table {
public:
    Symbol_table() {}
    std::shared_ptr<Symbol> lookup(const std::string& name);
    bool insert(std::shared_ptr<Symbol> sym);
    friend std::ostream& operator<<(std::ostream& os, const Symbol_table& symtab);
    Symbol_table(const Symbol_table&) = delete;
    Symbol_table& operator=(const Symbol_table&) = delete;
    void erase(const std::string& name);

private:
    std::unordered_map<std::string, std::shared_ptr<Symbol>> symbols;
};

#endif