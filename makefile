CXX = gcc
# TARGET = dict1
# SRC = $(wildcard *.c)
# OBJ = $(patsubst %.c, %.o, $(SRC))

CXXFLAGS = -c -Wall

OBJ = main2.o MyDualCircularLinkedListsWithSentinels.o
dict2: $(OBJ)
	$(CXX) -o $@ $^
	
OBJ = main1.o MyDualCircularLinkedListsWithSentinels.o
dict1: $(OBJ)
	$(CXX) -o $@ $^
	
OBJ = main3.o MyDualCircularLinkedListsWithSentinels.o
dict3: $(OBJ)
	$(CXX) -o $@ $^
		
%.o: %.c
	$(CXX) $(CXXFLAGS) $< -o $@
	
.PHONY: clean
clean:
	rm -f *.o $(TARGET)
	

