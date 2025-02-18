#Jiwon KIM et Nguyen Hanh Dung 

#CFLAGS = -g -Wall -Wextra -pedantic -Wno-unused-parameter
CFLAGS = -g -Wno-unused-parameter
CC = gcc

PROGRAMS =   tests_ecosys tests_ecosys2 ecosys

.PHONY:	all clean

all: $(PROGRAMS)

tests_ecosys: ecosys.o main_tests.o
	$(CC) -o $@ $(CFLAGS) $^

# Ajoute la règle pour créer le programme tests_ecosys2
tests_ecosys2: ecosys.o main_tests2.o
	$(CC) -o $@ $(CFLAGS) $^


ecosys: ecosys.o main_ecosys.o
	$(CC) -o $@ $(CFLAGS) $^

ecosys.o: ecosys.c
	gcc $(CFLAGS) -c ecosys.c

main_tests.o: main_tests.c
	gcc $(CFLAGS) -c main_tests.c

# Ajoute la règle pour main_tests2.o
main_tests2.o: main_tests2.c 
	$(CC) $(CFLAGS) -c main_tests2.c

main_ecosys.o: main_ecosys.c 
	gcc $(CFLAGS) -c main_ecosys.c

#Ou plus simplement
#%.o:%.c %.h
#	$(CC)  $(GCC_FLAGS) -c  $<


clean:
	rm -f *.o *~ $(PROGRAMS)
