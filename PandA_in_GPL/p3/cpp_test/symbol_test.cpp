#include <iostream>
#include <string>
#include "types_and_ops.h"
#include "Symbol.h"
using namespace std;
// typedef struct{
//     int id;
//     string name;
//     int gpa;
// }Person;

// void assing_gpa(Person *student){

//     student->gpa = 3.14;
// }


// int main(){
//     // int* id=nullptr;
//     // id = new int;
//     // *id = 1;
//     Person* pd=nullptr;
//     pd = new Person;
//     assing_gpa(pd);
//     delete pd;

//     // std::cout << "the address "  <<  id << std::endl;
//     // std::cout << "the value "  <<  *id << std::endl;
//     // delete id;
//     return 0;

// }

int main()
{
  // double* oneofem=new double(3.141592);
  // double* bunchofem=new double[4] {1.123, 2.234, 3.456, 7.899};
  int *sample= new int(1);
  Symbol one("pi", sample);
  // Symbol two("racetimes", bunchofem, 4);
  // cout << two << endl;
  // cout << one << endl;
}
