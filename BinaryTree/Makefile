#This is a template makefile.
EXEC := BinaryTree

CCFLAGS := -std=c++11 -c -Wall -g #compiler flags for C++
#-std=c++11: use the ISO C++11 standard
#-c run partial compile (generate just the next step in the process
#-Wall show all warnings
#-g output debugging data
CFLAGS := -c -Wall #compiler flags for C

CCSRC := $(wildcard src/*.cc) #search for .cc files in src folder
CSRC := $(wildcard src/*.c)   #search for .c files
OBJ := $(CCSRC:.cc=.o) $(CSRC:.c=.o)

all: $(CCSRC) $(CSRC) debug

#generate unoptimized code for easy debugging
debug: $(OBJ)
	g++ $(wildcard debug/src/*.o) -o debug/$(EXEC)
#generate optimized code and do not leave object files
release: $(OBJ)
	g++ -O2 $(wildcard debug/src/*.o) -o $(EXEC)
        #-O2 optimizes the code
	rm -rf debug #clean up

#generate object files
.cc.o:
	mkdir -p debug/src  #make the directory if necessary
	g++ $(CCFLAGS) $< -o debug/$@  #compile the object files
.c.o:
	mkdir -p debug/src
	gcc $(CFLAGS) $< -o debug/$@

.PHONY: clean #ignore any files that are called clean
clean:
	rm -rf debug $(EXEC) #delete the debug folder    
                             #and the binary release
