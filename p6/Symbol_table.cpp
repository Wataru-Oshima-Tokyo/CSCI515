#include "Symbol_table.h"

std::shared_ptr<Symbol> Symbol_table::lookup(const std::string& name) {
    auto iter = symbols.find(name);
    if (iter == symbols.end()) {
        return nullptr;
    }
    else {
        return iter->second;
    }
}

bool Symbol_table::insert(std::shared_ptr<Symbol> sym) {
    auto result = symbols.emplace(sym->get_name(), sym);
    return result.second;
}

std::ostream& operator<<(std::ostream& os, const Symbol_table& symtab) {
    std::vector<std::shared_ptr<Symbol>> sorted_symbols;
    for (auto& entry : symtab.symbols) {
        sorted_symbols.push_back(entry.second);
    }
    std::sort(sorted_symbols.begin(), sorted_symbols.end(), [](std::shared_ptr<Symbol> a, std::shared_ptr<Symbol> b) {
        return a->get_name() < b->get_name();
    });
    for (auto& sym : sorted_symbols) {
        os << *sym;
    }
    return os;
}

void Symbol_table::erase(const std::string& name) {
    symbols.erase(name);
}
