MAKE = make
GCC = gcc
ECHO = echo
LIBFLAGS =-lcrypt -lm
CFLAGS = -Wall
INCLUDE = include/
SRC = $(wildcard src/*.c)
MOVE = mv
EXC = ./bin/seekfox.out
LIB = lib/
READ = @read -p
BIN = bin/*
LOG = log/*

.SILENT:clean
.SILENT:cleanlog

all :
	@$(MAKE) compile -s
	@dos2unix bin/readRequete.sh
	@$(MAKE) run -s

compile :
	@$(ECHO) 'Loading ...';
	@mkdir -p bin
	@mkdir -p lib
	@mkdir -p data
	@mkdir -p log
	@mkdir -p requete 
	@$(GCC) $(CFLAGS) -I $(INCLUDE) -c $(SRC) $(LIBFLAGS)
	@$(MOVE) *.o $(LIB)
	@$(GCC) $(CFLAGS) -o $(EXC) $(LIB)*.o $(LIBFLAGS)
run :
	@$(ECHO) '\n'------------------RUN------------------'';
	@$(EXC)
	@$(ECHO) '\n'------------------END------------------'\n';

admin :
	@$(ECHO) '\n'------------------RUN------------------'';
	@$(EXC) admin
	@$(ECHO) '\n'------------------END------------------'\n';

clean :
	@rm -f $(shell find ./bin -name *.out)
	@rm -f $(shell find ./lib -name *.o)
	@rm -f $(shell find ./log -name *.log)

cleanlog :
	@rm -f $(shell find ./log -name *.)

