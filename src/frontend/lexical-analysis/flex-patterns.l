%{

#include "flex-actions.h"

%}

/* Obliga a crear una regla explícita para manejar lexemas desconocidos. */
%option nodefault

/* Escanea un único archivo y se detiene. */
%option noyywrap

/* Dispone una variable global "yylineno" con el número de línea actual. */
%option yylineno

/* Patrones reutilizables. */
crlf			\r\n
digit			[0-9]
endline			\n
whitespace		[ \f\n\r\t\v]
char            [a-zA-Z_]

%%

"{"                                         { return OPEN_BRACKETS; }
"}"                                         { return CLOSE_BRACKETS; }
"("											{ return OPEN_PARENTHESIS; }
")"											{ return CLOSE_PARENTHESIS; }

"."                                         { return DOT; }

"+"											{ return PLUS; }
"-"											{ return SUB; }
"*"											{ return MUL; }
"/"										    { return DIV; }

"&&"                                         { return AND; }
"||"                                          { return OR; }
"!"                                         { return NOT; }
"="                                         { return EQUAL; }
"=="                                        { return EQUAL_EQUAL; }
"!="                                        { return NOTEQUAL; }
"<"                                         { return LOWER; }
">"                                         { return GREATER; }
"<="                                        { return LOWER_EQUAL; }
">="                                        { return GREATER_EQUAL; }

";"                                         { return SEMICOLON; }

"if"                                        { return IF; }
"else"                                      { return ELSE; }
"while"                                     { return WHILE; }
"return"                                    { return RETURN;}    

"TONE"                                      { return TONE_DEF; }
"BPM"                                       { return BPM; }
"RYTHM"                                     { return RYTHM_DEF;}

"int"                                       { return INTEGER_DEF; }
"boolean"                                   { return BOOLEAN_DEF; }
"melody"                                    { return MELODY; }
"note"                                      { return NOTE; }
"add"                                       { return ADD; }

false|true                                  { return BOOLEAN; }

[A-G][#b]?[2-6]                                  { return TonePatternAction(yytext); }

whole|half|quarter|eight|sixteenth|thirtySecond|sixtyFourth   { return RythmPatternAction(yytext); }

{char}+                                     { return VariablePatternAction(yytext); }

{digit}+									{ return IntegerPatternAction(yytext); }

{whitespace}								{ IgnoredPatternAction(yytext); }

.											{ return UnknownPatternAction(yytext); }

%%