#include "Scope_manager.h"
#include <iostream>
#include <memory>

int main() {
    // Get the singleton instance of the scope manager
    Scope_manager& symtab = Scope_manager::instance();

    // Create some symbols and add them to the current scope
    std::shared_ptr<Symbol> sym1 = std::make_shared<Symbol>("x", new double(3.14));
    std::shared_ptr<Symbol> sym2 = std::make_shared<Symbol>("y", new int(42));
    symtab.add_to_current_scope(sym1);
    symtab.add_to_current_scope(sym2);

    // Lookup a symbol in the current scope
    std::shared_ptr<Symbol> found_sym = symtab.lookup("x");
    if (found_sym != nullptr) {
        std::cout << "Found symbol: " << *found_sym << std::endl;
    } else {
        std::cout << "Symbol not found." << std::endl;
    }

    // Create a new scope and add a symbol to it
    symtab.push_table();
    std::shared_ptr<Symbol> sym3 = std::make_shared<Symbol>("x", new std::string("hello"));
    symtab.add_to_current_scope(sym3);

    // Lookup a symbol in the current scope
    found_sym = symtab.lookup("x");
    if (found_sym != nullptr) {
        std::cout << "Found symbol: " << *found_sym << std::endl;
    } else {
        std::cout << "Symbol not found." << std::endl;
    }

    // Check if a symbol is defined in the current scope
    bool defined = symtab.defined_in_current_scope("y");
    if (defined) {
        std::cout << "Symbol y is defined in the current scope." << std::endl;
    } else {
        std::cout << "Symbol y is not defined in the current scope." << std::endl;
    }

    // Remove the current scope
    symtab.pop_table();

    // Lookup a symbol in the current scope
    found_sym = symtab.lookup("x");
    if (found_sym != nullptr) {
        std::cout << "Found symbol: " << *found_sym << std::endl;
    } else {
        std::cout << "Symbol not found." << std::endl;
    }

    return 0;
}