/*
 * Analyseur lexical du compilateur L en FLEX
 */
 
%{
#include "symboles.h"
%}
%option yylineno
%option nounput
%option noinput

/* Déclarations à compléter ... */

%%
[0-9]+ {return NOMBRE;}
[ \t] ; /* ignore les blancs et tabulations */
\n     return 0;
<<EOF>>              { return FIN;                 }  /* Fin de fichier */

%%
int yywrap(){
  return 1;
}

