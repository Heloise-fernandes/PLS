CC = gcc
OBJS0 = Lecture_Ecriture_B.o huffman_part2.o arbre.o huffman_liste.o package_merge.o anlyseTexte.o main.o
OBJS1 = Lecture_Ecriture_B.o huffman_part2.o arbre.o huffman_liste.o package_merge.o anlyseTexte.o compresser.o 
OBJS2 = Lecture_Ecriture_B.o huffman_part2.o arbre.o huffman_liste.o package_merge.o anlyseTexte.o decompresser.o
EXEC0 = ../bin/pls
EXEC1 = ../bin/compresser
EXEC2 = ../bin/decompresser
CFLAGS = -Wall -I ../include
SRCS0 = $(OBJS0:.c=.o)
SRCS1 = $(OBJS1:.c=.o)
SRCS2 = $(OBJS2:.c=.o)

all : $(EXEC0) $(EXEC1) $(EXEC2)

$(EXEC0): $(OBJS0)
	$(CC) $(OBJS0) -o $(EXEC0) -lm

$(EXEC1): $(OBJS1)
	$(CC) $(OBJS1) -o $(EXEC1) -lm

$(EXEC2): $(OBJS2)
	$(CC) $(OBJS2) -o $(EXEC2) -lm
	
clean:
	-rm -rf ./*.o
