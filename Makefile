CC = gcc
CCFLAGS = -Wall -ggdb -std=gnu99
LIBS = -lm

FLEX = flex

LexDir = Analyseur_Lexical
SynDir = Analyseur_Syntaxique
SemDir = Analyseur_Semantique
UtiDir = util

OBJ = $(LexDir)/analyseur_lexical_flex.o\
      $(SynDir)/analyseur_syntaxique.o\
      $(SemDir)/analyseur_semantique.o\
      $(UtiDir)/util.o\
      $(UtiDir)/syntabs.o\
      $(UtiDir)/premiers.o\
      $(UtiDir)/suivants.o\
      $(UtiDir)/affiche_arbre_abstrait.o\
      $(UtiDir)/tabsymboles.o\

all: compilateur

compilateur: compilateur.c $(OBJ)
	$(CC) $(CCFLAGS) -o $@ $^ $(LIBS)

$(LexDir)/analyseur_lexical_flex.c: $(LexDir)/analyseur_lexical.flex
	$(FLEX) -o $@ $^

$(LexDir)/analyseur_lexical_flex.o: $(LexDir)/analyseur_lexical_flex.c
	$(CC) $(CCFLAGS) -c $^ -o $@
    
$(SynDir)/analyseur_syntaxique.o: $(SynDir)/analyseur_syntaxique.c
	$(CC) $(CCFLAGS) -c $^ -o $@

$(SemDir)/analyseur_semantique.o: $(SemDir)/analyseur_semantique.c
	$(CC) $(CCFLAGS) -c $^ -o $@

$(UtiDir)/%.o: $(UtiDir)/%.c
	$(CC) $(CCFLAGS) -c $^ -o $@

.PHONY : clean

clean:
	rm -f $(OBJ)
	rm -f compilateur
	rm -f $(LexDir)/analyseur_lexical_flex.c
