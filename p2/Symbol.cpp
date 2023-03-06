#include "Symbol.h"
   
Symbol::Symbol(const std::string& name, double* value) : 
    type_{ GPL::Type::DOUBLE }, name_{ name }, value_{ value }, count_{ 1 } {}

Symbol::Symbol(const std::string& name, double* value, int count) :
    type_{ GPL::Type::DOUBLE }, name_{ name }, value_{ value }, count_{ count } {}

Symbol::Symbol(const std::string& name, int* value) :
    type_{ GPL::Type::INT }, name_{ name }, value_{ value }, count_{ 1 } {}

Symbol::Symbol(const std::string& name, int* value, int count) :
    type_{ GPL::Type::INT }, name_{ name }, value_{ value }, count_{ count } {}

Symbol::Symbol(const std::string& name, std::string* value) :
    type_{ GPL::Type::STRING }, name_{ name }, value_{ value }, count_{ 1 } {}

Symbol::Symbol(const std::string& name, std::string* value, int count) :
    type_{ GPL::Type::STRING }, name_{ name }, value_{ value }, count_{ count } {}

GPL::Type Symbol::get_type() const {
    return type_;
}

std::string Symbol::get_name() const {
    return name_;
}

void* Symbol::get_value() const {
    return value_;
}

int Symbol::get_count() const{
    return count_;
}

Symbol::~Symbol() {
    switch (type_) {
        case GPL::Type::DOUBLE:
            if (count_ == 1) {
                delete static_cast<double*>(value_);
            }
            else {
                delete[] static_cast<double*>(value_);
            }
            break;
        case GPL::Type::INT:
            if (count_ == 1) {
                delete static_cast<int*>(value_);
            }
            else {
                delete[] static_cast<int*>(value_);
            }
            break;
        case GPL::Type::STRING:
            if (count_ == 1) {
                delete static_cast<std::string*>(value_);
            }
            else {
                delete[] static_cast<std::string*>(value_);
            }
            break;
        default:
            break;
    }
}

std::ostream& operator<<(std::ostream& os, const Symbol& sym) {
    os << ((sym.get_type() == GPL::Type::DOUBLE) ? "double" : "") << " "
        << sym.get_name() << " = ";
    switch (sym.get_type()) {
    case GPL::Type::DOUBLE: {
        double* value = static_cast<double*>(sym.value_);
        if (sym.count_ == 1) {
            os << *value;
        }
        else {
            os << "[";
            for (int i = 0; i < sym.count_; ++i) {
                os << value[i];
                if (i != sym.count_ - 1) {
                    os << ", ";
                }
            }
            os << "]";
        }
        break;
    }
    default:
        assert(false);
        break;
    }
    return os;
}