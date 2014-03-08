INCLUDE_DIR=./includes/
COMMON=../Common/
CPP=g++ -Wall
C11=g++ -std=c++11 -Wall
# gcc workaround
ENABLE_THREAD=-pthread -Wl,--no-as-needed

FLOAT_EQ=../Common/FloatEquality.cpp
bin/FloatEquality.o: $(FLOAT_EQ) 
	g++ -c $(FLOAT_EQ) -o $@ 

RBT=./src/RBT.cpp
rbt: $(RBT)
	$(CPP) $(RBT) -I$(INCLUDE_DIR) -o bin/rbt_test

AVL=./src/AVLTree.cpp
avl: $(AVL)
	$(CPP) $(AVL) -I$(INCLUDE_DIR) -o bin/avl

VECTORN=./src/VectorN.cpp ./bin/FloatEquality.o
vecn: $(VECTORN)
	$(CPP) $(VECTORN) -I$(INCLUDE_DIR) -I$(COMMON) -o bin/vecn

LCKDQ=./src/LockedQueue.cpp
lckdq: $(LCKDQ)
	$(C11) $(ENABLE_THREAD) $(LCKDQ) -I$(INCLUDE_DIR) -o bin/lckdq

LCKFQ=./src/LockFreeQueue.cpp
lckfq: $(LCKFQ)
	$(C11) $(ENABLE_THREAD) $(LCKFQ) -I$(INCLUDE_DIR) -o bin/lckfq
