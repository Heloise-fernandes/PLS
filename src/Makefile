CC = gcc
OBJS = Lecture_Ecriture_B.o huffman_part2.o arbre.o huffman_liste.c package_merge.o
EXEC = ../bin/huffman_part2
CFLAGS = -Wall -I ../src
SRCS = $(OBJS:.c=.o)

all : $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) -lm

clean:
	-rm -rf ./*.o
