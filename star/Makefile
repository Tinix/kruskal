CC       = gcc
TARGET   = kruskal
CFLAGS   = -Wall -Werror -Wextra -pedantic -std=c99 -g
VALGRIND = valgrind --leak-check=full --show-reachable=yes
HEADERS  = $(wildcard *.h)
SOURCES  = $(wildcard *.c)
OBJECTS  = $(SOURCES:.c=.o)
FILE     = test0.dot
IN       = ../input/$(FILE)
OUT      = ../output/$(FILE)

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

-include .depend

.depend : $(SOURCES) $(HEADERS)
	$(CC) -MM $(SOURCES) > .depend

clean :
	rm -f $(TARGET) $(OBJECTS) .depend
	rm -rf _original _indent

indent : clean
	mkdir _original _indent
	cp $(HEADERS) $(SOURCES) _original
	cp $(HEADERS) $(SOURCES) _indent
	indent -kr -nut -brf -cli4 -l79 _indent/*
	meld _original _indent &

open :
	gedit Makefile pqueue.* union_find.* main.c $(IN) $(OUT) &

run : $(TARGET)
	./$(TARGET) < $(IN) > $(OUT)
	neato -Tpng -o $(OUT).png $(OUT)
	xdg-open $(OUT).png
	gedit $(OUT)

valgrind : $(TARGET)
	$(VALGRIND) ./$(TARGET) < $(IN) > $(OUT)
	neato -Tpng -o $(OUT).png $(OUT)
	xdg-open $(OUT).png
	gedit $(OUT)

.PHONY : clean open run valgrind
