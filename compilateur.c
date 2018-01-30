#include "./Analyseur_Syntaxique/analyseur_syntaxique.h"

int main(int argc, char **argv) {  
  char nom[100];
  char valeur[100];  
  
  yyin = fopen(argv[1], "r");
  if(yyin == NULL){
    fprintf(stderr, "impossible d'ouvrir le fichier %s\n", argv[1]);
    exit(1);
  }
  do {
    uniteCourante = yylex();  
    //nom_token( uniteCourante, nom, valeur );
    //printf("%s\t%s\t%s\n", yytext, nom, valeur);
      E();
  } while (uniteCourante != FIN);
  
    printf("La compilation est magnifiquement recursif\n");
  return 0;
}
