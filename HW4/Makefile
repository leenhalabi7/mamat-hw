CC = gcc
CLINK = $(CC)
CFLAGS = -g -Wall -std=c99

libgrades.so: grades.o
	$(CLINK) -shared grades.o -o libgrades.so -llinked-list -L.

grades.o: grades.c grades.h linked-list.h
	$(CC) $(CFLAGS) -c -fpic grades.c

clean:
	rm -rf *.o libgrades.so
