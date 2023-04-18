// Mon Apr 27 16:03:16 PDT 2020
// bison syntax indicating C++ declarations required by both the parser and scanner
%code requires {
  #include "Constant.h"
  #include <string>
  #include "Scope_manager.h"
  #include "Variable.h"
  #include "Parameter.h"
  #include "Member_variable.h"
 
  class Expression;
  class Variable;
  struct Parameter;
  class Statement;
  class Member_variable;
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
#include <iomanip>
 #include <sstream>
// bison syntax indicating the end of a C/C++ code section
%} 


// turn on verbose (longer) error messages
%define parse.error verbose


%union {
 int            union_int;
 std::string*   union_string;  // MUST be a pointer to a string
 double         union_double;
 GPL::Type      union_gpl_type;
 const Variable* union_variable_ptr;
 const Expression* union_expression_ptr;
Parameter* union_param_node_ptr;
};
%destructor { delete $$; } <union_string>

// tokens declared here



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
%token <union_int> T_EXIT    "exit"; /* value is line number */
%token <union_int> T_PRINT   "print"; /* value is line number */
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
%type <union_gpl_type> object_type;
%type <union_expression_ptr> primary_expression;
%type <union_expression_ptr> expression;
%type <union_expression_ptr> optional_initializer;
%type <union_variable_ptr> variable;
%type <union_param_node_ptr> parameter;
%type <union_param_node_ptr> parameter_list;
%type <union_param_node_ptr> parameter_list_or_empty;
// Add the %nonassoc directive for the non-associative operators
%type <union_expression_ptr> or_expr;
%type <union_expression_ptr> and_expr;
%type <union_expression_ptr> equality_expr;
%type <union_expression_ptr> relational_expr;
%type <union_expression_ptr> add_sub_expr;
%type <union_expression_ptr> mul_div_mod_expr;
%type <union_expression_ptr> not_expr;
%type <union_expression_ptr> unary_expr; 

%nonassoc T_ELSE
%nonassoc T_IF_NO_ELSE

%{
template<typename OP, GPL::Operator op_type>
const Expression* bin_op_check(const Expression* one, const Expression* three, unsigned int valid_types)
    {
        bool lhs_valid = one->type() & valid_types;
        bool rhs_valid = three->type() & valid_types;
        if (lhs_valid && rhs_valid){
            return new OP(one, three);
        }

        if (!lhs_valid)
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, to_string(op_type));
        if (!rhs_valid)
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, to_string(op_type));
        delete one;
        delete three;
        return new Integer_constant(0);
    }

template<typename OP, GPL::Operator op_type>
const Expression* unary_op_check(const Expression* two, unsigned int valid_types)
    {
        bool rhs_valid = two->type() & valid_types;
        if (rhs_valid)
            return new OP(two);
        if (!rhs_valid)
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, to_string(op_type));
        delete two;
        return new Integer_constant(0);
    }
%}


%%


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
                            const Constant* const_value = $3->evaluate();
                            // int* ivalue = new int(static_cast<int>(const_value->as_double()));
                            
                            int* ivalue =  new int(const_value->as_int());
                            
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
                            double* dvalue = nullptr;
                            
                            if (const_value->type() == GPL::INT) {
                                dvalue = new double(static_cast<double>(const_value->as_int()));
                            } else if (const_value->type() == GPL::DOUBLE) {
                                dvalue = new double(const_value->as_double());
                            }
                            
                            // double* dvalue = new double(const_value->as_double());
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

                            std::stringstream ss;

                            if (const_value->type() == GPL::INT) {
                                ss << const_value->as_int();
                            } else if (const_value->type() == GPL::DOUBLE) {
                                    ss << std::fixed << std::setprecision(6) << const_value->as_double();

                            } else {
                                ss << const_value->as_string();
                            }

                            std::string* svalue = new std::string(ss.str());
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
            switch($1) {
                case GPL::INT:
                {
                    int* ivalue = new int(0);
                    symtab.add_to_current_scope(std::make_shared<Symbol>(*$2, ivalue));
                    break;
                }
                case GPL::DOUBLE:
                {
                    double* dvalue = new double(0.0);
                    symtab.add_to_current_scope(std::make_shared<Symbol>(*$2, dvalue));
                    break;
                }
                case GPL::STRING:
                {
                    std::string* svalue = new std::string("");
                    symtab.add_to_current_scope(std::make_shared<Symbol>(*$2, svalue));
                    break;
                }
                default:
                    assert(false);
            }
        
        
        }
        delete $2;
        delete $3;

    }
    | simple_type T_ID T_LBRACKET expression T_RBRACKET {
            Scope_manager& symtab = Scope_manager::instance();
            int array_size;
            if ($4->type() != GPL::INT) {
                Error::error(Error::ARRAY_SIZE_MUST_BE_AN_INTEGER, GPL::to_string($4->type()), *$2, "a");
                array_size = 1;
            } else {
                array_size = $4->evaluate()->as_int();
            }
                if (array_size <= 0) {
                    Error::error(Error::INVALID_ARRAY_SIZE, *$2, std::to_string(array_size));
                }
                if (symtab.defined_in_current_scope(*$2)) {
                    Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2);
                } else {
                    switch ($1) {
                        case GPL::INT: {
                            int *ivalue = new int[array_size];
                            for (int i = 0; i < array_size; i++) {
                                ivalue[i] = 0;
                            }
                            symtab.add_to_current_scope(std::make_shared<Symbol>(*$2, ivalue, array_size));
                            break;
                        }
                        case GPL::DOUBLE: {
                            double *dvalue = new double[array_size];
                            for (int i = 0; i < array_size; i++) {
                                dvalue[i] = 0.0;
                            }
                            symtab.add_to_current_scope(std::make_shared<Symbol>(*$2, dvalue, array_size));
                            break;
                        }
                        case GPL::STRING: {
                            std::string *svalue = new std::string[array_size];
                            for (int i = 0; i < array_size; i++) {
                                svalue[i] = "";
                            }
                            
                            symtab.add_to_current_scope(std::make_shared<Symbol>(*$2, svalue, array_size));
                            break;
                        }
                        default:
                            assert(false);
                    }
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
    object_type T_ID parameter_list_or_empty {
        Scope_manager& symtab = Scope_manager::instance();
        if (symtab.defined_in_current_scope(*$2)) {
            Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2);
            delete $2;
            break;
        }

        // Create game object symbols and insert them into the symbol table

        switch ($1) {
            case GPL::Type::CIRCLE: {
                Circle* circle_obj = new Circle();
                symtab.add_to_current_scope(std::make_shared<Symbol>(*$2, circle_obj));
                break;
            }
            case GPL::Type::RECTANGLE: {
                
                Rectangle* rectangle_obj = new Rectangle();
                symtab.add_to_current_scope(std::make_shared<Symbol>(*$2, rectangle_obj));
                break;
            }
            case GPL::Type::TEXTBOX: {
                Textbox* textbox_obj = new Textbox();
                symtab.add_to_current_scope(std::make_shared<Symbol>(*$2, textbox_obj));
                break;
            }
            case GPL::Type::TRIANGLE: {
                Triangle* triangle_obj = new Triangle();
                symtab.add_to_current_scope(std::make_shared<Symbol>(*$2, triangle_obj));
                break;
            }
            case GPL::Type::PIXMAP: {
                Pixmap* pixmap_obj = new Pixmap();
                symtab.add_to_current_scope(std::make_shared<Symbol>(*$2, pixmap_obj));
                break;
            }
            default:
                assert(false);
        }

        // TODO: Process the object's parameters (if any) using the parameter_list_or_empty
        // Parameter *p = $3;
        // while (p != nullptr) {
        for (const Parameter *p = $3; p != nullptr; p = p->next) {
            
            std::shared_ptr<Symbol> game_object = symtab.lookup(*$2);
            // if (game_object && game_object->is_game_object()) {
               
            if (game_object) {
                // std::cout << p->name << std::endl;
                Game_object* obj = game_object->as_game_object(); 
                GPL::Type expected_type;
                try {
                    // std::cout << "done  "<< p->name << std::endl;
                    expected_type = obj->attribute_type(p->name);
                    // if (expected_type == p->value->type()) {
                         
                        switch (expected_type){
                            case GPL::INT: {
                                const Constant* const_value = p->value->evaluate();
                            
                                obj->write_attribute(p->name, const_value->as_int());
                                break;
                            }
                            case GPL::DOUBLE: {
                                const Constant* const_value = p->value->evaluate();
                            
                                obj->write_attribute(p->name, const_value->as_double());
                                break;
                            }
                            case GPL::STRING: {
                                const Constant* const_value = p->value->evaluate();

                                std::string number_string;

                                if (const_value->type() == GPL::INT) {
                                    // ss << const_value->as_int();
                                    number_string = std::to_string(const_value->as_int());
                                    std::cout << number_string << std::endl;
                                } else if (const_value->type() == GPL::DOUBLE) {
                                    number_string = std::to_string(const_value->as_double());
                                } else {
                                    number_string =  const_value->as_string();
                                }
                                // std::cout << ss.str() << std::endl;
                                // std::string* svalue = new std::string(ss.str());
                                //obj->write_attribute(p->name, svalue);
                                obj->write_attribute(p->name, number_string);
                                
                                break;
                            }
                            default:
                                assert(false);
                        }
                }

                catch (const  std::out_of_range& e){
                    Error::error(Error::UNKNOWN_CONSTRUCTOR_PARAMETER,*$2,p->name);
                } catch (GPL::Type errorneous_type){
                    Error::error(Error::INCORRECT_CONSTRUCTOR_PARAMETER_TYPE, *$2, p->name);
                }
            }
        }
        

        // Clean up
        delete $2;
        while ($3 != nullptr) {
            Parameter* temp = $3->next;
            delete $3;
            $3 = temp;
        }
    }
    | object_type T_ID T_LBRACKET expression T_RBRACKET{
            Scope_manager& symtab = Scope_manager::instance();
            int array_size;
            if ($4->type() != GPL::INT) {
                Error::error(Error::ARRAY_SIZE_MUST_BE_AN_INTEGER, GPL::to_string($4->type()), *$2, "a");
                array_size =1;
            }else{
                array_size = $4->evaluate()->as_int();
            } 
             
            if (array_size <= 0) {
                Error::error(Error::INVALID_ARRAY_SIZE, *$2, std::to_string(array_size));
                array_size = 1;
            }
            if (symtab.defined_in_current_scope(*$2)) {
                Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2);
            } else {
                switch ($1) {
                    case GPL::CIRCLE: {
                        Circle* circle_array = new Circle[array_size];
                        symtab.add_to_current_scope(std::make_shared<Symbol>(*$2, circle_array, array_size));
                        break;
                    }
                    case GPL::RECTANGLE: {
                        Rectangle* rectangle_array = new Rectangle[array_size];
                        symtab.add_to_current_scope(std::make_shared<Symbol>(*$2, rectangle_array, array_size));
                        break;
                    }
                    case GPL::TRIANGLE: {
                        Triangle* triangle_array = new Triangle[array_size];
                        // for (int i = 0; i < array_size; i++) {
                        //     circle_ptr[i] = new Circle();
                        // }
                        symtab.add_to_current_scope(std::make_shared<Symbol>(*$2, triangle_array, array_size));
                        break;
                    }
                    case GPL::PIXMAP: {
                        Pixmap* pixmap_array = new Pixmap[array_size];
                        // for (int i = 0; i < array_size; i++) {
                        //     circle_ptr[i] = new Circle();
                        // }
                        symtab.add_to_current_scope(std::make_shared<Symbol>(*$2, pixmap_array, array_size));
                        break;
                    }
                    case GPL::TEXTBOX: {
                        Textbox* text_array = new Textbox[array_size];
                        // for (int i = 0; i < array_size; i++) {
                        //     circle_ptr[i] = new Circle();
                        // }
                        symtab.add_to_current_scope(std::make_shared<Symbol>(*$2, text_array, array_size));
                        break;
                    }
                    default:
                        assert(false);
                
                }
            }
            delete $2;
    }


//---------------------------------------------------------------------
object_type:
    T_TRIANGLE      {$$=GPL::TRIANGLE;}
    | T_PIXMAP {$$=GPL::PIXMAP;}
    | T_CIRCLE {$$=GPL::CIRCLE;}
    | T_RECTANGLE {$$=GPL::RECTANGLE;}
    | T_TEXTBOX {$$=GPL::TEXTBOX;}


//---------------------------------------------------------------------
parameter_list_or_empty :
    T_LPAREN parameter_list T_RPAREN{
        $$ = $2;
    }
    | T_LPAREN T_RPAREN{
        $$ =nullptr;
    }
    | %empty{
        $$ =nullptr;
    }


//---------------------------------------------------------------------
parameter_list:
    parameter_list T_COMMA parameter {
        Parameter* current = $1;
        while (current->next) {
            current = current->next;
        }
        current->next = $3;
        current->next->next = nullptr;
        $$ = $1;
    }
    | parameter {
        $$ = $1;
    }


//---------------------------------------------------------------------
parameter:
    T_ID T_ASSIGN expression{
        $$ = new Parameter(*$1, $3);
    }


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
    T_IF T_LPAREN expression T_RPAREN statement_or_block_of_statements %prec T_IF_NO_ELSE
    | T_IF T_LPAREN expression T_RPAREN statement_or_block_of_statements T_ELSE statement_or_block_of_statements
    ;


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
    T_ID {
        Scope_manager& scopemgr = Scope_manager::instance();
        // Lookup symbol
        auto symbol=scopemgr.lookup(*$1);
        if (symbol == nullptr) {
            Error::error(Error::UNDECLARED_VARIABLE, *$1);
            $$ = new Variable("");
            delete $1;
            break;
        }
        if (symbol->get_count() >0) {
            Error::error(Error::VARIABLE_IS_AN_ARRAY, *$1);
            $$ = new Variable("");
            delete $1;
            break;
        }
        $$ = new Variable(*$1);
    }
    | T_ID T_LBRACKET expression T_RBRACKET {
        Scope_manager& scopemgr = Scope_manager::instance();
        auto symbol=scopemgr.lookup(*$1);
        if (symbol == nullptr) {
            Error::error(Error::UNDECLARED_VARIABLE, *$1 + "[]");
            $$ = new Variable("");
            delete $1;
            break;
        }
        if (symbol->get_count() <=0) {
            Error::error(Error::VARIABLE_NOT_AN_ARRAY, *$1);
            $$ = new Variable("");
            delete $1;
            break;
        }
        if ($3->type() != GPL::INT) {
            Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER, *$1, GPL::to_string($3->type()));
            $$ = new Variable("");
            delete $1;
            break;
        }
        $$ = new Variable(*$1, $3);
    }
    | T_ID T_PERIOD T_ID {
        
        Scope_manager& scopemgr = Scope_manager::instance();
        auto symbol = scopemgr.lookup(*$1);
        if (symbol == nullptr) {
            Error::error(Error::UNDECLARED_VARIABLE, *$1);
            // $$ = new Member_variable("");
            $$ = nullptr;
            delete $1;
            delete $3;
            break;
        }else {
            if (symbol->get_count() > 0) {
                Error::error(Error::VARIABLE_IS_AN_ARRAY, *$1);
                $$ = nullptr;
                delete $1;
                delete $3;
                break;
            }
            try{
                std::shared_ptr<const Constant>(symbol->as_constant(*$3));
                $$ = new Member_variable(*$1, *$3);
            }catch (GPL::Type type){
                Error::error(Error::LHS_OF_PERIOD_MUST_BE_OBJECT, *$1, GPL::to_string(type));
                $$ = nullptr;
            }catch (const std::out_of_range&) {
                Error::error(Error::UNDECLARED_MEMBER, *$1, *$3);
                $$ = nullptr;
            }
        
            delete $1;
            delete $3;
        }

    }
    | T_ID T_LBRACKET expression T_RBRACKET T_PERIOD T_ID {
        // std::cout << "T_LBRACKET get the parameter" << std::endl;
        Scope_manager& scopemgr = Scope_manager::instance();
        auto symbol = scopemgr.lookup(*$1);
        if (symbol == nullptr) {
            Error::error(Error::UNDECLARED_VARIABLE, *$1 + "[]");
            // $$ = new Member_variable("");
            $$ = nullptr;
            delete $1;
            delete $6;
            break;
        }else{
            if ($3->type() != GPL::INT) {
            Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER, *$1, GPL::to_string($3->type()));
            $$ = new Member_variable(*$1, 0, *$6);
            $$ = nullptr;
            delete $1;
            delete $6;
            break;
            }else {
                if (symbol->get_count() <=0) {
                    Error::error(Error::VARIABLE_NOT_AN_ARRAY, *$1);
                    $$ = new Member_variable(*$1, 0, *$6);
                    delete $1;
                    delete $6;
                    break;
                }
                try{
                    std::shared_ptr<const Constant>(symbol->as_constant(*$6));
                    $$ = new Member_variable(*$1, $3, *$6);
                }catch (GPL::Type type) {
                    Error::error(Error::LHS_OF_PERIOD_MUST_BE_OBJECT, *$1, GPL::to_string(type));
                    $$ = nullptr;
                } catch (const std::out_of_range&) {
                    Error::error(Error::UNDECLARED_MEMBER, *$1, *$6);
                    $$ = nullptr;
                }
                delete $1;
                delete $6;
            }
            

        }

    }


//---------------------------------------------------------------------
expression:
    or_expr
    ;

or_expr
    : and_expr
    | or_expr T_OR and_expr { $$ = bin_op_check<OR, GPL::OR>($1, $3, GPL::INT|GPL::DOUBLE); }
    ;

and_expr
    : equality_expr
    | and_expr T_AND equality_expr { $$ = bin_op_check<AND, GPL::AND>($1, $3, GPL::INT|GPL::DOUBLE); }
    ;

equality_expr
    : relational_expr
    | equality_expr T_EQUAL relational_expr { $$ = bin_op_check<EQUAL, GPL::EQUAL>($1, $3, GPL::INT|GPL::DOUBLE|GPL::STRING); }
    | equality_expr T_NOT_EQUAL relational_expr { $$ = bin_op_check<NOT_EQUAL, GPL::NOT_EQUAL>($1, $3, GPL::INT|GPL::DOUBLE|GPL::STRING); }
    ;

relational_expr
    : add_sub_expr
    | relational_expr T_LESS add_sub_expr { $$ = bin_op_check<LESS, GPL::LESS_THAN>($1, $3, GPL::INT|GPL::DOUBLE|GPL::STRING); }
    | relational_expr T_GREATER add_sub_expr { $$ = bin_op_check<GREATER, GPL::GREATER_THAN>($1, $3, GPL::INT|GPL::DOUBLE|GPL::STRING); }
    | relational_expr T_LESS_EQUAL add_sub_expr { $$ = bin_op_check<LESS_EQUAL, GPL::LESS_EQUAL>($1, $3, GPL::INT|GPL::DOUBLE|GPL::STRING); }
    | relational_expr T_GREATER_EQUAL add_sub_expr { $$ = bin_op_check<GREATER_EQUAL, GPL::GREATER_EQUAL>($1, $3, GPL::INT|GPL::DOUBLE|GPL::STRING); }
    ;

add_sub_expr
    : mul_div_mod_expr
    | add_sub_expr T_PLUS mul_div_mod_expr { $$ = bin_op_check<Plus, GPL::PLUS>($1, $3, GPL::INT|GPL::DOUBLE|GPL::STRING); }
    | add_sub_expr T_MINUS mul_div_mod_expr { $$ = bin_op_check<Minus, GPL::MINUS>($1, $3, GPL::INT|GPL::DOUBLE); }
    ;

mul_div_mod_expr
    : not_expr
    | mul_div_mod_expr T_MULTIPLY not_expr { $$ = bin_op_check<Multiply, GPL::MULTIPLY>($1, $3, GPL::INT|GPL::DOUBLE); }
    | mul_div_mod_expr T_DIVIDE not_expr { $$ = bin_op_check<Divide, GPL::DIVIDE>($1, $3, GPL::INT|GPL::DOUBLE); }
    | mul_div_mod_expr T_MOD not_expr { $$ = bin_op_check<Modulus, GPL::MOD>($1, $3, GPL::INT); }
    ;

not_expr
    : unary_expr
    | T_NOT unary_expr { $$ = unary_op_check<NOT, GPL::NOT>($2, GPL::INT|GPL::DOUBLE); }


unary_expr
    : primary_expression
    | T_MINUS not_expr { $$ = unary_op_check<NEGATIVE, GPL::UNARY_MINUS>($2, GPL::INT|GPL::DOUBLE); }
    | primary_expression T_TOUCHES primary_expression
    | primary_expression T_NEAR primary_expression
    ;




primary_expression:
    T_SIN T_LPAREN expression T_RPAREN {
        $$ = unary_op_check<SIN, GPL::SIN>($3, GPL::INT|GPL::DOUBLE);
    }
    | T_COS T_LPAREN expression T_RPAREN {
        $$ = unary_op_check<COS, GPL::COS>($3, GPL::INT|GPL::DOUBLE);
    }
    | T_TAN T_LPAREN expression T_RPAREN {
        $$ = unary_op_check<TAN, GPL::TAN>($3, GPL::INT|GPL::DOUBLE);
    }
    | T_ASIN T_LPAREN expression T_RPAREN {
        $$ = unary_op_check<ASIN, GPL::ASIN>($3, GPL::INT|GPL::DOUBLE);
    }
    | T_ACOS T_LPAREN expression T_RPAREN {
        $$ = unary_op_check<ACOS, GPL::ACOS>($3, GPL::INT|GPL::DOUBLE);
    }
    | T_ATAN T_LPAREN expression T_RPAREN {
        $$ = unary_op_check<ATAN, GPL::ATAN>($3, GPL::INT|GPL::DOUBLE);
    }
    | T_SQRT T_LPAREN expression T_RPAREN {
        $$ = unary_op_check<SQRT, GPL::SQRT>($3, GPL::INT|GPL::DOUBLE);
    }
    | T_ABS T_LPAREN expression T_RPAREN {
        $$ = unary_op_check<ABS, GPL::ABS>($3, GPL::INT|GPL::DOUBLE);
    }
    | T_FLOOR T_LPAREN expression T_RPAREN {
        $$ = unary_op_check<FLOOR, GPL::FLOOR>($3, GPL::INT|GPL::DOUBLE);
    }
    | T_RANDOM T_LPAREN expression T_RPAREN {
        $$ = unary_op_check<RANDOM, GPL::RANDOM>($3, GPL::INT|GPL::DOUBLE);
    }
    


//---------------------------------------------------------------------
primary_expression:
    T_LPAREN  expression T_RPAREN {$$=$2;}
    | variable {$$=$1;}
    | T_INT_CONSTANT { $$=new Integer_constant($1);}
    | T_TRUE { $$=new Integer_constant(1); }
    | T_FALSE { $$=new Integer_constant(0); }
    | T_DOUBLE_CONSTANT { $$=new Double_constant($1);}
    | T_STRING_CONSTANT { $$=new String_constant(*$1); delete $1;}
    ;

%%