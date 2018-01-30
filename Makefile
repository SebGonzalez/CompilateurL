CC = gcc
CCFLAGS = -Wall -ggdb
LIBS = -lm

FLEX = flex

LexDir = Analyseur_Lexical
SynDir = Analyseur_Syntaxique
UtiDir = util

OBJ = $(LexDir)/analyseur_lexical_flex.o\
      $(SynDir)/analyseur_syntaxique.o\
      $(UtiDir)/util.o\

all: compilateur

compilateur: compilateur.c $(OBJ)
	$(CC) $(CCFLAGS) -o $@ $^ $(LIBS)

$(LexDir)/analyseur_lexical_flex.c: $(LexDir)/analyseur_lexical.flex
	$(FLEX) -o $@ $^

$(LexDir)/analyseur_lexical_flex.o: $(LexDir)/analyseur_lexical_flex.c
	$(CC) $(CCFLAGS) -c $^ -o $@
    
$(SynDir)/analyseur_syntaxique.o: $(SynDir)/analyseur_syntaxique.c
	$(CC) $(CCFLAGS) -c $^ -o $@

$(UtiDir)/util.o: $(UtiDir)/util.c
	$(CC) $(CCFLAGS) -c $^ -o $@

.PHONY : clean

clean:
	rm -f $(OBJ)
	rm -f compilateur
	rm -f $(LexDir)/analyseur_lexical_flex.c