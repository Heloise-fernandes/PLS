CC = gcc
OBJS = Lecture_Ecriture_B.o huffman_part2.o arbre.o huffman_liste.o package_merge.o anlyseTexte.o main.o
EXEC = ../bin/pls
CFLAGS = -Wall -I ../include
SRCS = $(OBJS:.c=.o)

all : $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) -lm

clean:
	-rm -rf ./*.o
