MAKE = make
GCC = gcc
ECHO = echo
LIBFLAGS =
CFLAGS = -Wall
INCLUDE = include/
SRC = $(wildcard src/*.c)
MOVE = mv
EXC = ./bin/seekfox
LIB = lib/
READ = @read -p
BIN = bin/*
LOG = log/*

all :
	$(MAKE) compile -s
	$(MAKE) run -s
compile :
	@$(GCC) $(CFLAGS) -I $(INCLUDE) -c $(SRC) $(LIBFLAGS)
	@$(MOVE) *.o $(LIB)
	@$(GCC) $(CFLAGS) -o $(EXC) $(LIB)*.o $(LIBFLAGS)

run :
	@$(ECHO) '\n\n'------------------RUN------------------;
	@$(EXC)

clean :
	rm $(BIN) $(LIB)*
	$(MAKE) cleanlog

cleanlog :
	rm $(LOG)
