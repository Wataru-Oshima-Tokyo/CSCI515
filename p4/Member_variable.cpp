#include "Member_variable.h"

Member_variable::Member_variable(const std::string &name, const std::string &attribute_name)
    : Variable(name), attribute_name_(attribute_name) {}

Member_variable::Member_variable(const std::string &name, const Expression *index_expression, const std::string &attribute_name)
    : Variable(name, index_expression), attribute_name_(attribute_name) {}

const Constant *Member_variable::evaluate() const {
    if (attribute_name_.empty()) {
        return ret(new Integer_constant(0));
    }
    
    auto symbol_ptr = symbol();
    if (array_index_expression == nullptr) {
        try{
            return ret(symbol_ptr->as_constant(attribute_name_));
        }catch (const  std::out_of_range& e){
            Error::error(Error::UNDECLARED_MEMBER, symbol_ptr->get_name(), attribute_name_);
        }
        return ret(new Integer_constant(0));
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
        return ret(symbol_ptr->as_constant(attribute_name_));
    }
    std::cout << symbol_ptr->as_constant(index, attribute_name_)->as_string() << std::endl;
    return ret(symbol_ptr->as_constant(index, attribute_name_));
}

GPL::Type Member_variable::type() const {


    const Game_object *game_object = symbol()->as_game_object();
    if (!game_object) {
        // Error::error(Error::VARIABLE_NOT_A_GAME_OBJECT, attribute_name_);
        return type();
    }
    
    // ゲームオブジェクトの属性の型を取得
    return game_object->attribute_type(attribute_name_);
}