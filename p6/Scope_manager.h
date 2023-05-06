#ifndef SCOPE_MANAGER_H
#define SCOPE_MANAGER_H

#include "Symbol_table.h"
#include <vector>
#include <memory>

class Scope_manager {
public:
    // Static member function for getting the singleton instance
    static Scope_manager& instance();

    // Public member functions for managing symbol tables
    void push_table();
    void pop_table();
    bool add_to_current_scope(std::shared_ptr<Symbol> sym);
    std::shared_ptr<Symbol> lookup(const std::string& name);
    bool defined_in_current_scope(const std::string& name);

    // Friend function for printing the scope manager
    friend std::ostream& operator<<(std::ostream& os, const Scope_manager& sh);

    // Prevent compiler-generated functions
    Scope_manager(const Scope_manager&) = delete;
    Scope_manager& operator=(const Scope_manager&) = delete;
    void erase(const std::string& name);
    

private:
    // Private constructor for creating the singleton
    Scope_manager();

    // Private data member for holding the symbol tables
    std::vector<std::shared_ptr<Symbol_table>> tables_;

    // Private static member variable for holding the singleton instance
    static Scope_manager* instance_;
};

#endif // SCOPE_MANAGER_H