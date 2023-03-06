#include <iostream>
#include <memory>
#include "Date.h"

using namespace std;

// void some_func(double, int){}
// void string_function(const string& s, int){}

// int main()
// {
//     int value;
//     cin >> value;
//     switch(value){
//         case 1:
//             double large=20;
//             some_func(large, value);
//             break;
//         case 2:
//             string string_name="Ebeneezer Scrooge";
//             string_function(string_name, value);
//     }
// }


class Report{
    public:
        Report();
        Date when;
        std::string content;
    private:

};

Report::Report(){
    
}

int main(){
    std::shared_ptr<Report> date;
    date->when.day = 1;
    return 0;
}