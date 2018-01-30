CC = gcc
FLEX = flex

LIBS = -lm 
CCFLAGS = -Wall -ggdb

OBJ = ./Analyseur_Lexical/analyseur_lexical_flex.o ./Analyseur_Syntaxique/analyseur_syntaxique.o ./util/util.o

all: compilateur

compilateur: compilateur.c $(OBJ)
	$(CC) $(CCFLAGS) -o compilateur compilateur.c $(OBJ)

./Analyseur_Lexical/analyseur_lexical_flex.c: ./Analyseur_Lexical/analyseur_lexical.flex
	$(FLEX) -o $@ $^

./Analyseur_Lexical/analyseur_lexical_flex.o: ./Analyseur_Lexical/analyseur_lexical_flex.c
	$(CC) $(CCFLAGS) -c $^ -o $@
    
./Analyseur_Syntaxique/analyseur_syntaxique.o: ./Analyseur_Syntaxique/analyseur_syntaxique.c
	$(CC) $(CCFLAGS) -c $^ -o $@

./util/util.o: ./util/util.c
	$(CC) $(CCFLAGS) -c $^ -o $@

.PHONY : clean

clean:
	- rm -f $(OBJ)
	- rm -f compilateur
	- rm -f ./Analyseur_Lexical/analyseur_lexical_flex.c
