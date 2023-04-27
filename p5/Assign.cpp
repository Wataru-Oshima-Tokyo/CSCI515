#include "Assign.h"
#include "Variable.h"
#include "Expression.h"
#include "Locator.h"
#include "Constant.h"
#include "errno.h"
Assign::~Assign() {
    delete lhs;
    delete rhs;
}

void Assign::execute() const {
    std::shared_ptr<Locator> lvalue = lhs->modify();
    const Constant* rvalue = rhs->evaluate();
    switch (lvalue->type()) {
        case GPL::INT:
            lvalue->mutate(rvalue->as_int());
            break;
        case GPL::DOUBLE:
            lvalue->mutate(rvalue->as_double());
            break;
        case GPL::STRING:
            lvalue->mutate(rvalue->as_string());
            break;
        default:
            throw lvalue->type();
            break;
    }
    if (next != nullptr) {
        next->execute();
    }
}