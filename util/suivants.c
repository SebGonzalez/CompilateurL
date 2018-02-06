#include "symboles.h"
#include "suivants.h"

void initialise_suivants(void){
  int i,j;
  
  // Initialiser toutes les cases du tableau à 0
  for(i=0; i <= NB_NON_TERMINAUX; i++)
    for(j=0; j <= NB_TERMINAUX; j++)
      suivants[i][j] = 0;
      
  //exemple      
  suivants[_programme_][FIN] = 1;
  suivants[_optDecVariables_][ID_FCT] = 1;
  suivants[_optDecVariables_][FIN] = 1;
  suivants[_listeDecVariables_][POINT_VIRGULE] = 1;
  suivants[_listeDecVariables_][PARENTHESE_FERMANTE] = 1;
  suivants[_listeDecVariablesBis_][POINT_VIRGULE] = 1;
  suivants[_listeDecVariablesBis_][PARENTHESE_FERMANTE] = 1;
  suivants[_declarationVariable_][VIRGULE] = 1;
  suivants[_optTailleTableau_][VIRGULE] = 1;
  //Provisoire
  suivants[_optTailleTableau_][POINT_VIRGULE] = 1;
  suivants[_listeDecFonctions_][FIN] = 1;
  suivants[_declarationFonction_][ID_FCT] = 1;
  suivants[_listeParam_][FIN] = 1;
  suivants[_optListeDecVariables_][PARENTHESE_FERMANTE] = 1;

  suivants[_instruction_][ID_VAR] = 1;
  suivants[_instruction_][ACCOLADE_OUVRANTE] = 1;
  suivants[_instruction_][SI] = 1;
  suivants[_instruction_][TANTQUE] = 1;
  suivants[_instruction_][ID_FCT] = 1;
  suivants[_instruction_][RETOUR] = 1;
  suivants[_instruction_][ECRIRE] = 1;
  suivants[_instruction_][POINT_VIRGULE] = 1;

  suivants[_instructionAffect_][ID_VAR] = 1;
  suivants[_instructionAffect_][ACCOLADE_OUVRANTE] = 1;
  suivants[_instructionAffect_][SI] = 1;
  suivants[_instructionAffect_][TANTQUE] = 1;
  suivants[_instructionAffect_][ID_FCT] = 1;
  suivants[_instructionAffect_][RETOUR] = 1;
  suivants[_instructionAffect_][ECRIRE] = 1;
  suivants[_instructionAffect_][POINT_VIRGULE] = 1;

  suivants[_instructionBloc_][ID_FCT] = 1;
  suivants[_instructionBloc_][ID_VAR] = 1;
  suivants[_instructionBloc_][ACCOLADE_OUVRANTE] = 1;
  suivants[_instructionBloc_][SI] = 1;
  suivants[_instructionBloc_][TANTQUE] = 1;
  suivants[_instructionBloc_][RETOUR] = 1;
  suivants[_instructionBloc_][ECRIRE] = 1;
  suivants[_instructionBloc_][POINT_VIRGULE] = 1;
  suivants[_instructionBloc_][SINON] = 1;

  suivants[_listeInstructions_][ACCOLADE_FERMANTE] = 1;

  suivants[_instructionSi_][ID_VAR] = 1;
  suivants[_instructionSi_][ACCOLADE_OUVRANTE] = 1;
  suivants[_instructionSi_][SI] = 1;
  suivants[_instructionSi_][TANTQUE] = 1;
  suivants[_instructionSi_][ID_FCT] = 1;
  suivants[_instructionSi_][RETOUR] = 1;
  suivants[_instructionSi_][ECRIRE] = 1;
  suivants[_instructionSi_][POINT_VIRGULE] = 1;

  suivants[_optSinon_][ID_VAR] = 1;
  suivants[_optSinon_][ACCOLADE_OUVRANTE] = 1;
  suivants[_optSinon_][SI] = 1;
  suivants[_optSinon_][TANTQUE] = 1;
  suivants[_optSinon_][ID_FCT] = 1;
  suivants[_optSinon_][RETOUR] = 1;
  suivants[_optSinon_][ECRIRE] = 1;
  suivants[_optSinon_][POINT_VIRGULE] = 1;

  suivants[_instructionTantque_][ID_VAR] = 1;
  suivants[_instructionTantque_][ACCOLADE_OUVRANTE] = 1;
  suivants[_instructionTantque_][SI] = 1;
  suivants[_instructionTantque_][TANTQUE] = 1;
  suivants[_instructionTantque_][ID_FCT] = 1;
  suivants[_instructionTantque_][RETOUR] = 1;
  suivants[_instructionTantque_][ECRIRE] = 1;
  suivants[_instructionTantque_][POINT_VIRGULE] = 1;

  suivants[_instructionAppel_][ID_VAR] = 1;
  suivants[_instructionAppel_][ACCOLADE_OUVRANTE] = 1;
  suivants[_instructionAppel_][SI] = 1;
  suivants[_instructionAppel_][TANTQUE] = 1;
  suivants[_instructionAppel_][ID_FCT] = 1;
  suivants[_instructionAppel_][RETOUR] = 1;
  suivants[_instructionAppel_][ECRIRE] = 1;
  suivants[_instructionAppel_][POINT_VIRGULE] = 1;

  suivants[_instructionRetour_][ID_VAR] = 1;
  suivants[_instructionRetour_][ACCOLADE_OUVRANTE] = 1;
  suivants[_instructionRetour_][SI] = 1;
  suivants[_instructionRetour_][TANTQUE] = 1;
  suivants[_instructionRetour_][ID_FCT] = 1;
  suivants[_instructionRetour_][RETOUR] = 1;
  suivants[_instructionRetour_][ECRIRE] = 1;
  suivants[_instructionRetour_][POINT_VIRGULE] = 1;

  suivants[_instructionEcriture_][ID_VAR] = 1;
  suivants[_instructionEcriture_][ACCOLADE_OUVRANTE] = 1;
  suivants[_instructionEcriture_][SI] = 1;
  suivants[_instructionEcriture_][TANTQUE] = 1;
  suivants[_instructionEcriture_][ID_FCT] = 1;
  suivants[_instructionEcriture_][RETOUR] = 1;
  suivants[_instructionEcriture_][ECRIRE] = 1;
  suivants[_instructionEcriture_][POINT_VIRGULE] = 1;

  suivants[_instructionVide_][ID_VAR] = 1;
  suivants[_instructionVide_][ACCOLADE_OUVRANTE] = 1;
  suivants[_instructionVide_][SI] = 1;
  suivants[_instructionVide_][TANTQUE] = 1;
  suivants[_instructionVide_][ID_FCT] = 1;
  suivants[_instructionVide_][RETOUR] = 1;
  suivants[_instructionVide_][ECRIRE] = 1;
  suivants[_instructionVide_][POINT_VIRGULE] = 1;

  suivants[_expression_][POINT_VIRGULE] = 1;
  suivants[_expression_][ALORS] = 1;
  suivants[_expression_][FAIRE] = 1;
  suivants[_expression_][PARENTHESE_FERMANTE] = 1;
  suivants[_expression_][CROCHET_FERMANT] = 1;
  suivants[_expression_][VIRGULE] = 1;
  suivants[_expressionBis_][POINT_VIRGULE] = 1;
  suivants[_expressionBis_][ALORS] = 1;
  suivants[_expressionBis_][FAIRE] = 1;
  suivants[_expressionBis_][PARENTHESE_FERMANTE] = 1;
  suivants[_expressionBis_][CROCHET_FERMANT] = 1;
  suivants[_expressionBis_][VIRGULE] = 1;
  suivants[_conjonction_][OU] = 1;
  suivants[_conjonctionBis_][OU] = 1;
  suivants[_negation_][ET] = 1;
  suivants[_comparaison_][ET] = 1;
  suivants[_comparaisonBis_][ET] = 1;
  suivants[_expArith_][EGAL] = 1;
  suivants[_expArith_][INFERIEUR] = 1;
  suivants[_expArithBis_][EGAL] = 1;
  suivants[_expArithBis_][INFERIEUR] = 1;
  suivants[_terme_][PLUS] = 1;
  suivants[_terme_][MOINS] = 1;
  suivants[_termeBis_][PLUS] = 1;
  suivants[_termeBis_][MOINS] = 1;
  suivants[_facteur_][FOIS] = 1;
  suivants[_facteur_][DIVISE] = 1;
  suivants[_var_][EGAL] = 1;
  suivants[_var_][FOIS] = 1;
  suivants[_var_][DIVISE] = 1;
  suivants[_optIndice_][EGAL] = 1;
  suivants[_optIndice_][FOIS] = 1;
  suivants[_optIndice_][DIVISE] = 1;
  suivants[_appelFct_][FOIS] = 1;
  suivants[_appelFct_][DIVISE] = 1;
  suivants[_appelFct_][POINT_VIRGULE] = 1;
  suivants[_listeExpressions_][PARENTHESE_FERMANTE] = 1;
  suivants[_listeExpressionsBis_][PARENTHESE_FERMANTE] = 1;
  
  // TODO: Compléter le tableau suivants ici
}

int est_suivant(int terminal, int non_terminal)
{
	printf("%d %d\n", terminal, non_terminal);
  return suivants[non_terminal][terminal];
}