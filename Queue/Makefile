CFLAGS := -std=c++11 -c -Wall
#-std=c++11: use the ISO C++11 standard
#-c run partial compile (generate just the next step in the process
#-Wall show all warnings

SRC    := $(wildcard src/*.cc) #search for .cc files in src folder
OBJ    := $(SRC:.cc=.o)
EXEC   := Queue

all: $(SRC) debug

debug: $(OBJ) #generate unoptimized code for easy debugging
	g++ $(wildcard debug/src/*.o) -o debug/$(EXEC)

release: $(OBJ) #generate optimized code and do not leave object files
	g++ -O2 $(wildcard debug/src/*.o) -o $(EXEC)
           #-O2 optimizes the code
	rm -rf debug #clean up

release:

.cc.o: #generate object files
	mkdir -p debug/src           #make the directory if necessary
	g++ $(CFLAGS) $< -o debug/$@ #compile the object files

.PHONY: clean #ignore any files that are called clean
clean:
	rm -rf debug $(EXEC) #delete the debug folder    
                             #and the binary release
