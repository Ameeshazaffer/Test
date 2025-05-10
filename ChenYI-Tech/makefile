CC = gcc
CFLAGS = -Wall -g
OBJETS = main.o animal.o refuge.o
EXEC = chenil

all: $(EXEC)

$(EXEC): $(OBJETS)
	$(CC) $(OBJETS) -o $(EXEC)

main.o: main.c animal.h refuge.h
	$(CC) $(CFLAGS) -c main.c

animal.o: animal.c animal.h refuge.h
	$(CC) $(CFLAGS) -c animal.c

refuge.o: refuge.c animal.h refuge.h
	$(CC) $(CFLAGS) -c refuge.c

clean:
	rm -f $(OBJETS) $(EXEC)

fclean: clean

re: fclean all
