#include "Assign.h"
#include "Variable.h"
#include "Expression.h"
#include "Locator.h"
#include "Constant.h"
#include "errno.h"
Assign::~Assign() {
    if (owns_expressions) {
        delete lhs;
        delete rhs;
    }
}

void Assign::execute() const {
    std::shared_ptr<Locator> lvalue = lhs->modify();
    const Constant* rvalue;
    try{
        rvalue = rhs->evaluate();
    }catch(...){
    std::cout << "An exception occurred" << std::endl;
        rvalue = lhs->evaluate();
    }
    
    switch (lvalue->type()) {
        case GPL::INT:
            lvalue->mutate(rvalue->as_int());
            break;
        case GPL::DOUBLE:
            try{
                lvalue->mutate(rvalue->as_double());
            }catch(GPL::Type errorneous_type){
                if (rvalue->type() == GPL::INT) {
                    lvalue->mutate(double(static_cast<double>(rvalue->as_int())));
                    std::cout << "ASSIGN TYPE CASTED INT"<< std::endl;
                }else{
                    lvalue->mutate(0.0);
                    std::cout << "ASSIGN ZERO"<< std::endl;
                }
            }
            
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