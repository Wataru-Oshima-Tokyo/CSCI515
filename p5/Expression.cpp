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
// overwritethe pointer.
const Constant* Expression::ret(const Constant* new_evald_constant) const
{
  delete evaluated_constant;
  return evaluated_constant=new_evald_constant;
}
/**********************************************/
/************* Other operators ****************/
/**********************************************/

std::string Expression::get_name() const
{
  return "";
}


const Constant* Plus::evaluate() const
{
  GPL::Type lht=lhs->type();
  GPL::Type rht=rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lht==GPL::STRING || rht==GPL::STRING){
      return ret(new String_constant(lhs_constant->as_string() + //<--addition
                                  rhs_constant->as_string()));
  }

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

  if(lhs->type()==GPL::DOUBLE || rhs->type()==GPL::DOUBLE)
    return ret(new Double_constant(lhs_constant->as_double() * //<--multiply
                                   rhs_constant->as_double()));
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

  if (!Error::runtime() && rhs_constant->as_double() == 0.0) {
    Error::error(Error::DIVIDE_BY_ZERO_AT_PARSE_TIME);
    return ret(new Integer_constant(0));
  }

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

  if (!Error::runtime() && rhs_constant->as_int() == 0) {
    Error::error(Error::MOD_BY_ZERO_AT_PARSE_TIME);
    return ret(new Integer_constant(0));
  }


  return ret(new Integer_constant(lhs_constant->as_int() % rhs_constant->as_int()));
}

GPL::Type Modulus::type() const
{

  return GPL::INT;
}


const Constant* OR::evaluate() const
{
  const Constant* lhs_constant = lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();

  return ret(new Integer_constant(lhs_constant->as_double() || //<--or
                                   rhs_constant->as_double()));

}

GPL::Type OR::type() const
{

  return GPL::INT;
}

const Constant* AND::evaluate() const
{
  const Constant* lhs_constant = lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();

  return ret(new Integer_constant(lhs_constant->as_double() &&  //<--AND
                                  rhs_constant->as_double()));
}

GPL::Type AND::type() const
{
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
  return ret(new Integer_constant(lhs_constant->as_double()==rhs_constant->as_double()));
}

GPL::Type EQUAL::type() const
{
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
  return GPL::INT;
}


const Constant* NEGATIVE::evaluate() const
{
  // const Constant* lhs_constant = lhs->evaluate();
  const Constant* value_constant = value->evaluate();


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
  const Constant* value_constant = value->evaluate();


  if(value->type()==GPL::DOUBLE) {
        return ret(new Integer_constant(!value_constant->as_double()));
  }

  return ret(new Integer_constant(!value_constant->as_int()));
}

GPL::Type NOT::type() const
{
  return GPL::INT;
}

const Constant* SIN::evaluate() const
{
  const Constant* value_constant = value->evaluate();

  return ret(new Double_constant(std::sin(value_constant->as_double() * (std::numbers::pi / 180))));

}

GPL::Type SIN::type() const
{
  return GPL::DOUBLE;
}

const Constant* COS::evaluate() const
{
  const Constant* value_constant = value->evaluate();

  return ret(new Double_constant(std::cos(value_constant->as_double()* (std::numbers::pi / 180))));
}

GPL::Type COS::type() const
{
  return GPL::DOUBLE;
}

const Constant* TAN::evaluate() const
{
  const Constant* value_constant = value->evaluate();
  return ret(new Double_constant(std::tan(value_constant->as_double()* (std::numbers::pi / 180))));

}

GPL::Type TAN::type() const
{
  return GPL::DOUBLE;
}

const Constant* ASIN::evaluate() const
{
  const Constant* value_constant = value->evaluate();

  return ret(new Double_constant(std::asin(value_constant->as_double())*180/std::numbers::pi));

}

GPL::Type ASIN::type() const
{
  return GPL::DOUBLE;
}

const Constant* ACOS::evaluate() const
{
  const Constant* value_constant = value->evaluate();

  return ret(new Double_constant(std::acos(value_constant->as_double())*180/std::numbers::pi));

}

GPL::Type ACOS::type() const
{
  return GPL::DOUBLE;
}

const Constant* ATAN::evaluate() const
{
  const Constant* value_constant = value->evaluate();

  return ret(new Double_constant(std::atan(value_constant->as_double())*180/std::numbers::pi));


}

GPL::Type ATAN::type() const
{
  return GPL::DOUBLE;
}


const Constant* SQRT::evaluate() const
{
  const Constant* value_constant = value->evaluate();

  return ret(new Double_constant(std::sqrt(value_constant->as_double())));


}

GPL::Type SQRT::type() const
{
  return GPL::DOUBLE;
}

const Constant* ABS::evaluate() const
{
  const Constant* value_constant = value->evaluate();

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
  const Constant* value_constant = value->evaluate();

  return ret(new Integer_constant(floor(value_constant->as_double())));

}

GPL::Type FLOOR::type() const
{
  return GPL::INT;
}

const Constant* RANDOM::evaluate() const
{
  const Constant* value_constant = value->evaluate();

  if (value_constant->as_double() <1){
    Error::error(Error::INVALID_ARGUMENT_FOR_RANDOM, value_constant->as_string());
    if (value_constant->type() == GPL::INT)
      return ret(new Integer_constant(1));
    return ret(new Integer_constant(0));
  }

  return ret(new Integer_constant(std::rand()% static_cast<int>(std::floor(value_constant->as_double()))));


}

GPL::Type RANDOM::type() const
{
  return GPL::INT;
}


