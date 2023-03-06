#include "Scope_manager.h"
#include <stdexcept>

// Static member variable definition
Scope_manager* Scope_manager::instance_ = nullptr;

// Constructor
Scope_manager::Scope_manager() {
    // Create a new symbol table and push it onto the back of the vector
    tables_.push_back(std::make_shared<Symbol_table>());
}

// Static member function for getting the singleton instance
Scope_manager& Scope_manager::instance() {
    if (instance_ == nullptr) {
        instance_ = new Scope_manager;
    }
    return *instance_;
}

// Public member function for creating a new symbol table
void Scope_manager::push_table() {
    tables_.push_back(std::make_shared<Symbol_table>());
}

// Public member function for removing the last symbol table
void Scope_manager::pop_table() {
    if (tables_.size() == 1) {
        throw std::underflow_error("Can't pop global symbol table");
    }
    tables_.pop_back();
}

// Public member function for adding a symbol to the current scope
bool Scope_manager::add_to_current_scope(std::shared_ptr<Symbol> sym) {
    return tables_.back()->insert(sym);
}

// Public member function for looking up a symbol
std::shared_ptr<Symbol> Scope_manager::lookup(const std::string& name) {
    for (auto it = tables_.rbegin(); it != tables_.rend(); ++it) {
        auto sym = (*it)->lookup(name);
        if (sym != nullptr) {
            return sym;
        }
    }
    return nullptr;
}

// Public member function for checking if a symbol is defined in the current scope
bool Scope_manager::defined_in_current_scope(const std::string& name) {
    auto sym = tables_.back()->lookup(name);
    return (sym != nullptr);
}

// Friend function for printing the scope manager
std::ostream& operator<<(std::ostream& os, const Scope_manager& sh) {
    for (auto it = sh.tables_.rbegin(); it != sh.tables_.rend(); ++it) {
        // os << "Symbol table: " << std::distance(it, sh.tables_.rend()) << std::endl;
        // os << **it << std::endl;
    }
    return os;
}