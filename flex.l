%{
    /*PROGRAM, PROGRAMNAME, SEMICOLON, GREATERTHAN, SMALLERTHAN, EQUALITY, NOTEQUALITY, EQUAL, UNITARYMINUS,
    LESSTHANOREQUAL, GREATERTHANOREQUAL, MAIN, RIGHTCURLYBRACKET, VOID, NUMBERINTEGER, NUMBERFLOAT,
    LEFTCURLYBRACKET, RIGHTSQUAREBRACKET, LEFTSQUAREBRACKET, RIGHTPARENTHESIS, LETTERCHAR, WORDSTRING
    LEFTPARENTHESIS, VAR, COLON, MODULE, INTEGER, FLOAT, CHARAC, COMMA, MODULENAME, THEN,
    RETURN, END, READ, WRITE, IF, ELSE, DO, WHILE, FOR, TO, COMPARISON, STRING, AND, OR, SIGN, IDENTIFIER*/
#include "bison.tab.h"
#include <string.h>
/*#include <stdlib.h> */ 

%}

/*regular definitions */
/*Lex definitions used in the regular expressions */

delim       [ \t\n]
whitespace  {delim}+
letter      [A-Za-z]
digit       [0-9]
id          {letter}({letter}|{digit})*
integer     {digit}+
float       {digit}+\.{digit}+
character       \'[A-Za-z]\'
string       \"{letter}({letter}|{digit}|{delim})*\"
%%




"=="        { return(EQUALITY); }
"!="        { return(NOTEQUALITY); }
"<="        { return(LESSTHANOREQUAL); }
">="        { return(GREATERTHANOREQUAL); }


main        { return(MAIN);}
globalvar   { return(GLOVALVAR);}
var         { return(VAR);}
do          { return(DO); }
else        { return(ELSE); }
if          { return(IF); }
int         { return(INTEGER); }
float       { return(FLOAT); }
char        { return(CHARAC); }
read        { return(READ); }
then        { return(THEN); }
while       { return(WHILE); }
write       { return(WRITE); }
void        { return(VOID); }
module      { return(MODULE); }
return      { return(RETURNN); }
for         { return(FOR); }
to          { return(TO); }
program     { return(PROGRAM); }

{character} {yylval.varchar = (char *) strdup(yytext) ; return(LETTERCHAR); }
{integer}   { yylval.intval = atoi (yytext) ;return(NUMBERINTEGER); }
{float}     { yylval.varfloat = atof (yytext);return(NUMBERFLOAT); }


{id}        {yylval.id = (char *) strdup(yytext) ;return(IDENTIFIER); }
{string}    {yylval.varstring = (char *) strdup(yytext) ;return(WORDSTRING); }


[ \t\n]+    /* blank, tab, new line: eat up whitespace */
. { return(yytext[0]); }








%%

int yywrap(void){}