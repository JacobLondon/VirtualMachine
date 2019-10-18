OBJ_FILES=main.o instruction.o memory.o parser.o processor.o display.o
LIBS=-lncurses
TARGET=VirtualMachine

.PHONY: clean
CXXFLAGS=-std=c++17 -ggdb

$(TARGET) : $(OBJ_FILES)
	$(CXX) -o $(TARGET) $(OBJ_FILES) $(LIBS)

clean : 
	rm -rf *.o $(TARGET) $(LEX_FILES) $(YACC_FILES)
