// File: Expression.cpp
#include "Expression.h"
#include "Constant.h"
#include "error.h"
#include<string>
#include <cmath>
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

  if(lhs->type()==GPL::DOUBLE || rhs->type()==GPL::DOUBLE)
    return ret(new Double_constant(lhs_constant->as_double() / //<--divide
                                   rhs_constant->as_double()));
  return ret(new Integer_constant(std::round(lhs_constant->as_int() /     //<--divide
                                  rhs_constant->as_int())));
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
  if (lhs->type() == GPL::STRING) {
    Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "&&");
  }
  if (rhs->type() == GPL::STRING) {
    Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "&&");
  }

  if (lhs->type() == GPL::STRING || rhs->type() == GPL::STRING){
    return ret(new Integer_constant(0 * 0));
  }
    

  if(lhs->type()==GPL::DOUBLE || rhs->type()==GPL::DOUBLE) {
        return ret(new Integer_constant(lhs_constant->as_double() && //<--or
                                   rhs_constant->as_double()));
  }

  return ret(new Integer_constant(lhs_constant->as_int() &&     //<--or
                                  rhs_constant->as_int()));
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
        return ret(new Integer_constant(lhs_constant->as_string() < //<--or
                                   rhs_constant->as_string()));
  }


  if(lhs->type()==GPL::DOUBLE || rhs->type()==GPL::DOUBLE) {
        return ret(new Integer_constant(lhs_constant->as_double() < //<--or
                                   rhs_constant->as_double()));
  }

  return ret(new Integer_constant(lhs_constant->as_int() <    //<--or
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
        return ret(new Integer_constant(lhs_constant->as_string() == //<--or
                                   rhs_constant->as_string()));
  }
  if(lhs->type()==GPL::DOUBLE || rhs->type()==GPL::DOUBLE) {
        return ret(new Integer_constant(lhs_constant->as_double() == //<--or
                                   rhs_constant->as_double()));
  }

  return ret(new Integer_constant(lhs_constant->as_int() ==    //<--or
                                  rhs_constant->as_int()));
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
  const Constant* lhs_constant = lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();

  if(rhs->type()==GPL::STRING) {
        return ret(new String_constant(lhs_constant->as_string() + //<--or
                                   rhs_constant->as_string()));
  }
  if(rhs->type()==GPL::DOUBLE) {
        return ret(new Double_constant(lhs_constant->as_int()  * //<--or
                                   rhs_constant->as_double()));
  }

  return ret(new Integer_constant(lhs_constant->as_int()  *   //<--or
                                  rhs_constant->as_int()));
}

GPL::Type NEGATIVE::type() const
{
  GPL::Type lht = lhs->type();
  GPL::Type rht = rhs->type();
  if (lht == GPL::DOUBLE || rht == GPL::DOUBLE)
    return GPL::DOUBLE;
  return GPL::INT;
}