#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../util/symboles.h"
#include "../util/util.h"
#include "../util/premiers.h"
#include "../util/suivants.h"

int yylex(void);
extern char *yytext;
FILE *yyin;

//Prototypes

void programme();
void optDecVariables();
void listeDecVariables();
void listeDecVariablesBis();
void declarationVariable();
void optTailleTableau();
void listeDecFonctions();
void declarationFonction();
void listeParam();
void optListeDecVariables();
void instruction();
void instructionAffect();
void instructionBloc();
void listeInstructions();
void instructionSi();
void optSinon();
void instructionTantque();
void instructionAppel();
void instructionRetour();
void instructionEcriture();
void instructionVide();
void expression();
void expressionBis();
void conjonction();
void conjonctionBis();
void negation();
void comparaison();
void comparaisonBis();
void expArith();
void expArithBis();
void terme();
void termeBis();
void facteur();
void var();
void optIndice();
void appelFct();
void listeExpressions();
void listeExpressionsBis();

int uniteCourante;

#define ERREUR() erreur(__FUNCTION__);
