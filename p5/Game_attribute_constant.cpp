
#include "Game_attribute_constant.h"
int Game_attribute_constant::as_int() const {
    // if (type() != GPL::INT)
    //     throw type();
    int value;
    try {
        gop->read_attribute(attribute_name, value);
    } catch (const std::out_of_range& e){
        Error::error(Error::UNDECLARED_MEMBER,attribute_name, "here");
    }
    return value;
    
}

double Game_attribute_constant::as_double() const{
    // if (type() != GPL::DOUBLE)
    //     throw type();
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




    std::string value;
    try {
        if (type() == GPL::INT){
            int _value;
            gop->read_attribute(attribute_name, _value);
            value = std::to_string(_value);
        }else if (type() == GPL::DOUBLE){
            double _value;
            gop->read_attribute(attribute_name, _value);
            value = std::to_string(_value);
        }else{
            gop->read_attribute(attribute_name, value);
        }
        // std::cout << type() << std::endl;
        
        // std::cout << attribute_name << std::endl;




        
    } catch (const std::out_of_range& e){
        Error::error(Error::UNDECLARED_MEMBER,attribute_name, "here");
    }
    return value;
}