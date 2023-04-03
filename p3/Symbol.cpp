#include "Symbol.h"
#include "Constant.h"

Symbol::Symbol(const std::string& name, double* value) : 
    type_{ GPL::Type::DOUBLE }, name_{ name }, value_{ symboltype(value) }, count_{ 0 } {}

Symbol::Symbol(const std::string& name, double* value, int count) :
    type_{ GPL::Type::DOUBLE }, name_{ name }, value_{ symboltype(value) }, count_{ count } {}

Symbol::Symbol(const std::string& name, int* value) :
    type_{ GPL::Type::INT }, name_{ name }, value_{ symboltype(value)  }, count_{ 0 } {}

Symbol::Symbol(const std::string& name, int* value, int count) :
    type_{ GPL::Type::INT }, name_{ name }, value_{ symboltype(value)  }, count_{ count } {}

Symbol::Symbol(const std::string& name, std::string* value) :
    type_{ GPL::Type::STRING }, name_{ name }, value_{ symboltype(value) }, count_{ 0 } {}

Symbol::Symbol(const std::string& name, std::string* value, int count) :
    type_{ GPL::Type::STRING }, name_{ name }, value_{ symboltype(value)  }, count_{ count } {}

GPL::Type Symbol::get_type() const {
    return type_;
}

std::string Symbol::get_name() const {
    return name_;
}

int Symbol::get_count() const{
    return count_;
}

Symbol::~Symbol() {
    switch (type_) {
        case GPL::Type::DOUBLE:
            if (count_ == 0) {
                delete value_.double_pointer;
            }
            else {
                delete[] value_.double_pointer;
            }
            break;
        case GPL::Type::INT:
            if (count_ == 0) {
                delete value_.int_pointer;
            }
            else {
                delete[] value_.int_pointer;
            }
            break;
        case GPL::Type::STRING:
            if (count_ == 0) {
                delete value_.string_pointer;
            }
            else {
                delete[] value_.string_pointer;
            }
            break;
        default:
         assert(false);
            break;
    }
}

std::ostream& operator<<(std::ostream& os, const Symbol& sym) {
    switch (sym.get_type()) {

    
        case GPL::Type::DOUBLE: {
            
            if (sym.count_ == 0) {
                os << "double " << sym.get_name() << " = ";
                os << *sym.value_.double_pointer;
            }
            else {
                for (int i = 0; i < sym.count_; ++i) {
                    os << "double "  << sym.get_name() << "[" << i << "]" <<" = "
                    << sym.value_.double_pointer[i];
                    if (i != sym.count_-1){
                        os <<std::endl;
                    }
                }
            }
            break;
        }
        case GPL::Type::INT: {
            
            if (sym.count_ == 0) {
                os << "int " << sym.get_name() << " = ";
                os << *sym.value_.int_pointer;
            }
            else {

                for (int i = 0; i < sym.count_; ++i) {
                    os << "int "  << sym.get_name() << "[" << i << "]" <<" = "
                    << sym.value_.int_pointer[i];
                    if (i != sym.count_-1){
                        os <<std::endl;
                    }
                }
            }
            break;
        }
        case GPL::Type::STRING: {
            
            if (sym.count_ == 0) {
                os << "string " << sym.get_name();
                os << " = " << "\"";
                os << *sym.value_.string_pointer << "\"";
            }
            else {
                for (int i = 0; i < sym.count_; ++i) {
                    os << "string "  << sym.get_name() << "[" << i << "]" <<" = "
                    << "\"" <<sym.value_.string_pointer[i] << "\"";
                    if (i != sym.count_-1){
                        os <<std::endl;
                    }
                }
            }
            break;
        }



    default:
        assert(false);
        break;
    }
    
    os << std::endl;
    return os;
}
const Constant* Symbol::as_constant() const {
    switch (type_) {
        case GPL::Type::INT:
            return new Integer_constant(*value_.int_pointer);
        case GPL::Type::DOUBLE:
            return new Double_constant(*value_.double_pointer);
        case GPL::Type::STRING:
            return new String_constant(*value_.string_pointer);
        default:
            throw type_;
    }
}

const Constant* Symbol::as_constant(int index) const {
    if (index < 0 || index >= count_) {
        return nullptr;
    }
    //ToDo: I need to change for array
    switch (type_) {
        case GPL::Type::INT:
            return new Integer_constant(*value_.int_pointer);
        case GPL::Type::DOUBLE:
            return new Double_constant(*value_.double_pointer);
        case GPL::Type::STRING:
            return new String_constant(*value_.string_pointer);
        default:
            throw type_;
    }
}

