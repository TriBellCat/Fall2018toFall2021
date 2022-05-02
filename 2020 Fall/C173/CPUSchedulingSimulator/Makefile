# The variable CFLAGS specifies compiler options
#   -c :    Only compile (don't link)
#   -Wall:  Enable all warnings about lazy / dangerous C programming 
#   -std=c99: Using newer C99 version of C programming language
CFLAGS=-c -Wall -std=c99

# All of the .h header files to use as dependencies
HEADERS=main.h fcfs.h sjf.h rr.h

# All of the object files to produce as intermediary work
OBJECTS=main.o fcfs.o sjf.o rr.o

# The final program to build
EXECUTABLE=lab5

# --------------------------------------------

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf *.o $(EXECUTABLE)
