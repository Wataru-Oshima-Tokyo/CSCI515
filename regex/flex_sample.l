%option noyywrap
%{
  #include <iostream>
  using std::cout;
%}

%%


int {
	cout << "INT\n";
}

[a-z]+ {
	cout << "WORD\n";
}

%%

int main(){
	yylex();
	return 0;
}


