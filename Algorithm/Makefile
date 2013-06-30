INCLUDE_DIR=./includes/
all: *

HUFFMAN=./src/Huffman.cpp
huffman: $(HUFFMAN)
	g++ -Wall $(HUFFMAN) -I$(INCLUDE_DIR) -o bin/huffman

LISTINTERSECT=./src/ListIntersection.c
intersect: $(LISTINTERSECT)
	gcc -Wall $(LISTINTERSECT) -I$(INCLUDE_DIR) -o bin/list_intersect 

LCS=./src/LCS.cpp
diff: $(LCS)
	g++ -Wall $(LCS) -I$(INCLUDE_DIR) -o bin/diff
