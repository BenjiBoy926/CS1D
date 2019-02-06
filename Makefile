CC = g++
FLAGS = -std=c++14 -Wall -g
OBJS =
EXE = hw12

all: $(EXE)

$(EXE): $(EXE).cpp queue.h
	$(CC) $(FLAGS) $(EXE).cpp -o $(EXE)

clean:
	rm $(OBJS) $(EXE) $(EXE).scr

tar:
	tar cf $(EXE).tar $(EXE).scr Makefile *.cpp *.h

submission:
	script -c "make commands" $(EXE).scr; make tar; make clean

commands:
	date; ls -l; make all; ls -l; valgrind ./$(EXE); exit
	
