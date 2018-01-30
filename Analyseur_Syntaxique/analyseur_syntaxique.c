#include "analyseur_syntaxique.h"

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
