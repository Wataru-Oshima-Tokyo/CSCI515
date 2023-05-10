//File: Locator.cpp
#include "Locator.h"
#include "Statement.h"
#include "Animation_code.h"

GPL::Type  Locator::type() const 
{ return intrinsic_type; }

int Locator::get_int_value() const {
    throw intrinsic_type;
}

double Locator::get_double_value() const {
    throw intrinsic_type;
}

std::string Locator::get_string_value() const {
    throw intrinsic_type;
}



//
//Game_object
//
void Game_attribute_locator::mutate(int val)            
{
  gop->write_attribute(attribute_name, val);
}

void Game_attribute_locator::mutate(double val)            
{
  gop->write_attribute(attribute_name, val);
}

void Game_attribute_locator::mutate(const std::string& val)            
{
  gop->write_attribute(attribute_name, val);
}

void Game_attribute_locator::mutate(const Animation_code* val)           
{
  gop->write_attribute(attribute_name, val);
}

void Animation_code_locator::mutate(const std::string& val){
  anc->set_parameter_name(val);
}

void Animation_code_locator::mutate(const Statement* val){
  anc->set_block(val);
} 


// Integer_locator
int Integer_locator::get_int_value() const {
    return data;
}

// Double_locator
double Double_locator::get_double_value() const {
    return data;
}

// String_locator
std::string String_locator::get_string_value() const {
    return data;
}
