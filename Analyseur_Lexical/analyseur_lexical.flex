/*
 * Analyseur lexical du compilateur L en FLEX
 */
 
%{
#include "symboles.h"
%}
%option yylineno
%option nounput
%option noinput

lettre [A-Za-z]
chiffre [0-9]
alphanum {lettre}|{chiffre}

/* Déclarations à compléter ... */

%%
{chiffre}+                                      {return NOMBRE;}
";"                                             {return POINT_VIRGULE;}
"+"                                             {return PLUS;}
"-"                                             {return MOINS;}
"*"                                             {return FOIS;}
"/"                                             {return DIVISE;}
"("                                             {return PARENTHESE_OUVRANTE;}
")"                                             {return PARENTHESE_FERMANTE;}
"["                                             {return CROCHET_OUVRANT;}
"]"                                             {return CROCHET_FERMANT;}
"{"                                             {return ACCOLADE_OUVRANTE;}
"}"                                             {return ACCOLADE_FERMANTE;}
"="                                             {return EGAL;}
"<"                                             {return INFERIEUR;}
"&"                                             {return ET;}
"|"                                             {return OU;}
"!"                                             {return NON;}
"si"                                            {return SI;}
"alors"                                         {return ALORS;}
"sinon"                                         {return SINON;}
"tantque"                                       {return TANTQUE;}
"faire"                                         {return FAIRE;}
"entier"                                        {return ENTIER;}
"retour"                                        {return RETOUR;}
"lire"                                          {return LIRE;}
"ecrire"                                        {return ECRIRE;}
"$"({alphanum}|_)+                              {return ID_VAR;}
({lettre}|"_")({alphanum}|"_")*                 {return ID_FCT;}
","                                             {return VIRGULE;}

[ \t\n] ; /* ignore les blancs, tabulations et retour à la ligne */
#.* ; //on ignore les commentaires
<<EOF>>              { return FIN;                 }  /* Fin de fichier */

%%
int yywrap(){
  return 1;
}

