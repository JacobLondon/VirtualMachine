OBJ_FILES=instruction.o memory.o parser.o processor.o tokens.o types.o
LEX_FILES=parser.cpp
YACC_FILES=tokens.cpp
TARGET=VirtualMachine

.PHONY: clean
CXXFLAGS=-std=c++17

$(TARGET) : $(OBJ_FILES)
	$(CXX) -o $(TARGET) $(OBJ_FILES)

%.cpp : %.lpp
	$(LEX) $(LEXFLAGS) -o $@ $< 

%.cpp : %.ypp
	$(YACC) $(YACCFLAGS) -o $@ $<

clean : 
	rm -rf *.o $(TARGET) $(LEX_FILES) $(YACC_FILES)
