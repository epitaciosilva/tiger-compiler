%{
    #include "include/utilities.h"
    #include "include/tokens.h"
    #include "include/errormsg.h"

    int offSet = 1;

    int yywrap(void){
        offSet=1;
        return 1;
    }

    void update(void){
        EM_tokPos = offSet;
        offSet += yyleng;
    }
%}

DIGITS [0-9]+
STRINGS \".*\"
IDS [a-zA-Z][a-zA-Z0-9]*

%option nounput
%option noinput

%%

{DIGITS} {update(); yylval.ival=atoi(yytext); return INT;}
{STRINGS} {update(); yylval.sval=yytext; return STRING;}

array {update(); return ARRAY;}
if {update(); return IF;}
then {update(); return THEN;}
else {update(); return ELSE;}
while {update(); return WHILE;}
for {update(); return FOR;}
to {update(); return TO;}
do {update(); return DO;}
let {update(); return LET;}
in {update(); return IN;}
end {update(); return END;}
of {update(); return OF;}
break {update(); return BREAK;}
nil {update(); return NIL;}
function {update(); return FUNCTION;}
var {update(); return VAR;}
type {update(); return TYPE;}

{IDS} {update(); yylval.sval=String(yytext); return ID;}

"," {update(); return COMMA;}
":" {update(); return COLON;}
";" {update(); return SEMICOLON;}
"(" {update(); yylval.sval=yytext; return LPARENTHESIS;}
")" {update(); return RPARENTHESIS;}
"[" {update(); return LBRACKET;}
"]" {update(); return RBRACKET;}
"{" {update(); return LBRACE;}
"}" {update(); return RBRACE;}
"." {update(); return DOT;}
"+" {update(); return PLUS;}
"-" {update(); return MINUS;}
"*" {update(); return TIMES;}
"/" {update(); return DIVIDE;}
"=" {update(); return EQ;}
"<>" {update(); return NEQ;}
"<"  {update(); return LT;}
"<=" {update(); return LE;}
">" {update(); return GT;}
">=" {update(); return GE;}
"&" {update(); return AND;}
"|" {update(); return OR;}
":=" {update(); return ASSIGN;}

"//".*   /* comments */

[\r\t] {update(); continue;}
[\n] {update(); EM_newline(); continue;}
" " {update(); continue;}
.	 {update(); EM_error(EM_tokPos,"illegal token");}
%%