
#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <iostream>
#include <string>
#include "types_and_ops.h"
#include <assert.h>
class Symbol {

    public:
        Symbol(const std::string& name, double* value);
        Symbol(const std::string& name, double* value, int count);
        Symbol(const std::string& name, int* value);
        Symbol(const std::string& name, int* value, int count);
        Symbol(const std::string& name, std::string* value);
        Symbol(const std::string& name, std::string* value, int count);

        
        GPL::Type get_type() const;
        std::string get_name() const;
        virtual ~Symbol();
        friend std::ostream& operator<<(std::ostream& os, const Symbol& sym);
        Symbol(const Symbol&) = delete;
        Symbol& operator=(const Symbol&) = delete;
        void* get_value() const;
        int get_count() const;
    private:
        GPL::Type type_;
        std::string name_;
        void* value_;
        int count_;
};

#endif