#include "analyseur_syntaxique.h"

void E() {
    printf("<E>");
    T();
    EPrime();
    printf("</E>");
    
}

void EPrime() {
    printf("<EPrime>");
    if(uniteCourante == PLUS) {
        uniteCourante = yylex();
        E();
    }
    else {
        return;
    }
    printf("</EPrime>");
}

void T() {
    printf("<T>");
    F();
    TPrime();
    printf("</T>");
}

void TPrime() {
    printf("<TPrime>");
    if(uniteCourante == FOIS) {
        uniteCourante = yylex();
        T();
    }
    else {
        return;
    }
    printf("</TPrime>");
}

void F() {
    printf("<T>");
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
    printf("</T>");
}
