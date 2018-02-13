#include "analyseur_syntaxique.h"

int consume(int x){
    char valeur[20];
    char valeur2[20];
    char nom[20];
    char nom2[20];
    nom_token(x,nom,valeur);

    if(uniteCourante == x){
        //affiche_element(nom,valeur,trace_xml);
        uniteCourante = yylex();
        return 1;
    }else{
        nom_token(uniteCourante,nom2,valeur2);
        fprintf(stderr,"%s expected (of type %s) %s found (of type %s)\n", valeur, nom, valeur2, nom2);
    }   

    return 0;
}

//Procedures

void optDecVariables(){
    if(est_premier(uniteCourante,_listeDecVariables_)){
        listeDecVariables();
        if(!consume(POINT_VIRGULE)){
            erreur("optDecVariables ;");
        }
    }else if(est_suivant(uniteCourante,_optDecVariables_)){}
    else{
        erreur("optDecVariables");
    }
}

void listeDecFonctions(){
    if(est_premier(uniteCourante,_declarationFonction_)){
        declarationFonction();
        listeDecFonctions();
    }else if(est_suivant(uniteCourante,_listeDecFonctions_)){}
    else{
        erreur("listeDecFonctions");
    }
}

void declarationFonction(){
    if(consume(ID_FCT)){
        listeParam();
        optDecVariables();
        instructionBloc();
    }else{
        erreur("declarationFonction");
    }
}

void listeParam(){
    if(consume(PARENTHESE_OUVRANTE)){
        optListeDecVariables();
        if(!consume(PARENTHESE_FERMANTE)){
            erreur("listeParam");
        }
    }else{
        erreur("listeParam");
    }
}

void optListeDecVariables(){
    if(est_premier(uniteCourante,_listeDecVariables_)){
        listeDecVariables();
    }else if(est_suivant(uniteCourante,_optListeDecVariables_)){

    }else{
        erreur("optListeDecVariables");
    }
}

void instruction(){
    if(est_premier(uniteCourante,_instructionAffect_)){
        instructionAffect();
    }else if(est_premier(uniteCourante,_instructionBloc_)){
        instructionBloc();
    }else if(est_premier(uniteCourante,_instructionSi_)){
        instructionSi();
    }else if(est_premier(uniteCourante,_instructionTantque_)){
        instructionTantque();
    }else if(est_premier(uniteCourante,_instructionAppel_)){
        instructionAppel();
    }else if(est_premier(uniteCourante,_instructionRetour_)){
        instructionRetour();
    }else if(est_premier(uniteCourante,_instructionEcriture_)){
        instructionEcriture();
    }else if(est_premier(uniteCourante,_instructionVide_)){
        instructionVide();
    }else{
        erreur("instruction");
    }
}

void instructionAffect(){
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
    }else{
        erreur("instructionAffect");
    }
}

void instructionBloc(){
    if(consume(ACCOLADE_OUVRANTE)){
        listeInstructions();
        if(!consume(ACCOLADE_FERMANTE)){
            erreur("instructionBloc");
        }
    }else{
        erreur("instructionBloc");
    }
}

void listeInstructions(){
    if(est_premier(uniteCourante,_instruction_)){
        instruction();
        listeInstructions();
    }else if(est_suivant(uniteCourante,_listeInstructions_)){}
    else{
        erreur("listeInstructions");
    }
}

void instructionSi(){
    if(consume(SI)){
        expression();
        if(consume(ALORS)){
            instructionBloc();
            optSinon();
        }else{
            erreur("instructionSi");
        }
    }else{
        erreur("instructionSi");
    }
}

void optSinon(){
    if(consume(SINON)){
        instructionBloc();
    }else if(est_suivant(uniteCourante,_optSinon_)){}
    else{
        erreur("optSinon");
    }
}

void instructionTantque(){
    if(consume(TANTQUE)){
        expression();
        if(consume(FAIRE)){
            instructionBloc();
        }else{
            erreur("instructionTantque");
        }
    }else{
        erreur("instructionTantque");
    }
}

void instructionAppel(){
    if(est_premier(uniteCourante,_appelFct_)){
        appelFct();
        if(!consume(POINT_VIRGULE)){
            erreur("instructionAppel");
        }
    }else{
        erreur("instructionAppel");
    }
}

void instructionRetour(){
    if(consume(RETOUR)){
        expression();
        if(!consume(POINT_VIRGULE)){
            erreur("instructionRetour");
        }
    }else{
        erreur("instructionRetour");
    }
}

void instructionEcriture(){
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
    }else{
        erreur("instructionEcriture");
    }
}

void instructionVide(){
    if(!consume(POINT_VIRGULE)){
        ERREUR();
    }
}

void expression(){
    if(est_premier(uniteCourante,_conjonction_)){
        conjonction();
        expressionBis();
    }else{
        ERREUR();
    }
}

void expressionBis(){
    if(consume(OU)){
        conjonction();
        expressionBis();
    }else if(est_suivant(uniteCourante,_expressionBis_)){}
    else{
        ERREUR();
    }
}

void conjonction(){
    if(est_premier(uniteCourante,_negation_)){
        negation();
        conjonctionBis();
    }else{
        ERREUR();
    }
}

void conjonctionBis(){
    if(consume(ET)){
        negation();
        conjonctionBis();
    }else if(est_suivant(uniteCourante,_conjonctionBis_)){}
    else{
        ERREUR();
    }
}

void negation(){
    if(consume(NON)){
        comparaison();
    }else if(est_premier(uniteCourante,_comparaison_)){
        comparaison();
    }else{
        ERREUR();
    }
}

void comparaison(){
    if(est_premier(uniteCourante,_expArith_)){
        expArith();
        comparaisonBis();
    }else{
        ERREUR();
    }
}

void comparaisonBis(){
    if(consume(EGAL)){
        expArith();
        comparaisonBis();
    }else if(consume(INFERIEUR)){
        expArith();
        comparaisonBis();
    }else if(est_suivant(uniteCourante,_comparaisonBis_)){}
    else{
        ERREUR();
    }
}

void expArith(){
    if(est_premier(uniteCourante,_terme_)){
        terme();
        expArithBis();
    }else{
        ERREUR();
    }
}

void expArithBis(){
    if(consume(PLUS)){
        terme();
        expArithBis();
    }else if(consume(MOINS)){
        terme();
        expArithBis();
    }else if(est_suivant(uniteCourante,_expArithBis_)){}
    else{
        ERREUR();
    }
}

void terme(){
    if(est_premier(uniteCourante,_facteur_)){
        facteur();
        termeBis();
    }else{
        ERREUR();
    }
}

void termeBis(){
    if(consume(FOIS)){
        facteur();
        termeBis();
    }else if(consume(DIVISE)){
        facteur();
        termeBis();
    }else if(est_suivant(uniteCourante,_termeBis_)){}
    else{
        ERREUR();
    }
}

void facteur(){
    if(consume(PARENTHESE_OUVRANTE)){
        expression();
        if(!consume(PARENTHESE_FERMANTE)){
            ERREUR();
        }
    }else if(consume(NOMBRE)){}
    else if(est_premier(uniteCourante,_appelFct_)){
        appelFct();
    }else if(est_premier(uniteCourante,_var_)){
        var();
    }else if(consume(LIRE)){
        if(consume(PARENTHESE_OUVRANTE)){
            if(!consume(PARENTHESE_FERMANTE)){
                ERREUR();
            }
        }else{
            ERREUR();
        }
    }else{
        ERREUR();
    }
}

void var(){
    if(consume(ID_VAR)){
        optIndice();
    }else{
        ERREUR();
    }
}

void optIndice(){
    if(consume(CROCHET_OUVRANT)){
        expression();
        if(!consume(CROCHET_FERMANT)){
            ERREUR();
        }
    }else if(est_suivant(uniteCourante,_optIndice_)){}
    else{
        ERREUR();
    }
}

void appelFct(){
    if(consume(ID_FCT)){
        if(consume(PARENTHESE_OUVRANTE)){
            listeExpressions();
            if(!consume(PARENTHESE_FERMANTE)){
                ERREUR();
            }
        }else{
            ERREUR();
        }
    }else{
        ERREUR();
    }
}

void listeExpressions(){
    if(est_premier(uniteCourante,_expression_)){
        expression();
        listeExpressionsBis();
    }else if(est_suivant(uniteCourante,_listeExpressions_)){}
    else{
        ERREUR();
    }
}

void listeExpressionsBis(){
    if(consume(VIRGULE)){
        expression();
        listeExpressionsBis();
    }else if(est_suivant(uniteCourante,_listeExpressionsBis_)){}
    else{
        ERREUR();
    }
}

void listeDecVariables(){
    if(est_premier(uniteCourante,_declarationVariable_)){
        declarationVariable();
        listeDecVariablesBis();
    }else{
        erreur("listeDecVariables");
    }
}

void listeDecVariablesBis(){
    if(consume(VIRGULE)){
        declarationVariable();
        listeDecVariablesBis();
    }else if(est_suivant(uniteCourante,_listeDecVariablesBis_)){}
    else{
        erreur("listeDecVariablesBis");
    }
}

void declarationVariable(){
    if(consume(ENTIER)){
        if(consume(ID_VAR)){
            optTailleTableau();
        }else{
            erreur("declarationVariable");
        }
    }else{
        erreur("declarationVariable");
    }
}

void optTailleTableau(){
    if(consume(CROCHET_OUVRANT)){
        if(consume(NOMBRE)){
            if(!consume(CROCHET_FERMANT)){
                erreur("optTailleTableau");
            }
        }else{
            erreur("optTailleTableau");
        }

    }else if(est_suivant(uniteCourante,_optTailleTableau_)){}
    else{
        erreur("optTailleTableau");
    }
}

void programme(){
    if(est_premier(uniteCourante,_optDecVariables_)){
        optDecVariables();
        listeDecFonctions();
    }else{
        printf("programme");
        exit(-1);
    }
}