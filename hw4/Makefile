CC = g++
FLAGS = -std=c++14 -Wall -g
SOURCES = $(wildcard *.cpp)
OBJS = $(SOURCES:.cpp=.o)
EXE = exec

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(OBJS) -o $(EXE)

%.o: %.cpp %.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm $(OBJS) $(EXE) $(EXE).scr

tar:
	tar cf $(EXE).tar $(EXE).scr Makefile *.cpp *.h

submission:
	script -c "make commands" $(EXE).scr; make tar; make clean

commands:
	date; ls -l; make all; ls -l; valgrind ./$(EXE); exit
	
