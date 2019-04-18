#########################################################
#                                                       #
#                 Makefile for linux gcc                #
#                                                       #
#########################################################

#########################################################
##
##               specify the include paths
##
#########################################################

INCLUDE_DIR= -I/usr/X11R6/include

#########################################################
##
##              specify the lib directories
##
#########################################################

LIB_DIR= -L/usr/X11R6/lib

#########################################################
##
##             specify the librarys to link
##
#########################################################

LIBS= -lGL -lGLU -lglut -lstdc++ -lm

#########################################################
##
## specify a line to compile the source files. The first
## version produces a release build. The second produces
## a debug build
##
#########################################################

COMPILE= g++ -O2 $(INCLUDE_DIR)

# COMPILE= gcc -g -I  $(INCLUDE_DIR)


#########################################################
##
##               specify the output file
##
#########################################################

OUTPUT=t1

#########################################################
##
##              specify the input objects
##
#########################################################

OBJECTS= node.o line.o main.o


#########################################################
##
##      Everything is dependant on the output file
##
#########################################################

all : compile run clean

run : compile
	./$(OUTPUT)

#########################################################
##
##  The output program is dependant on the input objects
##
#########################################################

compile : $(OBJECTS)
	$(COMPILE) $(OBJECTS) $(LIB_DIR) $(LIBS)   -o $(OUTPUT)


#########################################################
##
##     Compile each *.cpp file into a *.o file.
##
#########################################################

main.o : main.cpp
	$(COMPILE) -c main.cpp

line.o : line.cpp
	$(COMPILE) -c line.cpp

node.o : node.cpp
	$(COMPILE) -c node.cpp


#########################################################
#
#           A rule to delete all temp files
#
#########################################################

clean:
	rm $(OUTPUT) $(OBJECTS)

