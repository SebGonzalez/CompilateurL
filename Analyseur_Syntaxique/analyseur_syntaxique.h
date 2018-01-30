#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../util/symboles.h"
#include "../util/util.h"

int yylex(void);
extern char *yytext;
FILE *yyin;

void E();
void EPrime();
void T();
void TPrime();
void F();

int uniteCourante;
