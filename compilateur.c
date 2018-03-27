#include "./Analyseur_Syntaxique/analyseur_syntaxique.h"
#include "./Analyseur_Semantique/analyseur_semantique.h"

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
  (void)trace_xml;
  int arbre_abstrait = 0;

  charger_fichier(argv[argc-1]);

  for(int i=1; i<argc-1; i++) {
    if(strcmp("-l", argv[i]) == 0) {
      trace_analyseur_lexical = 1;
    }
    else if(strcmp("-a", argv[i]) == 0) {
      arbre_abstrait = 1;
    }
    else if(strcmp("-s", argv[i]) == 0) {
      trace_xml = 1;
      setTraceXml(1);
    }
    else if(strcmp("-all", argv[i]) == 0) {
      trace_analyseur_lexical = 1;
      trace_xml = 1;
      arbre_abstrait = 1;
       setTraceXml(1);
       setTraceTableSymbole();
    }
    else if(strcmp("-t", argv[i]) == 0){
      setTraceTableSymbole();
    }
    else if(strcmp("-n", argv[i]) == 0){
      setTraceCode();
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

  if(fichier_utilise == 1)  charger_fichier(argv[argc-1]);
  uniteCourante = yylex(); 
  n_prog *n = programme();
  fichier_utilise = 1;

  if(arbre_abstrait)
      affiche_n_prog(n);

  parcours_n_prog(n);

  return 0;
}
