%token T_INT_CONSTANT;
%token T_PLUS T_MINUS T_MULTIPLY T_DIVIDE T_EXPONENT
%token T_ERROR;

%{
  #include <iostream>
  #include <cmath>
  using std::cout;
  using std::cerr;
  using std::endl;

  /* we must provide the prototype to yylex() since its source is
     in a separate file */
  int yylex();

  /* we must write this function. Generated code calls it */
  int yyerror(const char* err);
%}

%%

start_symbol : expr  { cout << " = " << $1 << endl; }

expr:  
      term
    | expr T_MINUS term { $$ = $1 - $3; }
    | expr T_PLUS term { $$ = $1 + $3; }
    ;

term:
      factor
    | term T_DIVIDE factor { $$ = $1 / $3; }
    | term T_MULTIPLY factor { $$ = $1 * $3; }
    ;

factor:
      primary
    | primary T_EXPONENT factor { $$ = pow($1, $3); }
    ;

primary:
      T_INT_CONSTANT {$$=$1;}
    ;


%%

int main(int argc, char** argv)
{
  yyparse();
}

int yyerror(const char* err)
{
  cerr << err << endl;
  return 0;
}
