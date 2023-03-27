// Mon Apr 27 16:03:16 PDT 2020
// bison syntax indicating C++ declarations required by both the parser and scanner
%code requires {
  #include "Constant.h"
  #include <string>
  #include "Scope_manager.h"
  class Expression;
  class Variable;
  struct Parameter;
  class Statement;
  #ifndef P1
    #include "types_and_ops.h"  //include in all projects except the first
  #endif
  #ifdef GRAPHICS
    #include "Window.h"
  #endif
}

// bison syntax to indicate the beginning of a C/C++ code section
%{

extern int yylex();  // prototype of function generated by flex
extern int yyerror(const char *); // used to print errors
extern int line_count;            // current line in the input; from record.l

#include "error.h"      // class for printing errors (used by gpl)
#include <iostream>

// bison syntax indicating the end of a C/C++ code section
%} 


// turn on verbose (longer) error messages
%define parse.error verbose

%union {
 int            union_int;
 std::string*   union_string;  // MUST be a pointer to a string
 double         union_double;
 GPL::Type      union_gpl_type;
 const Expression* union_expression_ptr;
};
%destructor { delete $$; } <union_string>

// tokens declared here

%%

  /* updated January 2019 
    * Copy the following token declarations into your .y file. */

  /* Tokens with angle braces < > after %token require a type. 
    * This is the type of the variable the scanner (flex) puts into the union.
    * Fill in the < > with the appropriate union variable
    *     for example
    *     %token <union_int> T_INT_CONSTANT       "int constant" 
    */

%token T_INT                 "int";
%token T_DOUBLE              "double";
%token T_STRING              "string";
%token T_TRIANGLE            "triangle";
%token T_PIXMAP              "pixmap";
%token T_CIRCLE              "circle";
%token T_RECTANGLE           "rectangle";
%token T_TEXTBOX             "textbox";

%token T_FORWARD             "forward";
%token T_INITIALIZATION      "initialization";
%token T_TERMINATION         "termination";
%token T_ON                  "on";
%token T_ANIMATION           "animation";
%token T_IF                  "if";
%token T_FOR                 "for";
%token T_ELSE                "else";
%token < > T_EXIT            "exit"; /* value is line number */
%token < > T_PRINT           "print"; /* value is line number */
%token T_TRUE                "true";
%token T_FALSE               "false";

%token T_SPACE               "space";
%token T_LEFTARROW           "leftarrow";
%token T_RIGHTARROW          "rightarrow";
%token T_UPARROW             "uparrow";
%token T_DOWNARROW           "downarrow";
%token T_LEFTMOUSE_DOWN      "leftmouse_down";
%token T_MIDDLEMOUSE_DOWN    "middlemouse_down";
%token T_RIGHTMOUSE_DOWN     "rightmouse_down";
%token T_LEFTMOUSE_UP        "leftmouse_up";
%token T_MIDDLEMOUSE_UP      "middlemouse_up";
%token T_RIGHTMOUSE_UP       "rightmouse_up";
%token T_MOUSE_MOVE          "mouse_move";
%token T_MOUSE_DRAG          "mouse_drag";
%token T_F1                  "f1";
%token T_AKEY                "akey";
%token T_SKEY                "skey";
%token T_DKEY                "dkey";
%token T_FKEY                "fkey";
%token T_HKEY                "hkey";
%token T_JKEY                "jkey";
%token T_KKEY                "kkey";
%token T_LKEY                "lkey";
%token T_WKEY                "wkey";
%token T_ZKEY                "zkey";

%token T_LPAREN              "(";
%token T_RPAREN              ")";
%token T_LBRACE              "{";
%token T_RBRACE              "}";
%token T_LBRACKET            "[";
%token T_RBRACKET            "]";
%token T_SEMIC               ";";
%token T_COMMA               ",";
%token T_PERIOD              ".";

%token T_ASSIGN              "=";
%token T_PLUS_ASSIGN         "+=";
%token T_MINUS_ASSIGN        "-=";
%token T_PLUS_PLUS           "++";
%token T_MINUS_MINUS         "--";

%token T_SIN                 "sin";
%token T_COS                 "cos";
%token T_TAN                 "tan";
%token T_ASIN                "asin";
%token T_ACOS                "acos";
%token T_ATAN                "atan";
%token T_SQRT                "sqrt";
%token T_ABS                 "abs";
%token T_FLOOR               "floor";
%token T_RANDOM              "random";

%token T_TOUCHES             "touches";
%token T_NEAR                "near";

%token T_MULTIPLY            "*";
%token T_DIVIDE              "/";
%token T_PLUS                "+";
%token T_MINUS               "-";
%token T_MOD                 "%";

%token T_LESS                "<";
%token T_GREATER             ">";
%token T_LESS_EQUAL          "<=";
%token T_GREATER_EQUAL       ">=";
%token T_EQUAL               "==";
%token T_NOT_EQUAL           "!=";
%token T_NOT                 "!";
%token T_AND                 "&&";
%token T_OR                  "||";

%token <union_int> T_INT_CONSTANT    "int constant";
%token <union_double> T_DOUBLE_CONSTANT "double constant";
%token <union_string> T_STRING_CONSTANT "string constant";
%token <union_string> T_ID            	 "identifier";

 /* special token that does not match any production */
 /* used for characters that are not part of the language */
%token T_ERROR               "error";


%type <union_gpl_type> simple_type;
%type <union_expression_ptr> primary_expression;
%type <union_expression_ptr> expression;
%type <union_expression_ptr> optional_initializer;
// Add the %nonassoc directive for the non-associative operators

  
%left T_PLUS T_MINUS;
%left T_MULTIPLY T_DIVIDE T_MOD;
%left T_LESS T_GREATER T_LESS_EQUAL T_GREATER_EQUAL;
%left T_EQUAL T_NOT_EQUAL;

%nonassoc T_NEAR T_TOUCHES UNARY_OPS IF_NO_ELSE T_ELSE;


// Grammer rules


// updated October 2021

//---------------------------------------------------------------------
program:
    declaration_list block_list


//---------------------------------------------------------------------
declaration_list:
    declaration_list declaration
    | %empty


//---------------------------------------------------------------------
declaration:
    variable_declaration T_SEMIC
    | object_declaration T_SEMIC
    | forward_declaration T_SEMIC


//---------------------------------------------------------------------
variable_declaration:
    simple_type T_ID optional_initializer{
        Scope_manager& symtab = Scope_manager::instance();
        if(symtab.defined_in_current_scope(*$2))
        {
            Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE,*$2);
            delete $2;
        break;
        }
        try{
            switch($1){
                case GPL::INT :
                    {
                        if ($3 != nullptr) {
                            const Constant* const_value = $3->evaluate();// This causes the error (seg fault error)
                            int* ivalue = new int(const_value->as_int());
                            symtab.add_to_current_scope(std::make_shared<Symbol>(*$2, ivalue));
                        } else {
                            int *ivalue = new int(0);  
                            symtab.add_to_current_scope(std::make_shared<Symbol>(*$2, ivalue));
                        }
                        
                    }
                    break;
                case GPL::DOUBLE :
                    {
                        if ($3 != nullptr) {
                            const Constant* const_value = $3->evaluate();
                            double* dvalue = new double(const_value->as_double());
                            symtab.add_to_current_scope(std::make_shared<Symbol>(*$2, dvalue));
                        }else{
                            double *dvalue = new double(0.0); 
                            symtab.add_to_current_scope(std::make_shared<Symbol>(*$2, dvalue));
                        }
                        
                    }
                    break;
                case GPL::STRING :
                    {
                        if ($3 != nullptr) {
                            const Constant* const_value = $3->evaluate();
                            std::string* svalue = new std::string(const_value->as_string());
                            symtab.add_to_current_scope(std::make_shared<Symbol>(*$2, svalue));
                        }else{
                            std::string *svalue = new std::string("");
                            symtab.add_to_current_scope(std::make_shared<Symbol>(*$2, svalue)); 
                        }
                        
                    }
                    break;
                default:
                    break;

            }
            
        }catch(GPL::Type errorneous_type){
            Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE, GPL::to_string(errorneous_type), *$2, GPL::to_string($1));
        }
        delete $2;
        delete $3;

    }
    | simple_type T_ID T_LBRACKET T_INT_CONSTANT T_RBRACKET {
        Scope_manager& symtab = Scope_manager::instance();
        if(symtab.defined_in_current_scope(*$2))
        {
            Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE,*$2);
            delete $2;
            break;
        }
        if($4 == 0)
        {
            Error::error(Error::INVALID_ARRAY_SIZE,*$2,std::to_string($4));
            delete $2;
            break;
        }
        
        switch($1){
            case GPL::INT :
                {

                    int *ivalue = new int[$4];
                    for (int i=0; i< $4;i++){
                        ivalue[i] = 42;
                    }
                     symtab.add_to_current_scope(std::make_shared<Symbol>(*$2, ivalue, $4));
                }
                break;
            case GPL::DOUBLE :
                {
                    double *dvalue = new double[$4];
                    for (int i=0; i< $4;i++){
                        dvalue[i] = 3.14159;
                    }
                    symtab.add_to_current_scope(std::make_shared<Symbol>(*$2, dvalue,$4));
                }
                break;
            case GPL::STRING :
                {
                    std::string *svalue = new std::string[$4];
                    for (int i=0; i< $4;i++){
                        svalue[i] = "Hello world";
                    }
                    symtab.add_to_current_scope(std::make_shared<Symbol>(*$2, svalue, $4));
                }
                break;
            default:
                break;

        }
        delete $2;
    }


//---------------------------------------------------------------------
simple_type:
    T_INT      {$$=GPL::INT;}
    | T_DOUBLE {$$=GPL::DOUBLE;}
    | T_STRING {$$=GPL::STRING;}



//---------------------------------------------------------------------
optional_initializer:
    T_ASSIGN expression  {$$=$2;}
    | %empty  {$$=nullptr;}   
  

//---------------------------------------------------------------------
object_declaration:
    object_type T_ID parameter_list_or_empty
    | object_type T_ID T_LBRACKET expression T_RBRACKET


//---------------------------------------------------------------------
object_type:
    T_TRIANGLE
    | T_PIXMAP
    | T_CIRCLE
    | T_RECTANGLE
    | T_TEXTBOX


//---------------------------------------------------------------------
parameter_list_or_empty :
    T_LPAREN parameter_list T_RPAREN
    | T_LPAREN T_RPAREN
    | %empty


//---------------------------------------------------------------------
parameter_list :
    parameter_list T_COMMA parameter
    | parameter


//---------------------------------------------------------------------
parameter:
    T_ID T_ASSIGN expression


//---------------------------------------------------------------------
block_list:
    block_list block
    | %empty


//---------------------------------------------------------------------
block:
    initialization_block
    | termination_block
    | animation_block
    | on_block


//---------------------------------------------------------------------
initialization_block:
    T_INITIALIZATION statement_block


//---------------------------------------------------------------------
termination_block:
    T_TERMINATION statement_block


//---------------------------------------------------------------------
forward_declaration:
    T_FORWARD T_ANIMATION T_ID T_LPAREN animation_parameter T_RPAREN


//---------------------------------------------------------------------
animation_parameter:
    object_type T_ID
    | object_type


//---------------------------------------------------------------------
animation_block:
    animation_declaration statement_block


//---------------------------------------------------------------------
animation_declaration:
    T_ANIMATION T_ID T_LPAREN object_type T_ID T_RPAREN


//---------------------------------------------------------------------
on_block:
    T_ON keystroke statement_block


//---------------------------------------------------------------------
keystroke:
    T_SPACE
    | T_UPARROW
    | T_DOWNARROW
    | T_LEFTARROW
    | T_RIGHTARROW
    | T_LEFTMOUSE_DOWN
    | T_MIDDLEMOUSE_DOWN
    | T_RIGHTMOUSE_DOWN
    | T_LEFTMOUSE_UP
    | T_MIDDLEMOUSE_UP
    | T_RIGHTMOUSE_UP
    | T_MOUSE_MOVE
    | T_MOUSE_DRAG
    | T_AKEY
    | T_SKEY
    | T_DKEY
    | T_FKEY
    | T_HKEY
    | T_JKEY
    | T_KKEY
    | T_LKEY
    | T_WKEY
    | T_ZKEY
    | T_F1


//---------------------------------------------------------------------
statement_or_block_of_statements:
    statement_block
    | statement


//---------------------------------------------------------------------
statement_block:
    T_LBRACE statement_list T_RBRACE
    | T_LBRACE T_RBRACE



//---------------------------------------------------------------------
statement_list:
    statement_list statement
    | statement


//---------------------------------------------------------------------
statement:
    if_statement
    | for_statement
    | assign_statement T_SEMIC
    | print_statement T_SEMIC
    | exit_statement T_SEMIC


//---------------------------------------------------------------------
if_statement:
    T_IF T_LPAREN expression T_RPAREN statement_or_block_of_statements
    | T_IF T_LPAREN expression T_RPAREN statement_or_block_of_statements T_ELSE statement_or_block_of_statements
    | T_IF expression statement  IF_NO_ELSE %prec IF_NO_ELSE
    | T_IF expression statement T_ELSE statement


//---------------------------------------------------------------------
for_statement:
    T_FOR T_LPAREN assign_statement_or_empty T_SEMIC expression T_SEMIC assign_statement_or_empty T_RPAREN statement_or_block_of_statements


//---------------------------------------------------------------------
print_statement:
    T_PRINT T_LPAREN expression T_RPAREN


//---------------------------------------------------------------------
exit_statement:
    T_EXIT T_LPAREN expression T_RPAREN


//---------------------------------------------------------------------
assign_statement_or_empty:
    assign_statement
    | %empty


//---------------------------------------------------------------------
assign_statement:
    variable T_ASSIGN expression
    | variable T_PLUS_ASSIGN expression
    | variable T_MINUS_ASSIGN expression
    | variable T_PLUS_PLUS
    | variable T_MINUS_MINUS


//---------------------------------------------------------------------
variable:
    T_ID
    | T_ID T_LBRACKET expression T_RBRACKET
    | T_ID T_PERIOD T_ID
    | T_ID T_LBRACKET expression T_RBRACKET T_PERIOD T_ID


//---------------------------------------------------------------------
expression: 
    primary_expression {$$=$1;}

expression:
    expression T_OR expression { $$=new OR($1, $3); }
    | expression T_AND expression { $$=new AND($1, $3); }
    | expression T_LESS_EQUAL expression { $$=new LESS_EQUAL($1, $3); }
    | expression T_GREATER_EQUAL  expression { $$=new GREATER_EQUAL($1, $3); }
    | expression T_LESS expression { $$=new LESS($1, $3); }
    | expression T_GREATER  expression { $$=new GREATER($1, $3); }
    | expression T_EQUAL expression  { $$=new EQUAL($1, $3); }
    | expression T_NOT_EQUAL expression { $$=new NOT_EQUAL($1, $3); }
    | expression T_PLUS expression { $$=new Plus($1, $3); }
    | expression T_MINUS expression { $$=new Minus($1, $3); }
    | expression T_MULTIPLY expression { $$=new Multiply($1, $3); }
    | expression T_DIVIDE expression { $$=new Divide($1, $3); }
    | expression T_MOD expression { $$=new Modulus($1, $3); }
    | T_MINUS  expression %prec UNARY_OPS { $$=new NEGATIVE(-1, $2); }
    | T_NOT  expression
    | expression T_NEAR expression
    | expression T_TOUCHES expression

primary_expression:
    T_SIN T_LPAREN expression T_RPAREN
    | T_COS T_LPAREN expression T_RPAREN
    | T_TAN T_LPAREN expression T_RPAREN
    | T_ASIN T_LPAREN expression T_RPAREN
    | T_ACOS T_LPAREN expression T_RPAREN
    | T_ATAN T_LPAREN expression T_RPAREN
    | T_SQRT T_LPAREN expression T_RPAREN
    | T_ABS T_LPAREN expression T_RPAREN
    | T_FLOOR T_LPAREN expression T_RPAREN
    | T_RANDOM T_LPAREN expression T_RPAREN


//---------------------------------------------------------------------
primary_expression:
    T_LPAREN  expression T_RPAREN {$$=nullptr; /*CHANGE*/}
    | variable {$$=nullptr; /*CHANGE*/}
    | T_INT_CONSTANT { $$=new Integer_constant($1);}
    | T_TRUE 
    | T_FALSE
    | T_DOUBLE_CONSTANT { $$=new Double_constant($1);}
    | T_STRING_CONSTANT { $$=new String_constant(*$1); delete $1;}
    ;

%%