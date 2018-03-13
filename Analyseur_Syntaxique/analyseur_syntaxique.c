#include "analyseur_syntaxique.h"

int trace_xml = 0;

void setTraceXml(int trace) {
    trace_xml = trace;
}

/*void setTraceAnalyseur(int trace) {
    trace_analyseur_lexical = trace;
}*/

int consume(int x){
    /*char valeur[10];
    char valeur2[10];
    char nom[10];
    char nom2[10];*/
    //nom_token(x,nom,valeur);

    if(uniteCourante == x){
    	char nom[100], valeur[100];
    
      //nom_token( uniteCourante, nom, valeur );
      //printf("%s\t%s\t%s\n", yytext, nom, valeur);
        affiche_feuille(uniteCourante, trace_xml);
        uniteCourante = yylex();
        return 1;
    }/*else{
        nom_token(uniteCourante,nom2,valeur2);
        fprintf(stderr,"%s expected %s found\n", valeur, valeur2);
    }  */ 

    return 0;
}

void balise_ouvrante(const char *fonction) { 
    affiche_balise_ouvrante(fonction, trace_xml);
}

void balise_fermante(const char *fonction) {
    affiche_balise_fermante(fonction, trace_xml);
}

//Procedures

void programme(){
    sortie_xml=fopen("my_file", "w");
    balise_ouvrante(__FUNCTION__);
    if(est_premier(uniteCourante,_optDecVariables_) || est_premier(uniteCourante, _listeDecFonctions_) || est_suivant(uniteCourante, _programme_)) {
        optDecVariables();
        listeDecFonctions();
        balise_fermante(__FUNCTION__); return;
    }else{
        printf("programme");
        exit(-1);
    }
}

void optDecVariables(){
    balise_ouvrante(__FUNCTION__);
    if(est_premier(uniteCourante,_listeDecVariables_)){
        listeDecVariables();
        if(!consume(POINT_VIRGULE)){
            erreur("optDecVariables ;");
        }
        balise_fermante(__FUNCTION__); return;
    }else if(est_suivant(uniteCourante,_optDecVariables_)){
        balise_fermante(__FUNCTION__); return;
    }
    else{
        erreur("optDecVariables");
    }
}

void listeDecVariables(){
    balise_ouvrante(__FUNCTION__);
    if(est_premier(uniteCourante,_declarationVariable_)){
        declarationVariable();
        listeDecVariablesBis();
        balise_fermante(__FUNCTION__); return;
    }else{
        erreur("listeDecVariables");
    }
}


void listeDecVariablesBis(){
    balise_ouvrante(__FUNCTION__);
    if(consume(VIRGULE)){
        declarationVariable();
        listeDecVariablesBis();
        balise_fermante(__FUNCTION__); return;
    }else if(est_suivant(uniteCourante,_listeDecVariablesBis_)){
        balise_fermante(__FUNCTION__); return;
    }
    else{
        erreur("listeDecVariablesBis");
    }
}

void declarationVariable(){
    balise_ouvrante(__FUNCTION__);
    if(consume(ENTIER)){
        if(consume(ID_VAR)){
            optTailleTableau();
        }else{
            erreur("declarationVariable");
        }
        balise_fermante(__FUNCTION__); return;
    }else{
        erreur("declarationVariable");
    }
}

void optTailleTableau(){
    balise_ouvrante(__FUNCTION__);
    if(consume(CROCHET_OUVRANT)){
        if(consume(NOMBRE)){
            if(!consume(CROCHET_FERMANT)){
                erreur("optTailleTableau");
            }
        }else{
            erreur("optTailleTableau");
        }
        balise_fermante(__FUNCTION__); return;
    }else if(est_suivant(uniteCourante,_optTailleTableau_)){
        balise_fermante(__FUNCTION__); return;
    }
    else{
        erreur("optTailleTableau");
    }
}

void listeDecFonctions(){
    balise_ouvrante(__FUNCTION__);
    if(est_premier(uniteCourante,_declarationFonction_)){
        declarationFonction();
        listeDecFonctions();
        balise_fermante(__FUNCTION__); return;
    }else if(est_suivant(uniteCourante,_listeDecFonctions_)){
        balise_fermante(__FUNCTION__); return;
    }
    else{
        erreur("listeDecFonctions");
    }
}

void declarationFonction(){
    balise_ouvrante(__FUNCTION__);
    if(consume(ID_FCT)){
        listeParam();
        optDecVariables();
        instructionBloc();
        balise_fermante(__FUNCTION__); return;
    }else{
        erreur("declarationFonction");
    }
}

void listeParam(){
    balise_ouvrante(__FUNCTION__);
    if(consume(PARENTHESE_OUVRANTE)){
        optListeDecVariables();
        if(!consume(PARENTHESE_FERMANTE)){
            erreur("listeParam");
        }
        balise_fermante(__FUNCTION__); return;
    }else{
        erreur("listeParam");
    }
}

void optListeDecVariables(){
    balise_ouvrante(__FUNCTION__);
    if(est_premier(uniteCourante,_listeDecVariables_)){
        listeDecVariables();
        balise_fermante(__FUNCTION__); return;
    }else if(est_suivant(uniteCourante,_optListeDecVariables_)){
        balise_fermante(__FUNCTION__); return;
    }else{
        erreur("optListeDecVariables");
    }
}

void instruction(){
    balise_ouvrante(__FUNCTION__);
    if(est_premier(uniteCourante,_instructionAffect_)){
        instructionAffect();
        balise_fermante(__FUNCTION__); return;
    }else if(est_premier(uniteCourante,_instructionBloc_)){
        instructionBloc();
        balise_fermante(__FUNCTION__); return;
    }else if(est_premier(uniteCourante,_instructionSi_)){
        instructionSi();
        balise_fermante(__FUNCTION__); return;
    }else if(est_premier(uniteCourante,_instructionTantque_)){
        instructionTantque();
        balise_fermante(__FUNCTION__); return;
    }else if(est_premier(uniteCourante,_instructionAppel_)){
        instructionAppel();
        balise_fermante(__FUNCTION__); return;
    }else if(est_premier(uniteCourante,_instructionRetour_)){
        instructionRetour();
        balise_fermante(__FUNCTION__); return;
    }else if(est_premier(uniteCourante,_instructionEcriture_)){
        instructionEcriture();
        balise_fermante(__FUNCTION__); return;
    }else if(est_premier(uniteCourante,_instructionVide_)){
        instructionVide();
        balise_fermante(__FUNCTION__); return;
    }else{
        erreur("instruction");
    }
}

void instructionAffect(){
    balise_ouvrante(__FUNCTION__);
    if(est_premier(uniteCourante,_var_)){
        var();
        if(consume(EGAL)){
            expression();
            if(!consume(POINT_VIRGULE)){
                erreur("instructionAffect");
            }
        }else{
            erreur("instructionAffect");
        }
        balise_fermante(__FUNCTION__); return;
    }else{
        erreur("instructionAffect");
    }
}

void instructionBloc(){
    balise_ouvrante(__FUNCTION__);
    if(consume(ACCOLADE_OUVRANTE)){
        listeInstructions();
        if(!consume(ACCOLADE_FERMANTE)){
            erreur("instructionBloc");
        }
        balise_fermante(__FUNCTION__); return;
    }else{
        erreur("instructionBloc");
    }
}

void listeInstructions(){
    balise_ouvrante(__FUNCTION__);
    if(est_premier(uniteCourante,_instruction_)){
        instruction();
        listeInstructions();
        balise_fermante(__FUNCTION__); return;
    }else if(est_suivant(uniteCourante,_listeInstructions_)){
        balise_fermante(__FUNCTION__); return;
    }
    else{
        erreur("listeInstructions");
    }
}

void instructionSi(){
    balise_ouvrante(__FUNCTION__);
    if(consume(SI)){
        expression();
        if(consume(ALORS)){
            instructionBloc();
            optSinon();
        }else{
            erreur("instructionSi");
        }
        balise_fermante(__FUNCTION__); return;
    }else{
        erreur("instructionSi");
    }
}

void optSinon(){
    balise_ouvrante(__FUNCTION__);
    if(consume(SINON)){
        instructionBloc();
        balise_fermante(__FUNCTION__); return;
    }else if(est_suivant(uniteCourante,_optSinon_)){
        balise_fermante(__FUNCTION__); return;
    }
    else{
        erreur("optSinon");
    }
}

void instructionTantque(){
    balise_ouvrante(__FUNCTION__);
    if(consume(TANTQUE)){
        expression();
        if(consume(FAIRE)){
            instructionBloc();
        }else{
            erreur("instructionTantque");
        }
        balise_fermante(__FUNCTION__); return;
    }else{
        erreur("instructionTantque");
    }
}

void instructionAppel(){
    balise_ouvrante(__FUNCTION__);
    if(est_premier(uniteCourante,_appelFct_)){
        appelFct();
        if(!consume(POINT_VIRGULE)){
            erreur("instructionAppel");
        }
        balise_fermante(__FUNCTION__); return;
    }else{
        erreur("instructionAppel");
    }
}

void instructionRetour(){
    balise_ouvrante(__FUNCTION__);
    if(consume(RETOUR)){
        expression();
        if(!consume(POINT_VIRGULE)){
            erreur("instructionRetour");
        }
        balise_fermante(__FUNCTION__); return;
    }else{
        erreur("instructionRetour");
    }
}

void instructionEcriture(){
    balise_ouvrante(__FUNCTION__);
    if(consume(ECRIRE)){
        if(consume(PARENTHESE_OUVRANTE)){
            expression();
            if(consume(PARENTHESE_FERMANTE)){
                if(!consume(POINT_VIRGULE)){
                    erreur("instructionEcriture");
                }
            }else{
                erreur("instructionEcriture");
            }
        }else{
            erreur("instructionEcriture");
        }
        balise_fermante(__FUNCTION__); return;
    }else{
        erreur("instructionEcriture");
    }
}

void instructionVide(){
    balise_ouvrante(__FUNCTION__);
    if(!consume(POINT_VIRGULE)){
        ERREUR();
    }
    else {
        balise_fermante(__FUNCTION__); return;
    }
}

void expression(){
    balise_ouvrante(__FUNCTION__);
    if(est_premier(uniteCourante,_conjonction_)){
        conjonction();
        expressionBis();
		balise_fermante(__FUNCTION__); return;
    }else{
        ERREUR();
    }
}

void expressionBis(){
    balise_ouvrante(__FUNCTION__);
    if(consume(OU)){
        conjonction();
        expressionBis();
        balise_fermante(__FUNCTION__); return;
	}else if(consume(INTERROGATION)){
		expression();
		if(consume(DEUXPOINTS)) {
			expression();
		}
		balise_fermante(__FUNCTION__); return;
    }else if(est_suivant(uniteCourante,_expressionBis_)){
        balise_fermante(__FUNCTION__); return;
    }
    else{
        ERREUR();
    }
}

void conjonction(){
    balise_ouvrante(__FUNCTION__);
    if(est_premier(uniteCourante,_negation_)){
        comparaison();
        conjonctionBis();
        balise_fermante(__FUNCTION__); return;
    }else{
        ERREUR();
    }
}

void conjonctionBis(){
    balise_ouvrante(__FUNCTION__);
    if(consume(ET)){
        comparaison();
        conjonctionBis();
        balise_fermante(__FUNCTION__); return;
    }else if(est_suivant(uniteCourante,_conjonctionBis_)){
        balise_fermante(__FUNCTION__); return;
    }
    else{
        ERREUR();
    }
}

void negation(){
    balise_ouvrante(__FUNCTION__);
    if(consume(NON)){
        negation();
        balise_fermante(__FUNCTION__); return;
    }else if(est_premier(uniteCourante,_facteur_)){
        facteur();
        balise_fermante(__FUNCTION__); return;
    }else{
        ERREUR();
    }
}

void comparaison(){
    balise_ouvrante(__FUNCTION__);
    if(est_premier(uniteCourante,_expArith_)){
        expArith();
        comparaisonBis();
        balise_fermante(__FUNCTION__); return;
    }else{
        ERREUR();
    }
}

void comparaisonBis(){
    balise_ouvrante(__FUNCTION__);
    if(consume(EGAL)){
        expArith();
        comparaisonBis();
        balise_fermante(__FUNCTION__); return;
    }else if(consume(INFERIEUR)){
        expArith();
        comparaisonBis();
        balise_fermante(__FUNCTION__); return;
    }else if(est_suivant(uniteCourante,_comparaisonBis_)){
        balise_fermante(__FUNCTION__); return;
    }
    else{
        ERREUR();
    }
}

void expArith(){
    balise_ouvrante(__FUNCTION__);
    if(est_premier(uniteCourante,_terme_)){
        terme();
        expArithBis();
        balise_fermante(__FUNCTION__); return;
    }else{
        ERREUR();
    }
}

void expArithBis(){
    balise_ouvrante(__FUNCTION__);
    if(consume(PLUS)){
        terme();
        expArithBis();
        balise_fermante(__FUNCTION__); return;
    }else if(consume(MOINS)){
        terme();
        expArithBis();
        balise_fermante(__FUNCTION__); return;
    }else if(est_suivant(uniteCourante,_expArithBis_)){
        balise_fermante(__FUNCTION__); return;
    }
    else{
        ERREUR();
    }
}

void terme(){
    balise_ouvrante(__FUNCTION__);
    if(est_premier(uniteCourante,_negation_)){
        negation();
        termeBis();
        balise_fermante(__FUNCTION__); return;
    }else{
        ERREUR();
    }
}

void termeBis(){
    balise_ouvrante(__FUNCTION__);
    if(consume(FOIS)){
        negation();
        termeBis();
        balise_fermante(__FUNCTION__); return;
    }else if(consume(DIVISE)){
        negation();
        termeBis();
        balise_fermante(__FUNCTION__); return;
    }else if(est_suivant(uniteCourante,_termeBis_)){
        balise_fermante(__FUNCTION__); return;
    }
    else{
        ERREUR();
    }
}

void facteur(){
    balise_ouvrante(__FUNCTION__);
    if(consume(PARENTHESE_OUVRANTE)){
        expression();
        if(!consume(PARENTHESE_FERMANTE)){
            ERREUR();
        }
        balise_fermante(__FUNCTION__); return;
    }else if(consume(NOMBRE)){
        balise_fermante(__FUNCTION__); return;
    }
    else if(est_premier(uniteCourante,_appelFct_)){
        appelFct();
        balise_fermante(__FUNCTION__); return;
    }else if(est_premier(uniteCourante,_var_)){
        var();
        balise_fermante(__FUNCTION__); return;
    }else if(consume(LIRE)){
        if(consume(PARENTHESE_OUVRANTE)){
            if(!consume(PARENTHESE_FERMANTE)){
                ERREUR();
            }
        }else{
            ERREUR();
        }
        balise_fermante(__FUNCTION__); return;
    }else{
        ERREUR();
    }
}

void var(){
    balise_ouvrante(__FUNCTION__);
    if(consume(ID_VAR)){
        optIndice();
        balise_fermante(__FUNCTION__); return;
    }else{
        ERREUR();
    }
}

void optIndice(){
    balise_ouvrante(__FUNCTION__);
    if(consume(CROCHET_OUVRANT)){
        expression();
        if(!consume(CROCHET_FERMANT)){
            ERREUR();
        }
        balise_fermante(__FUNCTION__); return;
    }else if(est_suivant(uniteCourante,_optIndice_)){
        balise_fermante(__FUNCTION__); return;
    }
    else{
        ERREUR();
    }
}

void appelFct(){
    balise_ouvrante(__FUNCTION__);
    if(consume(ID_FCT)){
        if(consume(PARENTHESE_OUVRANTE)){
            listeExpressions();
            if(!consume(PARENTHESE_FERMANTE)){
                ERREUR();
            }
        }else{
            ERREUR();
        }
        balise_fermante(__FUNCTION__); return;
    }else{
        ERREUR();
    }
}

void listeExpressions(){
    balise_ouvrante(__FUNCTION__);
    if(est_premier(uniteCourante,_expression_)){
        expression();
        listeExpressionsBis();
        balise_fermante(__FUNCTION__); return;
    }else if(est_suivant(uniteCourante,_listeExpressions_)){
        balise_fermante(__FUNCTION__); return;
    }
    else{
        ERREUR();
    }
}

void listeExpressionsBis(){
    balise_ouvrante(__FUNCTION__);
    if(consume(VIRGULE)){
        expression();
        listeExpressionsBis();
        balise_fermante(__FUNCTION__); return;
    }else if(est_suivant(uniteCourante,_listeExpressionsBis_)){
        balise_fermante(__FUNCTION__); return;
    }
    else{
        ERREUR();
    }
}
