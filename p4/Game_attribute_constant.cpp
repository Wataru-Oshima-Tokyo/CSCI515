
#include "Game_attribute_constant.h"
int Game_attribute_constant::as_int() const {
    if (type() != GPL::INT)
        throw type();
    int value;
    try {
        gop->read_attribute(attribute_name, value);
    } catch (const std::out_of_range& e){
        Error::error(Error::UNDECLARED_MEMBER,attribute_name, "here");
    }
    return value;
    
}

double Game_attribute_constant::as_double() const{
    if (type() != GPL::DOUBLE)
        throw type();
    double value;
    try {
        gop->read_attribute(attribute_name, value);
    } catch (const std::out_of_range& e){
        Error::error(Error::UNDECLARED_MEMBER,attribute_name, "here");
    }
    return value;
    
}

std::string Game_attribute_constant::as_string() const {
    // if (type() != GPL::STRING)
    //     throw type();
    std::cout << "AS_STRING" << std::endl;
    std::string value;
    try {
        gop->read_attribute(attribute_name, value);
        std::cout << value << std::endl;
    } catch (const std::out_of_range& e){
        std::cout << "error" << std::endl;
        Error::error(Error::UNDECLARED_MEMBER,attribute_name, "here");
    }
    return value;
}