#Trinity Caitlin Atayan Belen
#t_belen@u.pacific.edu
#ECPE 170

# The variable CC specifies which compiler will be used.
# (because different unix systems may use different compilers)
CC=gcc


# The variable CFLAGS specifies compiler options
#   -c :    Only compile (don't link)
#   -Wall:  Enable all warnings about lazy / dangerous C programming 
CFLAGS=-c -Wall -std=c99 -Wextra


# All of the .h header files to use as dependencies
HEADERS=arrayFunc.h clue.h size.h sizer.h play.h readFile.h

# All of the object files to produce as intermediary work
OBJECTS=main.o arrayFunc.o sizer.o play.o readFile.o


# The final program to build
EXECUTABLE=crossword


# --------------------------------------------


all: $(EXECUTABLE)


$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)


%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $<


clean:
	rm -rf *.o $(EXECUTABLE)

