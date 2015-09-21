CC=gcc
CFLAGS=-c -Wall -ansi -pedantic -g -I/opt/local/include
LDFLAGS= -g -L/opt/local/lib
SOURCES=main.c HuffmanCoding.c Codefy.c DiferenceCoding.c PriorityList.c DCT.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=huff

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ -L/opt/local/lib -lm

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ 

clean:
	rm $(OBJECTS)
