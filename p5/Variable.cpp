#include "Variable.h"

Variable::Variable(const std::string& symbol_name)
    : symbol_name(symbol_name), array_index_expression(nullptr) {}

Variable::Variable(const std::string& symbol_name, const Expression* index_expr)
    : symbol_name(symbol_name), array_index_expression(index_expr) {}

std::string Variable::get_name() const{
    return symbol_name;
}
std::shared_ptr<Locator> Variable::modify() const {
    auto symbol_ptr = symbol();
    // return symbol_ptr->as_lvalue();
    if (symbol_name.empty()) {
        return symbol_ptr->as_lvalue();
    }
    if (array_index_expression == nullptr) {
        return symbol_ptr->as_lvalue();
    }
    int index;
    try {
        index = array_index_expression->evaluate()->as_int();
    } catch (const std::exception& e) {
        index = 0; // Set a default value for the index
    }
    
    auto array_size = symbol_ptr->get_count();
    if (index < 0 || index >= array_size) {
        Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, symbol_name, array_index_expression->evaluate()->as_string());
        return symbol_ptr->as_lvalue();
    }
    return symbol_ptr->as_lvalue(index);
}


const Constant* Variable::evaluate() const {

    if (symbol_name.empty()) {
        return ret(new Integer_constant(0));
    }
    auto symbol_ptr = symbol();
    if (array_index_expression == nullptr) {
        return ret(symbol_ptr->as_constant());
        }
    int index;
    try {
        index = array_index_expression->evaluate()->as_int();
    } catch (const std::exception& e) {
        index = 0; // Set a default value for the index
    }
    
    auto array_size = symbol_ptr->get_count();
    if (index < 0 || index >= array_size) {
        Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, symbol_name, array_index_expression->evaluate()->as_string());
        return ret(symbol_ptr->as_constant(0));
    }
    return ret(symbol_ptr->as_constant(index));
}

GPL::Type Variable::type() const {
    if (symbol_name.empty()) {
        return GPL::INT;
    }
    return symbol()->get_type();
}

Variable::~Variable() {
    delete array_index_expression;
}