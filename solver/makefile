# module name
NAME = SS

# switches
SW = -g3 -Wall
#SW = -O3 -Wall

# libreries
LIB = -lm  /opt/ibm/ILOG/CPLEX_Studio_Community1262/cplex/lib/x86-64_linux/static_pic/libcplex.a -lpthread #-lefence


# compiler
CC = g++

# default target- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

default: $(NAME)

# clean - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

clean::
	rm -f *.o *~ #$(NAME)

CPLEX = -I/opt/ibm/ILOG/CPLEX_Studio_Community1262/cplex/include/ilcplex

# basic files used in the project
BASIC = StdAfx.h mymemory.h

# main module (linking phase) - - - - - - - - - - - - - - - - - - - - - - - -

OBJ =   SSCplex.o Main.o

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LIB) $(SW)

# dependencies: every .o from its .cpp + every recursively included .h- - - - -

SSCplex.o: SSCplex.cpp SSCplex.h $(BASIC)
	$(CC) -c $*.cpp -o $@ $(SW) $(CPLEX)

Main.o: Main.cpp  SSCplex.h $(BASIC)
	$(CC) -c $*.cpp -o $@ $(SW) $(CPLEX)

############################ End of makefile #################################
