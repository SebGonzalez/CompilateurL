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
    	//char nom[100], valeur[100];
    
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

n_prog *programme(){
    //sortie_xml=fopen("my_file", "w");
    n_prog *$$ = NULL;
    n_l_dec *$1 = NULL;
    n_l_dec *$2 = NULL;
    balise_ouvrante(__FUNCTION__);
    if(est_premier(uniteCourante,_optDecVariables_) || est_premier(uniteCourante, _listeDecFonctions_) || est_suivant(uniteCourante, _programme_)) {
        $1 = optDecVariables();
        $2 = listeDecFonctions();
        $$ = cree_n_prog($1, $2);
        balise_fermante(__FUNCTION__);
        return $$;
    }else{
        printf("programme");
        exit(-1);
    }
}

n_l_dec *optDecVariables(){
    n_l_dec *$$ = NULL;

    balise_ouvrante(__FUNCTION__);
    if(est_premier(uniteCourante,_listeDecVariables_)){
        $$ = listeDecVariables();
        if(!consume(POINT_VIRGULE)){
            erreur("optDecVariables ;");
        }
        balise_fermante(__FUNCTION__);
        return $$;
    }else if(est_suivant(uniteCourante,_optDecVariables_)){
        balise_fermante(__FUNCTION__);
        return NULL;
    }
    else{
        erreur("optDecVariables");
    }
}

n_l_dec *listeDecVariables(){
    n_l_dec *$$ = NULL;
    n_dec *$1 = NULL;
    n_l_dec *$2 = NULL;


    balise_ouvrante(__FUNCTION__);
    if(est_premier(uniteCourante,_declarationVariable_)){
        $1 = declarationVariable();
        $2 = listeDecVariablesBis();
        $$ = cree_n_l_dec($1, $2);
        balise_fermante(__FUNCTION__);
        return $$;
    }else{
        erreur("listeDecVariables");
    }
}


n_l_dec *listeDecVariablesBis(){
    n_l_dec *$$ = NULL;
    n_dec *$1 = NULL;
    n_l_dec *$2 = NULL;

    balise_ouvrante(__FUNCTION__);
    if(consume(VIRGULE)){
        $1 = declarationVariable();
        $2 = listeDecVariablesBis();
        $$ = cree_n_l_dec($1, $2);
        balise_fermante(__FUNCTION__);
        return $$;
    }else if(est_suivant(uniteCourante,_listeDecVariablesBis_)){
        balise_fermante(__FUNCTION__);
        return NULL;
    }
    else{
        erreur("listeDecVariablesBis");
    }
}

n_dec *declarationVariable(){
    n_dec *$$ = NULL;
    int $2;
    balise_ouvrante(__FUNCTION__);
    if(consume(ENTIER)){

        char *nom = malloc(sizeof(char *));
        strcpy(nom, yytext);

        if(consume(ID_VAR)){
            int $2 = optTailleTableau();
            if($2 == -1) $$ = cree_n_dec_var(nom);
            else $$ = cree_n_dec_tab(nom, $2);
        }else{
            erreur("declarationVariable");
        }
        balise_fermante(__FUNCTION__);
        return $$;
    }else{
        erreur("declarationVariable");
    }
}

int optTailleTableau(){
    int taille;
	char *nombre = malloc(sizeof(char *));
    balise_ouvrante(__FUNCTION__);
    if(consume(CROCHET_OUVRANT)){
        if(consume(NOMBRE)){
            if(!consume(CROCHET_FERMANT)){
                erreur("optTailleTableau");
            }

            strcpy(nombre, yytext);
        }else{
            erreur("optTailleTableau");
        }
        balise_fermante(__FUNCTION__); 
        return atoi(nombre);
    }else if(est_suivant(uniteCourante,_optTailleTableau_)){
        balise_fermante(__FUNCTION__);
        return -1;
    }
    else{
        erreur("optTailleTableau");
    }
}

n_l_dec *listeDecFonctions(){
    n_l_dec *$$ = NULL;
    n_dec *$1;
    n_l_dec *$2;
    balise_ouvrante(__FUNCTION__);
    if(est_premier(uniteCourante,_declarationFonction_)){
        $1 = declarationFonction();
        $2 = listeDecFonctions();
        $$ = cree_n_l_dec($1, $2);
        balise_fermante(__FUNCTION__);
        return $$;
    }else if(est_suivant(uniteCourante,_listeDecFonctions_)){
        balise_fermante(__FUNCTION__);
        return NULL;
    }
    else{
        erreur("listeDecFonctions");
    }
}

n_dec *declarationFonction(){
    n_dec *$$ = NULL;
    n_l_dec *$1 = NULL;
    n_l_dec *$2 = NULL;
    n_instr *$3 = NULL;
    balise_ouvrante(__FUNCTION__);

    char *nom = malloc(sizeof(char *));
    strcpy(nom, yytext);
    if(consume(ID_FCT)){
        $1 = listeParam();
        $2 = optDecVariables();
        $3 = instructionBloc();
        $$ = cree_n_dec_fonc(nom, $1, $2, $3);
        balise_fermante(__FUNCTION__);
        return $$;
    }else{
        erreur("declarationFonction");
    }
}

n_l_dec *listeParam(){
	n_l_dec *$$ = NULL;

    balise_ouvrante(__FUNCTION__);
    if(consume(PARENTHESE_OUVRANTE)){
        $$ = optListeDecVariables();
        if(!consume(PARENTHESE_FERMANTE)){
            erreur("listeParam");
        }
        balise_fermante(__FUNCTION__);
        return $$;
    }else{
        erreur("listeParam");
    }
}

n_l_dec *optListeDecVariables(){
	n_l_dec *$$ = NULL;

    balise_ouvrante(__FUNCTION__);
    if(est_premier(uniteCourante,_listeDecVariables_)){
        $$ = listeDecVariables();
        balise_fermante(__FUNCTION__);
        return $$;
    }else if(est_suivant(uniteCourante,_optListeDecVariables_)){
        balise_fermante(__FUNCTION__);
        return NULL;
    }else{
        erreur("optListeDecVariables");
    }
}

n_instr *instruction(){
	n_instr *$$ = NULL;

    balise_ouvrante(__FUNCTION__);
    if(est_premier(uniteCourante,_instructionAffect_)){
        $$ = instructionAffect();
        balise_fermante(__FUNCTION__); 
        return $$;
    }else if(est_premier(uniteCourante,_instructionBloc_)){
        $$ = instructionBloc();
        balise_fermante(__FUNCTION__);
        return $$;
    }else if(est_premier(uniteCourante,_instructionSi_)){
        $$ = instructionSi();
        balise_fermante(__FUNCTION__);
        return $$;
    }else if(est_premier(uniteCourante,_instructionTantque_)){
        $$ = instructionTantque();
        balise_fermante(__FUNCTION__);
        return $$;
    }else if(est_premier(uniteCourante,_instructionAppel_)){
        $$ = instructionAppel();
        balise_fermante(__FUNCTION__);
        return $$;
    }else if(est_premier(uniteCourante,_instructionRetour_)){
        $$ = instructionRetour();
        balise_fermante(__FUNCTION__);
        return $$;
    }else if(est_premier(uniteCourante,_instructionEcriture_)){
        $$ = instructionEcriture();
        balise_fermante(__FUNCTION__);
        return $$;
    }else if(est_premier(uniteCourante,_instructionVide_)){
        $$ = instructionVide();
        balise_fermante(__FUNCTION__);
        return $$;
    }else{
        erreur("instruction");
    }
}

n_instr *instructionAffect(){
	n_instr *$$ = NULL;
	n_var *$1 = NULL;
	n_exp *$2 = NULL;

    balise_ouvrante(__FUNCTION__);
    if(est_premier(uniteCourante,_var_)){
        $1 = var();
        if(consume(EGAL)){
            $2 = expression();
            if(!consume(POINT_VIRGULE)){
                erreur("instructionAffect");
            }
        }else{
            erreur("instructionAffect");
        }
        $$ = cree_n_instr_affect($1, $2);
        balise_fermante(__FUNCTION__);
        return $$;
    }else{
        erreur("instructionAffect");
    }
}

n_instr *instructionBloc(){
	n_instr *$$ = NULL;
	n_l_instr *$1 = NULL;

    balise_ouvrante(__FUNCTION__);
    if(consume(ACCOLADE_OUVRANTE)){
        $1 = listeInstructions();
        if(!consume(ACCOLADE_FERMANTE)){
            erreur("instructionBloc");
        }
        $$ = cree_n_instr_bloc($1);
        balise_fermante(__FUNCTION__);
        return $$;
    }else{
        erreur("instructionBloc");
    }
}

n_l_instr *listeInstructions(){
	n_l_instr *$$ = NULL;
	n_instr *$1 = NULL;
	n_l_instr *$2 = NULL;

    balise_ouvrante(__FUNCTION__);
    if(est_premier(uniteCourante,_instruction_)){
        $1 = instruction();
        $2 = listeInstructions();
        $$ = cree_n_l_instr($1, $2);
        balise_fermante(__FUNCTION__);
        return $$;
    }else if(est_suivant(uniteCourante,_listeInstructions_)){
        balise_fermante(__FUNCTION__);
        return NULL;
    }
    else{
        erreur("listeInstructions");
    }
}

n_instr *instructionSi(){
	n_instr *$$ = NULL;
	n_exp *$1 = NULL;
	n_instr *$2 = NULL;
	n_instr *$3 = NULL;

    balise_ouvrante(__FUNCTION__);
    if(consume(SI)){
        $1 = expression();
        if(consume(ALORS)){
            $2 = instructionBloc();
            $3 = optSinon();
        }else{
            erreur("instructionSi");
        }
        $$ = cree_n_instr_si($1, $2, $3);
        balise_fermante(__FUNCTION__);
        return $$;
    }else{
        erreur("instructionSi");
    }
}

n_instr *optSinon(){
	n_instr *$$ = NULL;
    balise_ouvrante(__FUNCTION__);
    if(consume(SINON)){
        $$ = instructionBloc();
        balise_fermante(__FUNCTION__);
        return $$;
    }else if(est_suivant(uniteCourante,_optSinon_)){
        balise_fermante(__FUNCTION__);
        return NULL;
    }
    else{
        erreur("optSinon");
    }
}

n_instr *instructionTantque(){
	n_instr *$$ = NULL;
	n_exp *$1 = NULL;
	n_instr *$2 = NULL;

    balise_ouvrante(__FUNCTION__);
    if(consume(TANTQUE)){
        $1 = expression();
        if(consume(FAIRE)){
            $2 = instructionBloc();
        }else{
            erreur("instructionTantque");
        }
        $$ = cree_n_instr_tantque($1, $2);
        balise_fermante(__FUNCTION__);
        return $$;
    }else{
        erreur("instructionTantque");
    }
}

n_instr *instructionAppel(){
	n_instr *$$ = NULL;
	n_appel *$1 = NULL;

    balise_ouvrante(__FUNCTION__);
    if(est_premier(uniteCourante,_appelFct_)){
        $1 = appelFct();
        if(!consume(POINT_VIRGULE)){
            erreur("instructionAppel");
        }
        $$ = cree_n_instr_appel($1);
        balise_fermante(__FUNCTION__);
        return $$;
    }else{
        erreur("instructionAppel");
    }
}

n_instr *instructionRetour(){
	n_instr *$$ = NULL;
	n_exp *$1 = NULL;

    balise_ouvrante(__FUNCTION__);
    if(consume(RETOUR)){
        $1 = expression();
        if(!consume(POINT_VIRGULE)){
            erreur("instructionRetour");
        }
        $$ = cree_n_instr_retour($1);
        balise_fermante(__FUNCTION__);
        return $$;
    }else{
        erreur("instructionRetour");
    }
}

n_instr *instructionEcriture(){
	n_instr *$$ = NULL;
	n_exp *$1 = NULL;

    balise_ouvrante(__FUNCTION__);
    if(consume(ECRIRE)){
        if(consume(PARENTHESE_OUVRANTE)){
            $1 = expression();
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
        $$ = cree_n_instr_ecrire($1);
        balise_fermante(__FUNCTION__);
        return $$;
    }else{
        erreur("instructionEcriture");
    }
}

n_instr *instructionVide(){
	n_instr *$$ = NULL;

    balise_ouvrante(__FUNCTION__);
    if(!consume(POINT_VIRGULE)){
        ERREUR();
    }
    else {
    	$$ = cree_n_instr_vide();
        balise_fermante(__FUNCTION__);
        return $$;
    }
}

n_exp *expression(){
	n_exp *$$ = NULL;
	n_exp *$1 = NULL;
	n_exp *$2 = NULL;

    balise_ouvrante(__FUNCTION__);
    if(est_premier(uniteCourante,_conjonction_)){
        $1 = conjonction();
        $$ = expressionBis($1);
		balise_fermante(__FUNCTION__);
		return $$;
    }else{
        ERREUR();
    }
}

n_exp *expressionBis(n_exp *herite){
	n_exp *$$ = NULL;
	n_exp *$1 = NULL;
	n_exp *$2 = NULL;
	n_exp *herite_fils = NULL;

    balise_ouvrante(__FUNCTION__);
    if(consume(OU)){
        $1 = conjonction();
        herite_fils = cree_n_exp_op(ou, herite, $1);
        $$ = expressionBis(herite_fils);
        balise_fermante(__FUNCTION__);
        return $$;
	}else if(consume(INTERROGATION)){
		$1 = expression();
		if(consume(DEUXPOINTS)) {
			$2 = expression();
		}
		$$ = cree_n_exp_op($1->type, $1, $2);
		balise_fermante(__FUNCTION__);
		return $$;
    }else if(est_suivant(uniteCourante,_expressionBis_)){
        balise_fermante(__FUNCTION__);
        return NULL;
    }
    else{
        ERREUR();
    }
}

n_exp *conjonction(){
	n_exp *$$ = NULL;
	n_exp *$1 = NULL;
	n_exp *$2 = NULL;
	
    balise_ouvrante(__FUNCTION__);
    if(est_premier(uniteCourante,_negation_)){
        $1 = comparaison();
        $2 = conjonctionBis();
        $$  = cree_n_exp_op($1->type, $1, $2);
        balise_fermante(__FUNCTION__);
        return $$;
    }else{
        ERREUR();
    }
}

n_exp *conjonctionBis(){
	n_exp *$$ = NULL;
	n_exp *$1 = NULL;
	n_exp *$2 = NULL;

    balise_ouvrante(__FUNCTION__);
    if(consume(ET)){
        $1 = comparaison();
        $2 = conjonctionBis();
        $$ = cree_n_exp_op(ET, $1, $2);
        balise_fermante(__FUNCTION__);
        return $$;
    }else if(est_suivant(uniteCourante,_conjonctionBis_)){
        balise_fermante(__FUNCTION__);
        return NULL;
    }
    else{
        ERREUR();
    }
}

n_exp *negation(){
	n_exp *$$ = NULL;
	n_exp *$1 = NULL;

    balise_ouvrante(__FUNCTION__);
    if(consume(NON)){
        $1 = negation();
        $$ = cree_n_exp_op(NON, $1, NULL);
        balise_fermante(__FUNCTION__);
        return $$;
    }else if(est_premier(uniteCourante,_facteur_)){
        $1 = facteur();
        $$ = cree_n_exp_op($1->type, $1, NULL);
        balise_fermante(__FUNCTION__);
        return $$;
    }else{
        ERREUR();
    }
}

n_exp *comparaison(){
	n_exp *$$ = NULL;
	n_exp *$1 = NULL;
	n_exp *$2 = NULL;

    balise_ouvrante(__FUNCTION__);
    if(est_premier(uniteCourante,_expArith_)){
        $1 = expArith();
        $2 = comparaisonBis();
        $$ = cree_n_exp_op($1->type, $1, NULL);
        balise_fermante(__FUNCTION__);
        return $$;
    }else{
        ERREUR();
    }
}

n_exp *comparaisonBis(){
	n_exp *$$ = NULL;
	n_exp *$1 = NULL;
	n_exp *$2 = NULL;

    balise_ouvrante(__FUNCTION__);
    if(consume(EGAL)){
        $1 = expArith();
        $2 = comparaisonBis();
        $$ = cree_n_exp_op(EGAL, $1, NULL);
        balise_fermante(__FUNCTION__);
        return $$;
    }else if(consume(INFERIEUR)){
        $1 = expArith();
        $2 = comparaisonBis();
        $$ = cree_n_exp_op(MOINS, $1, NULL);
        balise_fermante(__FUNCTION__);
        return $$;
    }else if(est_suivant(uniteCourante,_comparaisonBis_)){
        balise_fermante(__FUNCTION__);
        return NULL;
    }
    else{
        ERREUR();
    }
}

n_exp *expArith(){
	n_exp *$$ = NULL;
	n_exp *$1 = NULL;

    balise_ouvrante(__FUNCTION__);
    if(est_premier(uniteCourante,_terme_)){
        $1 = terme();
        $$ = expArithBis($1);
        balise_fermante(__FUNCTION__); 
        return $$;
    }else{
        ERREUR();
    }
}

n_exp *expArithBis(n_exp *herite){
	n_exp *$$ = NULL;
	n_exp *$1 = NULL;
	n_exp *herite_fils;

    balise_ouvrante(__FUNCTION__);
    if(consume(PLUS)){
        $1 = terme();
        herite_fils = cree_n_exp_op(PLUS, herite, $1);
        $$ = expArithBis(herite_fils);
        balise_fermante(__FUNCTION__);
        return $$;
    }else if(consume(MOINS)){
        $1 = terme();
        herite_fils = cree_n_exp_op(MOINS, herite, $1);
        $$ = expArithBis(herite_fils);
        balise_fermante(__FUNCTION__);
        return $$;
    }else if(est_suivant(uniteCourante,_expArithBis_)){
        balise_fermante(__FUNCTION__);
        return herite;
    }
    else{
        ERREUR();
    }
}

n_exp *terme(){
	n_exp *$$ = NULL;
	n_exp *$1 = NULL;

    balise_ouvrante(__FUNCTION__);
    if(est_premier(uniteCourante,_negation_)){
        $1 = negation();
        $$ = termeBis($1);
        balise_fermante(__FUNCTION__);
        return $$;
    }else{
        ERREUR();
    }
}

n_exp *termeBis(n_exp *herite){
	n_exp *$$ = NULL;
	n_exp *$1 = NULL;
	n_exp *herite_fils;

    balise_ouvrante(__FUNCTION__);
    if(consume(FOIS)){
        $1 = negation();
        herite_fils = cree_n_exp_op(FOIS, herite, $1);
        $$ = termeBis(herite_fils);
        balise_fermante(__FUNCTION__);
        return $$;
    }else if(consume(DIVISE)){
        $1 = negation();
        herite_fils = cree_n_exp_op(DIVISE, herite, $1);
        $$ = termeBis(herite_fils);
        balise_fermante(__FUNCTION__);
        return $$;
    }else if(est_suivant(uniteCourante,_termeBis_)){
        balise_fermante(__FUNCTION__);
        return herite;
    }
    else{
        ERREUR();
    }
}

n_exp *facteur(){
	n_exp *$$ = NULL;

    balise_ouvrante(__FUNCTION__);
    if(consume(PARENTHESE_OUVRANTE)){
        $$ = expression();
        if(!consume(PARENTHESE_FERMANTE)){
            ERREUR();
        }
        balise_fermante(__FUNCTION__);
        return $$;
    }else if(consume(NOMBRE)){
    	char *nombre = malloc(sizeof(char *));
        strcpy(nombre, yytext);
        $$ = cree_n_exp_entier(atoi(nombre));
        balise_fermante(__FUNCTION__);
        return $$;
    }
    else if(est_premier(uniteCourante,_appelFct_)){
        n_appel *$1 = appelFct();
        $$ = cree_n_instr_appel($1);
        balise_fermante(__FUNCTION__);
        return $$;
    }else if(est_premier(uniteCourante,_var_)){
        $$ = var();
        balise_fermante(__FUNCTION__);
        return $$;
    }else if(consume(LIRE)){
        if(consume(PARENTHESE_OUVRANTE)){
        	$$ = cree_n_exp_lire();
            if(!consume(PARENTHESE_FERMANTE)){
                ERREUR();
            }
        }else{
            ERREUR();
        }
        balise_fermante(__FUNCTION__);
        return $$;
    }else{
        ERREUR();
    }
}

n_exp *var(){
	n_exp *$$ = NULL;
	n_var *$1 = NULL;

    balise_ouvrante(__FUNCTION__);
    if(consume(ID_VAR)){
        $1 = optIndice();
        $$ = cree_n_exp_var($1);
        balise_fermante(__FUNCTION__);
        return $$;
    }else{
        ERREUR();
    }
}

n_var *optIndice(){
	n_var *$$ = NULL;
	n_exp *$1 = NULL;

    balise_ouvrante(__FUNCTION__);
    if(consume(CROCHET_OUVRANT)){
    	char *nom = malloc(sizeof(char *));
    	strcpy(nom, yytext);
    	printf("Variable : %s\n", yytext);
        $1 = expression();
        if(!consume(CROCHET_FERMANT)){
            ERREUR();
        }
        $$ = cree_n_var_indicee(nom, $1);
        balise_fermante(__FUNCTION__);
        return $$;
    }else if(est_suivant(uniteCourante,_optIndice_)){
    	char *nom = malloc(sizeof(char *));
    	strcpy(nom, yytext);
    	printf("Variable : %s\n", yytext);
    	$$ = cree_n_var_simple(nom);
        balise_fermante(__FUNCTION__);
        return $$;
    }
    else{
        ERREUR();
    }
}

n_appel *appelFct(){
	n_appel *$$ = NULL;
	n_l_exp *$1 = NULL;
    balise_ouvrante(__FUNCTION__);
    if(consume(ID_FCT)){
    	char *fonction = malloc(sizeof(char *));
    	strcpy(fonction, yytext);
        if(consume(PARENTHESE_OUVRANTE)){
            $1 = listeExpressions();
            if(!consume(PARENTHESE_FERMANTE)){
                ERREUR();
            }
        }else{
            ERREUR();
        }
        $$ = cree_n_appel(fonction, $1);
        balise_fermante(__FUNCTION__);
        return $$;
    }else{
        ERREUR();
    }
}

n_l_exp *listeExpressions(){
	n_l_exp *$$ = NULL;
	n_exp *$1 = NULL;
	n_l_exp *$2 = NULL;

    balise_ouvrante(__FUNCTION__);
    if(est_premier(uniteCourante,_expression_)){
        $1 = expression();
        $2 = listeExpressionsBis();
        $$ = cree_n_l_exp($1, $2);
        balise_fermante(__FUNCTION__);
        return $$;
    }else if(est_suivant(uniteCourante,_listeExpressions_)){
        balise_fermante(__FUNCTION__);
        return $$;
    }
    else{
        ERREUR();
    }
}

n_l_exp *listeExpressionsBis(){
	n_l_exp *$$ = NULL;
	n_exp *$1 = NULL;
	n_l_exp *$2 = NULL;
    balise_ouvrante(__FUNCTION__);
    if(consume(VIRGULE)){
        $1 = expression();
        $2 = listeExpressionsBis();
        $$ = cree_n_l_exp($1, $2);
        balise_fermante(__FUNCTION__);
        return $$;
    }else if(est_suivant(uniteCourante,_listeExpressionsBis_)){
        balise_fermante(__FUNCTION__);
        return NULL;
    }
    else{
        ERREUR();
    }
}
