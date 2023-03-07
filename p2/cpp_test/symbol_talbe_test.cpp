#include<iostream>
#include<memory>
#include "Symbol.h"
#include "Symbol_table.h"
using namespace std;

int main()
{
  Symbol_table symtab;

  double* double_oneofem=new double(3.141592);
  double* double_bunchofem=new double[4] {1.123, 2.234, 3.456, 7.899};
  string* string_oneofem=new string("hi there");
  string* string_bunchofem=new string[4]
    {"one", "two two", "three three three", "fo fo fo fo"};
  int* int_oneofem=new int(321);
  int* int_bunchofem=new int[4] {12, 34, 56, 78};

  symtab.insert(std::make_shared<Symbol>("alpha", string_oneofem));
  symtab.insert(std::make_shared<Symbol>("gamma", string_bunchofem, 4));
  symtab.insert(std::make_shared<Symbol>("beta", double_oneofem));
  symtab.insert(std::make_shared<Symbol>("delta", double_bunchofem, 4));
  symtab.insert(std::make_shared<Symbol>("zeta", int_oneofem));
  symtab.insert(std::make_shared<Symbol>("eta", int_bunchofem, 4));

  cout << symtab << endl;
  return 0;
}