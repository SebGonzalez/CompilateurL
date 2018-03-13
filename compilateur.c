#include "./Analyseur_Syntaxique/analyseur_syntaxique.h"

int fichier_utilise = 0;

void charger_fichier(char *nom) {
  fichier_utilise = 0;
  yyin = fopen(nom, "r");
    if(yyin == NULL){
      fprintf(stderr, "impossible d'ouvrir le fichier %s\n", nom);
      exit(1);
    }
}

int main(int argc, char **argv) {  
  //char nom[100];
  //char valeur[100];  
  int trace_analyseur_lexical = 0;
  int trace_xml = 0;

  charger_fichier(argv[argc-1]);

  for(int i=1; i<argc-1; i++) {
    if(strcmp("-l", argv[i]) == 0) {
      trace_analyseur_lexical = 1;
    }
    else if(strcmp("-s", argv[i]) == 0) {
      trace_xml = 1;
      setTraceXml(1);
    }
    else if(strcmp("-a", argv[i]) == 0) {
      trace_analyseur_lexical = 1;
      trace_xml = 1;
       setTraceXml(1);
    }
  }
  initialise_premiers();
  initialise_suivants();

  if(trace_analyseur_lexical) {
    fichier_utilise = 1;
    do {
      uniteCourante = yylex();  
      affiche_analyseur_lexical(uniteCourante, trace_analyseur_lexical);
    } while (uniteCourante != FIN);
  }
  if(trace_xml) {
    if(fichier_utilise == 1)  charger_fichier(argv[argc-1]);
    uniteCourante = yylex(); 
    programme();
  }
  return 0;
}
