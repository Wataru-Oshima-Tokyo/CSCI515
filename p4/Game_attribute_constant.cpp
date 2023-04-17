
#include "Game_attribute_constant.h"
int Game_attribute_constant::as_int() const {
    if (type() != GPL::INT)
        throw type();
    int value;
    try {
        gop->read_attribute(attribute_name, value);
    } catch (const std::out_of_range& e){
        // throw Error::error(Error::ATTRIBUTE_NOT_FOUND, attribute_name);
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
        // throw Error::error(Error::ATTRIBUTE_NOT_FOUND, attribute_name);
    }
    return value;
    
}

std::string Game_attribute_constant::as_string() const {
    if (type() != GPL::STRING)
        throw type();
    std::string value;
    try {
        gop->read_attribute(attribute_name, value);
    } catch (const std::out_of_range& e){
        // throw Error::error(Error::ATTRIBUTE_NOT_FOUND, attribute_name);
    }
    return value;
}