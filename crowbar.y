%{
#include <stdio.h>
#include "crowbar.h"
#define YYDEBUG 1
%}

%union {
   char              *identifier;
   ArgumentList      *parameter_list;
   Expression        *expression;
   Statement         *statement;
   StatementList     *statement_list;
   Block             *block;
   Elsif             *elsif;
   IdentifierList    *identifier_list;
}

%token <expression>     INI_LITERAL
%token <expression>     DOBULE_LITERAL
%token <expression>     STRING_LITERAL
%token <identifier>     IDENTIFIER
%token FUNCTION IF ELSE ELSEIF WHILE FOR RETURN_T BREAK CONTINUE NULL_T
       LP RP LC RC SEMICOLON COMMA ASSIGN LOGICAL_AND LOGICAL_OR
       EQ NE GT GE LT LE ADD SUB MUL DIV MOD TRUE_T FALSE_T GLOBAL_T
