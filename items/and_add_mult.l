%option noyywrap
%option no              default

%{
    #include <add_and_mult.ta.h"
    #include <string>
    using std::stoi;
%}

%%

"pi" {return T_PI;}

[0-9]+ {yylval.myunion_int=stoi(yytext); return T_INT};

"+" {return T_ADD;}

"*" {return T_MULT;}

[ \t\n] // do nothing
. //do nothing

%%
