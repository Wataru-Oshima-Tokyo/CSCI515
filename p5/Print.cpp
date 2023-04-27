#include "Print.h"
#include <iostream>
#include <string>
#include "Constant.h"


void Print::execute() const {
    if (argument->type() == GPL::INT || argument->type() == GPL::DOUBLE || argument->type() == GPL::STRING){
        std::string result = argument->evaluate()->as_string();
        std::cout << "print[" << line_number << "]: " << result << std::endl;
    }

    if (next != nullptr) {
        next->execute();
    }
}

Print::~Print(){
    delete argument;
}