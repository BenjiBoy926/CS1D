ID = CBH
CC = g++
FLAGS = -std=c++14 -Wall -g
EXE = hw2

# Objects 
OBJS = $(EXE).o char_string.o cstr.o

# Names of screen capture and tar archive are based on executable's name
SCR = $(EXE).scr
TAR = $(ID)$(EXE).tar

submission:
	script -c "date; ls-l; make all; ls -l; valgrind ./$(EXE); exit" $(SCR); make tar; make clean

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(FLAGS) -o $(EXE)

# Recipe for building all object files
%.o: %.cpp %.h
	$(CC) $(FLAGS) -c $< -o $@
	
clean:
	rm -f $(OBJS) $(EXE) $(SCR)

tar:
	tar cf $(TAR) *.cpp *.h $(SCR)