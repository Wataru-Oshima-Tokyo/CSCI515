
#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <iostream>
#include <string>
#include "types_and_ops.h"
#include <assert.h>

class Constant;
union symboltype{
        double *double_pointer;
        int *int_pointer;
        std::string *string_pointer;

        symboltype(){}
        symboltype(int* value): int_pointer(value){};
        symboltype(double* value): double_pointer(value){};
        symboltype(std::string* value): string_pointer(value){};
};

class Symbol {


    public:
        Symbol(const std::string& name, double* value);
        Symbol(const std::string& name, double* value, int count);
        Symbol(const std::string& name, int* value);
        Symbol(const std::string& name, int* value, int count);
        Symbol(const std::string& name, std::string* value);
        Symbol(const std::string& name, std::string* value, int count);
        // here??

        
        GPL::Type get_type() const;
        std::string get_name() const;
        virtual ~Symbol();
        friend std::ostream& operator<<(std::ostream& os, const Symbol& sym);
        Symbol(const Symbol&) = delete;
        Symbol& operator=(const Symbol&) = delete;
        int get_count() const;
        //↓here?
        const Constant* as_constant() const;          //Symbol value is not an array
        const Constant* as_constant(int index) const; //Symbol value is an array
    private:
        GPL::Type type_;
        std::string name_;
        symboltype value_;
        int count_;
};

#endif