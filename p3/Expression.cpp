// File: Expression.cpp
#include "Expression.h"
#include "Constant.h"
#include "error.h"
#include <string>
#include <cmath>
#include <iostream>
#include <numbers>
#include <ctime>
using std::string;

Expression::~Expression(){delete evaluated_constant;}

// This wrapper ensures that Constant objects created by evaluate() are
// properly released when a subsequent call to evaluate() will otherwise
// overwrite the pointer.
const Constant* Expression::ret(const Constant* new_evald_constant) const
{
  delete evaluated_constant;
  return evaluated_constant=new_evald_constant;
}
/**********************************************/
/************* Other operators ****************/
/**********************************************/

const Constant* Plus::evaluate() const
{
  GPL::Type lht=lhs->type();
  GPL::Type rht=rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lht==GPL::STRING || rht==GPL::STRING)
    return ret(new String_constant(lhs_constant->as_string() + //<--addition
                                   rhs_constant->as_string()));
  if(lht==GPL::DOUBLE || rht==GPL::DOUBLE)
    return ret(new Double_constant(lhs_constant->as_double() + //<--addition
                                   rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() +     //<--addition
                                  rhs_constant->as_int()));
}

GPL::Type Plus::type() const
{
  GPL::Type lht=lhs->type();
  GPL::Type rht=rhs->type();
  if(lht==GPL::STRING || rht==GPL::STRING)
    return GPL::STRING;
  if(lht==GPL::DOUBLE || rht==GPL::DOUBLE)
    return GPL::DOUBLE;
  return GPL::INT;
}

const Constant* Multiply::evaluate() const
{
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if (lhs->type()==GPL::STRING){
    Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "*");
  }
  if (rhs->type()==GPL::STRING){
    Error::error(Error::INVALID_RIGHT_OPERAND_TYPE,  "*");
  }

  if (lhs->type()==GPL::STRING || rhs->type()==GPL::STRING)
    return ret(new Integer_constant(0 * 0));

  if(lhs->type()==GPL::DOUBLE && rhs->type()==GPL::DOUBLE)
    return ret(new Double_constant(std::ceil(lhs_constant->as_double() * //<--multiply
                                   rhs_constant->as_double()*100000)/100000));


  if(lhs->type()==GPL::DOUBLE || rhs->type()==GPL::DOUBLE)
    return ret(new Double_constant(std::round(lhs_constant->as_double() * //<--multiply
                                   rhs_constant->as_double()*10)/10));
  return ret(new Integer_constant(lhs_constant->as_int() *     //<--multiply
                                  rhs_constant->as_int()));
}

GPL::Type Multiply::type() const
{
  GPL::Type lht=lhs->type();
  GPL::Type rht=rhs->type();
  if(lht==GPL::DOUBLE || rht==GPL::DOUBLE)
    return GPL::DOUBLE;
  return GPL::INT;
}

const Constant* Minus::evaluate() const
{
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if (lhs->type()==GPL::STRING){
    Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "-");
  }
  if (rhs->type()==GPL::STRING){
    Error::error(Error::INVALID_RIGHT_OPERAND_TYPE,  "-");
  }

  if (lhs->type()==GPL::STRING || rhs->type()==GPL::STRING)
    return ret(new Integer_constant(0 * 0));

  if(lhs->type()==GPL::DOUBLE || rhs->type()==GPL::DOUBLE)
    return ret(new Double_constant(lhs_constant->as_double() - //<--minus
                                   rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() -     //<--minus
                                  rhs_constant->as_int()));
}

GPL::Type Minus::type() const
{
  GPL::Type lht=lhs->type();
  GPL::Type rht=rhs->type();
  if(lht==GPL::DOUBLE || rht==GPL::DOUBLE)
    return GPL::DOUBLE;
  return GPL::INT;
}

const Constant* Divide::evaluate() const
{
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if (lhs->type()==GPL::STRING){
    Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "/");
  }
  if (rhs->type()==GPL::STRING){
    Error::error(Error::INVALID_RIGHT_OPERAND_TYPE,  "/");
  }

  if (lhs->type()==GPL::STRING || rhs->type()==GPL::STRING)
    return ret(new Integer_constant(0 * 0));


  if(lhs->type()==GPL::DOUBLE && rhs->type()==GPL::DOUBLE)
    return ret(new Double_constant(std::floor(lhs_constant->as_double() / //<--divide
                                   rhs_constant->as_double()*1000000)/1000000));

  if(lhs->type()==GPL::DOUBLE || rhs->type()==GPL::DOUBLE)
    return ret(new Double_constant(lhs_constant->as_double() / //<--divide
                                   rhs_constant->as_double()));

  return ret(new Integer_constant(lhs_constant->as_int() /     //<--divide
                                  rhs_constant->as_int()));
}

GPL::Type Divide::type() const
{
  GPL::Type lht=lhs->type();
  GPL::Type rht=rhs->type();
  if(lht==GPL::DOUBLE || rht==GPL::DOUBLE)
    return GPL::DOUBLE;
  return GPL::INT;
}

const Constant* Modulus::evaluate() const
{
  const Constant* lhs_constant = lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();
  if (lhs->type() == GPL::STRING || lhs->type() == GPL::DOUBLE) {
    Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "%");
  }
  if (rhs->type() == GPL::STRING || rhs->type() == GPL::DOUBLE) {
    Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "%");
  }

  if (lhs->type() == GPL::STRING || rhs->type() == GPL::STRING || lhs->type() == GPL::DOUBLE || rhs->type() == GPL::DOUBLE )
    return ret(new Integer_constant(0 * 0));

  return ret(new Integer_constant(lhs_constant->as_int() % rhs_constant->as_int()));
}

GPL::Type Modulus::type() const
{
  GPL::Type lht = lhs->type();
  GPL::Type rht = rhs->type();
  if (lht == GPL::DOUBLE || rht == GPL::DOUBLE)
    return GPL::DOUBLE;
  return GPL::INT;
}


const Constant* OR::evaluate() const
{
  const Constant* lhs_constant = lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();
  if (lhs->type() == GPL::STRING) {
    Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "||");
  }
  if (rhs->type() == GPL::STRING) {
    Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "||");
  }

  if (lhs->type() == GPL::STRING || rhs->type() == GPL::STRING){
    return ret(new Integer_constant(0 * 0));
  }
    

  if(lhs->type()==GPL::DOUBLE || rhs->type()==GPL::DOUBLE) {
        return ret(new Integer_constant(lhs_constant->as_double() || //<--or
                                   rhs_constant->as_double()));
  }

  return ret(new Integer_constant(lhs_constant->as_int() ||     //<--or
                                  rhs_constant->as_int()));
}

GPL::Type OR::type() const
{
  GPL::Type lht = lhs->type();
  GPL::Type rht = rhs->type();
  if (lht == GPL::DOUBLE || rht == GPL::DOUBLE)
    return GPL::DOUBLE;
  return GPL::INT;
}

const Constant* AND::evaluate() const
{
  const Constant* lhs_constant = lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();
  // if (lhs->type() == GPL::STRING) {
  //   Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "&&");
  // }
  // if (rhs->type() == GPL::STRING) {
  //   Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "&&");
  // }

  if (lhs->type() == GPL::STRING || rhs->type() == GPL::STRING){
            return ret(new Integer_constant(lhs_constant->as_double() &&
                                   rhs_constant->as_double()));
  }
    

  if(lhs->type()==GPL::DOUBLE || rhs->type()==GPL::DOUBLE) {
        return ret(new Integer_constant(lhs_constant->as_double() &&
                                   rhs_constant->as_double()));
  }

  return ret(new Integer_constant(lhs_constant->as_double() &&     
                                  rhs_constant->as_double()));
}

GPL::Type AND::type() const
{
  GPL::Type lht = lhs->type();
  GPL::Type rht = rhs->type();
  if (lht == GPL::DOUBLE || rht == GPL::DOUBLE)
    return GPL::DOUBLE;
  return GPL::INT;
}

const Constant* LESS::evaluate() const
{
  const Constant* lhs_constant = lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();

      
  if(lhs->type()==GPL::STRING || rhs->type()==GPL::STRING) {
        return ret(new Integer_constant(lhs_constant->as_string() < 
                                   rhs_constant->as_string()));
  }


  if(lhs->type()==GPL::DOUBLE || rhs->type()==GPL::DOUBLE) {
        return ret(new Integer_constant(lhs_constant->as_double() < 
                                   rhs_constant->as_double()));
  }

  return ret(new Integer_constant(lhs_constant->as_int() <    
                                  rhs_constant->as_int()));
}

GPL::Type LESS::type() const
{
  GPL::Type lht = lhs->type();
  GPL::Type rht = rhs->type();
  if (lht == GPL::DOUBLE || rht == GPL::DOUBLE)
    return GPL::DOUBLE;
  return GPL::INT;
}


const Constant* LESS_EQUAL::evaluate() const
{
  const Constant* lhs_constant = lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();

  if(lhs->type()==GPL::STRING || rhs->type()==GPL::STRING) {
        return ret(new Integer_constant(lhs_constant->as_string() <= //<--or
                                   rhs_constant->as_string()));
  }    

  if(lhs->type()==GPL::DOUBLE || rhs->type()==GPL::DOUBLE) {
        return ret(new Integer_constant(lhs_constant->as_double() <= //<--or
                                   rhs_constant->as_double()));
  }

  return ret(new Integer_constant(lhs_constant->as_int() <=    //<--or
                                  rhs_constant->as_int()));
}

GPL::Type LESS_EQUAL::type() const
{
  GPL::Type lht = lhs->type();
  GPL::Type rht = rhs->type();
  if (lht == GPL::DOUBLE || rht == GPL::DOUBLE)
    return GPL::DOUBLE;
  return GPL::INT;
}



const Constant* GREATER::evaluate() const
{
  const Constant* lhs_constant = lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();

  if(lhs->type()==GPL::STRING || rhs->type()==GPL::STRING) {
        return ret(new Integer_constant(lhs_constant->as_string() > //<--or
                                   rhs_constant->as_string()));
  }

  if(lhs->type()==GPL::DOUBLE || rhs->type()==GPL::DOUBLE) {
        return ret(new Integer_constant(lhs_constant->as_double() > //<--or
                                   rhs_constant->as_double()));
  }

  return ret(new Integer_constant(lhs_constant->as_int() >    //<--or
                                  rhs_constant->as_int()));
}

GPL::Type GREATER::type() const
{
  GPL::Type lht = lhs->type();
  GPL::Type rht = rhs->type();
  if (lht == GPL::DOUBLE || rht == GPL::DOUBLE)
    return GPL::DOUBLE;
  return GPL::INT;
}


const Constant* GREATER_EQUAL::evaluate() const
{
  const Constant* lhs_constant = lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();

  if(lhs->type()==GPL::STRING || rhs->type()==GPL::STRING) {
        return ret(new Integer_constant(lhs_constant->as_string() >= //<--or
                                   rhs_constant->as_string()));
  }
  if(lhs->type()==GPL::DOUBLE || rhs->type()==GPL::DOUBLE) {
        return ret(new Integer_constant(lhs_constant->as_double() >= //<--or
                                   rhs_constant->as_double()));
  }

  return ret(new Integer_constant(lhs_constant->as_int() >=    //<--or
                                  rhs_constant->as_int()));
}

GPL::Type GREATER_EQUAL::type() const
{
  GPL::Type lht = lhs->type();
  GPL::Type rht = rhs->type();
  if (lht == GPL::DOUBLE || rht == GPL::DOUBLE)
    return GPL::DOUBLE;
  return GPL::INT;
}


const Constant* EQUAL::evaluate() const
{
  const Constant* lhs_constant = lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();

    
  if(lhs->type()==GPL::STRING || rhs->type()==GPL::STRING) {
        return ret(new Integer_constant(lhs_constant->as_string() == //equal
                                   rhs_constant->as_string()));
  }
  if(lhs->type()==GPL::DOUBLE && rhs->type()==GPL::DOUBLE) {
        std::cout << "lhs:" << lhs_constant->as_double()
        << " rhs: " << rhs_constant->as_double()
        <<std::endl;
        return ret(new Integer_constant(lhs_constant->as_double() == 
                                   rhs_constant->as_double()));
  }
  if(lhs->type()==GPL::INT && rhs->type()==GPL::INT) {
        std::cout << "lhs:" << lhs_constant->as_double()
        << " rhs: " << rhs_constant->as_double()
        <<std::endl;
    return ret(new Integer_constant(lhs_constant->as_int() ==    
                                  rhs_constant->as_int()));
  }
  return ret(new Integer_constant(0));
}

GPL::Type EQUAL::type() const
{
  GPL::Type lht = lhs->type();
  GPL::Type rht = rhs->type();
  if (lht == GPL::DOUBLE || rht == GPL::DOUBLE)
    return GPL::DOUBLE;
  return GPL::INT;
}


const Constant* NOT_EQUAL::evaluate() const
{
  const Constant* lhs_constant = lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();

  if(lhs->type()==GPL::STRING || rhs->type()==GPL::STRING) {
        return ret(new Integer_constant(lhs_constant->as_string() != //<--or
                                   rhs_constant->as_string()));
  }
  if(lhs->type()==GPL::DOUBLE || rhs->type()==GPL::DOUBLE) {
        return ret(new Integer_constant(lhs_constant->as_double() != //<--or
                                   rhs_constant->as_double()));
  }

  return ret(new Integer_constant(lhs_constant->as_int() !=    //<--or
                                  rhs_constant->as_int()));
}

GPL::Type NOT_EQUAL::type() const
{
  GPL::Type lht = lhs->type();
  GPL::Type rht = rhs->type();
  if (lht == GPL::DOUBLE || rht == GPL::DOUBLE)
    return GPL::DOUBLE;
  return GPL::INT;
}


const Constant* NEGATIVE::evaluate() const
{
  // const Constant* lhs_constant = lhs->evaluate();
  const Constant* value_constant = value->evaluate();

  if (value->type() == GPL::STRING) {
    Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "-");
    return ret(new Integer_constant(0 * 0));
  }

  if(value->type()==GPL::DOUBLE) {
        return ret(new Double_constant(-1 *value_constant->as_double()));
  }

  return ret(new Integer_constant(-1 * value_constant->as_int()));
}

GPL::Type NEGATIVE::type() const
{
  return value->type();
}


const Constant* NOT::evaluate() const
{
  // const Constant* lhs_constant = lhs->evaluate();
  const Constant* value_constant = value->evaluate();

  if (value->type() == GPL::STRING) {
    Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "!");
    return ret(new Integer_constant(0 * 0));
  }

  if(value->type()==GPL::DOUBLE) {
        return ret(new Integer_constant(!value_constant->as_double()));
  }

  return ret(new Integer_constant(!value_constant->as_int()));
}

GPL::Type NOT::type() const
{
  return value->type();
}

const Constant* SIN::evaluate() const
{
  // const Constant* lhs_constant = lhs->evaluate();
  const Constant* value_constant = value->evaluate();

  if (value->type() == GPL::STRING) {
    Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "sin");
    return ret(new Integer_constant(0 * 0));
  }

  return ret(new Double_constant(std::sin(value_constant->as_double() * (std::numbers::pi / 180))));

}

GPL::Type SIN::type() const
{
  return value->type();
}

const Constant* COS::evaluate() const
{
  // const Constant* lhs_constant = lhs->evaluate();
  const Constant* value_constant = value->evaluate();

  if (value->type() == GPL::STRING) {
    Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "cos");
    return ret(new Integer_constant(0 * 0));
  }

  return ret(new Double_constant(std::cos(value_constant->as_double()* (std::numbers::pi / 180))));
}

GPL::Type COS::type() const
{
  return value->type();
}

const Constant* TAN::evaluate() const
{
  // const Constant* lhs_constant = lhs->evaluate();
  const Constant* value_constant = value->evaluate();

  if (value->type() == GPL::STRING) {
    Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "tan");
    return ret(new Integer_constant(0 * 0));
  }


  return ret(new Double_constant(std::tan(value_constant->as_double()* (std::numbers::pi / 180))));

}

GPL::Type TAN::type() const
{
  return value->type();
}

const Constant* ASIN::evaluate() const
{
  // const Constant* lhs_constant = lhs->evaluate();
  const Constant* value_constant = value->evaluate();

  if (value->type() == GPL::STRING) {
    Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "asin");
    return ret(new Integer_constant(0 * 0));
  }

  return ret(new Double_constant(std::asin(value_constant->as_double())*180/std::numbers::pi));

}

GPL::Type ASIN::type() const
{
  return value->type();
}

const Constant* ACOS::evaluate() const
{
  // const Constant* lhs_constant = lhs->evaluate();
  const Constant* value_constant = value->evaluate();

  if (value->type() == GPL::STRING) {
    Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "acos");
    return ret(new Integer_constant(0 * 0));
  }

  return ret(new Double_constant(std::acos(value_constant->as_double())*180/std::numbers::pi));

}

GPL::Type ACOS::type() const
{
  return value->type();
}

const Constant* ATAN::evaluate() const
{
  // const Constant* lhs_constant = lhs->evaluate();
  const Constant* value_constant = value->evaluate();

  if (value->type() == GPL::STRING) {
    Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "atan");
    return ret(new Integer_constant(0 * 0));
  }

  return ret(new Double_constant(std::atan(value_constant->as_double())*180/std::numbers::pi));


}

GPL::Type ATAN::type() const
{
  return value->type();
}


const Constant* SQRT::evaluate() const
{
  // const Constant* lhs_constant = lhs->evaluate();
  const Constant* value_constant = value->evaluate();

  if (value->type() == GPL::STRING) {
    Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "sqrt");
    return ret(new Integer_constant(0 * 0));
  }

  return ret(new Double_constant(std::sqrt(value_constant->as_double())));


}

GPL::Type SQRT::type() const
{
  return value->type();
}

const Constant* ABS::evaluate() const
{
  // const Constant* lhs_constant = lhs->evaluate();
  const Constant* value_constant = value->evaluate();

  if (value->type() == GPL::STRING) {
    Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "abs");
    return ret(new Integer_constant(0 * 0));
  }
  
  if(value->type()==GPL::DOUBLE) {
        return ret(new Double_constant(std::abs(value_constant->as_double())));
  }

  return ret(new Integer_constant(std::abs(value_constant->as_int())));


}

GPL::Type ABS::type() const
{
  return value->type();
}

const Constant* FLOOR::evaluate() const
{
  // const Constant* lhs_constant = lhs->evaluate();
  const Constant* value_constant = value->evaluate();

  if (value->type() == GPL::STRING) {
    Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "floor");
    return ret(new Integer_constant(0 * 0));
  }

  return ret(new Integer_constant(std::floor(value_constant->as_double())));


}

GPL::Type FLOOR::type() const
{
  return value->type();
}

const Constant* RANDOM::evaluate() const
{
  const Constant* value_constant = value->evaluate();

  if (value->type() == GPL::STRING) {
    Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "random");
    return ret(new Integer_constant(0 * 0));
  }
  if (value_constant->as_double() <1){
    Error::error(Error::INVALID_ARGUMENT_FOR_RANDOM, value_constant->as_string());
    return ret(new Integer_constant(0 * 0));
  }

  return ret(new Integer_constant(std::rand()% static_cast<int>(std::floor(value_constant->as_double()))));


}

GPL::Type RANDOM::type() const
{
  return value->type();
}



Variable::Variable(const std::string& symbol_name)
    : symbol_name(symbol_name), array_index_expression(nullptr) {}

Variable::Variable(const std::string& symbol_name, const Expression* index_expr)
    : symbol_name(symbol_name), array_index_expression(index_expr) {}

const Constant* Variable::evaluate() const {
    if (symbol_name.empty()) {
        return ret(new Integer_constant(0));
    }
    auto symbol_ptr = symbol();
    if (array_index_expression == nullptr) {
        return ret(symbol_ptr->as_constant());
    }
    int index;
    try {
        index = array_index_expression->evaluate()->as_int();
        std::cout << "Int: " << index<< std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        index = 0; // Set a default value for the index
    }
    
    auto array_size = symbol_ptr->get_count();
    if (index < 0 || index >= array_size) {
        std::cerr << "Error: index out of bounds for array variable " << symbol_name << std::endl;
        return ret(symbol_ptr->as_constant(0));
    }
    return ret(symbol_ptr->as_constant(index));
}

GPL::Type Variable::type() const {
    if (symbol_name.empty()) {
        return GPL::INT;
    }
    return symbol()->get_type();
}

Variable::~Variable() {
    delete array_index_expression;
}
