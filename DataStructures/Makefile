INCLUDE_DIR=./includes/
COMMON=../Common/

FLOAT_EQ=../Common/FloatEquality.cpp
FloatEquality.o: $(FLOAT_EQ) 
	g++ -c $(FLOAT_EQ) -o bin/FloatEquality.o

RBT=./src/RBT.cpp
rbt: $(RBT)
	g++ -Wall $(RBT) -I$(INCLUDE_DIR) -o bin/rbt_test

AVL=./src/AVLTree.cpp
avl: $(AVL)
	g++ -Wall $(AVL) -I$(INCLUDE_DIR) -o bin/avl

VECTORN=./src/VectorN.cpp ./bin/FloatEquality.o
vecn: $(VECTORN)
	g++ -Wall $(VECTORN) -I$(INCLUDE_DIR) -I$(COMMON) -o bin/vecn
