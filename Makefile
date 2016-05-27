CC=g++
C++FLAGS=-Wall -std=c++11 -pedantic

AVL_OBJ=queryTrees.o
TEST_AVL_PROG=queryTrees

BST_OBJ=testTrees.o
TEST_BST_PROG=testTrees

%.o : %.cpp
	$(CC)  -c $< -o $@ $(C++FLAGS)

all:
	make $(TEST_AVL_PROG)
	make $(TEST_BST_PROG)

$(TEST_AVL_PROG): $(AVL_OBJ)
	$(CC) $(C++FLAG) -o $@ $(AVL_OBJ)

$(TEST_BST_PROG): $(BST_OBJ)
	$(CC) $(C++FLAG) -o $@ $(BST_OBJ)


clean:
	(rm -f *.o;)
	rm -f $(TEST_AVL_PROG)
	rm -f $(TEST_BST_PROG)
