
  /* directives, preamble code, etc. */
%token <found_letter>LETTER
%token <found_number>NUMBER
%type <string_pointer> output_chatter

%{
#include<string>
%}

%union {
  int found_number;
  char found_letter;
  std::string* string_pointer;
}

%{
  #include<iostream>
  int yylex(void);//prototype for function declared in scanner
  void yyerror(const char* err_txt);
  using std::cout;
  using std::cerr;
%}
%%
  /* grammar rules */
  start_symbol: output_chatter {std::cout << "We have: " << *$1 << "\n"; }

    // $$              $1           $2
  output_chatter: output_chatter LETTER     {
                                              std::cout << "  parsed letter is=" << $2 << "\n";
                                              *$1+=$2; 
                                              $$=$1;
                                            }
    | output_chatter NUMBER    {
                                 std::cout << "  parsed number is=" << $2 << "\n";
                                 *$1+='#';
                                 $$=$1;
                               }
    | %empty  {
                std::cout << "I'm empty!\n";
                $$=new std::string;
              }


%%
 /* anything put here is copied unaltered to the generated C file */
  void yyerror(const char* err_txt)
  {
    cerr << "OUCH: " << err_txt << '\n';
  }
  int main()
  {
    yyparse();
    return 0;
  }

