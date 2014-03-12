INCLUDE_DIR=./includes/
COMMON=../Common/
CPP=g++ -Wall -I$(INCLUDE_DIR)
C11=g++ -std=c++11 -Wall -I$(INCLUDE_DIR)
# gcc workaround
ENABLE_THREAD=-pthread -Wl,--no-as-needed

bin/FloatEquality.o: ../Common/FloatEquality.cpp
	g++ -c $< -o $@ 

rbt: ./src/RBT.cpp
	$(CPP) $< -o bin/$@

avl: ./src/AVLTree.cpp
	$(CPP) $< -o bin/$@

vecn: ./src/VectorN.cpp ./bin/FloatEquality.o
	$(CPP) -I$(COMMON) $? -o bin/$@

lckdq: ./src/LockedQueue.cpp
	$(C11) $(ENABLE_THREAD) $< -o bin/$@

lckfq: ./src/LockFreeQueue.cpp
	$(C11) $(ENABLE_THREAD) $< -o bin/$@

heap: ./src/Heap.cpp
	$(C11) -DDEBUG $< -o bin/$@ 

clean:
	rm -rf bin/*
