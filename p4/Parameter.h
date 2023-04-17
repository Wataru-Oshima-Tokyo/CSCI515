#include <string>
#include "Expression.h"

struct Parameter {
    std::string name;
    const Expression* value;
    Parameter* next;

    // Add a constructor to initialize 'next' to nullptr
    Parameter(const std::string& name, const Expression* value)
        : name(name), value(value), next(nullptr) {}
};