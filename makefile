CFLAGS = -g -O
LIBS = -lm

OBJ =\
	main.o\
    Query.o \
    Literal.o \
    Dictionary.o \
    Utils.o \
    InputParser.o \
    Dataset.o \
    Comparator.o \

all: main

clean:
       rm -f *.o querproc
.cpp.o:
       $(CXX) -c $(INCLUDES) $(CFLAGS) $<

main: $(OBJ)
       $(CXX) $(OBJ) $(LIBS) -o querproc