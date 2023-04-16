#include <string>
#include "Expression.h"

struct Parameter {
public:
    Parameter(const std::string& name, const Expression* value)
        : name(name), value(value), next(nullptr) {}

    std::string name;
    const Expression* value;
    Parameter* next;
};