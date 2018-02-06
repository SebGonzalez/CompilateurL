#include "analyseur_syntaxique.h"

void consume(int x){
    char valeur[10];
    char valeur2[10];
    char nom[10];
    char nom2[10];
    nom_token(x,nom,valeur);

    if(uniteCourante == x){
        affiche_element(nom,valeur,trace_xml);
        uniteCourante = yylex();
    }else{
        nom_token(uniteCourante,nom2,valeur2);
        erreur()
    }
}

void E() {
    T();
    EPrime();
}

void EPrime() {
    if(uniteCourante == PLUS) {
        uniteCourante = yylex();
        E();
    }
    else {
        return;
    }
}

void T() {
    F();
    TPrime();
}

void TPrime() {
    if(uniteCourante == FOIS) {
        uniteCourante = yylex();
        T();
    }
    else {
        return;
    }
}

void F() {
    if(uniteCourante == PARENTHESE_OUVRANTE) {
        uniteCourante = yylex();
        E();
        if(uniteCourante == PARENTHESE_FERMANTE) {
            uniteCourante = yylex();
        }
        else {
        printf("Erreur de syntaxe\n");
        exit(-1);
            
    }

    }
    else if(uniteCourante == NOMBRE){
        uniteCourante = yylex();
    }
    else {
        printf("Erreur de syntaxe\n");
        exit(-1);
    }
}

void optDecVariables(){
    if(est_premier(uniteCourante,_listeDecVariables_)){
        listeDecVariables();
        if(uniteCourante == POINT_VIRGULE){
            uniteCourante == yylex();
        }else{
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
    if(uniteCourante == ID_FCT){
        uniteCourante == yylex();
        listeParam();
        optDecVariables();
        instructionBloc();
    }else{
        erreur("declarationFonction");
    }
}

void listeParam(){
    if(uniteCourante == PARENTHESE_OUVRANTE){
        uniteCourante = yylex();
        optListeDecVariables();
        if(uniteCourante == PARENTHESE_FERMANTE){
            uniteCourante = yylex();
        }else{
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
        if(uniteCourante == EGAL){
            uniteCourante = yylex();
            expression();
            if(uniteCourante == POINT_VIRGULE){
                uniteCourante == yylex();
            }else{
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
    consume(ACCOLADE_OUVRANTE);
    //TO DO
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
    if(uniteCourante == VIRGULE){
        uniteCourante == yylex();
        declarationVariable();
        listeDecVariablesBis();
    }else if(est_suivant(uniteCourante,_listeDecVariablesBis_)){}
    else{
        erreur("listeDecVariablesBis");
    }
}

void declarationVariable(){
    if(uniteCourante == ENTIER){
        uniteCourante == yylex();
        if(uniteCourante == ID_VAR){
            uniteCourante == yylex();
            optTailleTableau();
        }else{
            erreur("declarationVariable");
        }
    }else{
        erreur("declarationVariable");
    }
}

void optTailleTableau(){
    if(uniteCourante == CROCHET_OUVRANT){
        uniteCourante = yylex();
        if(uniteCourante == NOMBRE){
            uniteCourante = yylex();
            if(uniteCourante == CROCHET_FERMANT){
                uniteCourante = yylex();
            }else{
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