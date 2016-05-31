CC = gcc
OBJS1 = Lecture_Ecriture_B.o huffman_part2.o arbre.o huffman_liste.o package_merge.o anlyseTexte.o compresser.o RLE.o MTF.o pretraitement.o 
OBJS2 = Lecture_Ecriture_B.o huffman_part2.o arbre.o huffman_liste.o package_merge.o anlyseTexte.o decompresser.o  RLE.o MTF.o pretraitement.o
EXEC1 = ../bin/compresser
EXEC2 = ../bin/decompresser
CFLAGS = -Wall -I ../include
SRCS1 = $(OBJS1:.c=.o)
SRCS2 = $(OBJS2:.c=.o)

all : $(EXEC1) $(EXEC2)

$(EXEC1): $(OBJS1)
	$(CC) $(OBJS1) -o $(EXEC1) -lm

$(EXEC2): $(OBJS2)
	$(CC) $(OBJS2) -o $(EXEC2) -lm
	
clean:
	-rm -rf ./*.o
