BIN = assembler
BUILD_DIR = ./build
SOURCE_DIR = ./src
INCLUDE_DIR = ./inc

CPP = $(wildcard $(SOURCE_DIR)/*.cpp)
OBJ = $(CPP:$(SOURCE_DIR)/%.cpp=$(BUILD_DIR)/%.o)
OBJ += $(BUILD_DIR)/Parser.o $(BUILD_DIR)/Lexer.o
DEP = $(OBJ:%.o=%.d)

$(BIN) : $(OBJ)
	$(CXX) $(CXX_FLAGS) $^ -o $@

$(BUILD_DIR)/Parser.cpp $(BUILD_DIR)/Parser.hpp: $(SOURCE_DIR)/Parser.y
	bison -d -o $(BUILD_DIR)/Parser.cpp $(SOURCE_DIR)/Parser.y
$(BUILD_DIR)/Lexer.cpp: $(SOURCE_DIR)/Lexer.l
	lex -o $(BUILD_DIR)/Lexer.cpp $(SOURCE_DIR)/Lexer.l
-include $(DEP)

$(BUILD_DIR)/%.o : $(BUILD_DIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) -MMD -c $< -o $@

$(BUILD_DIR)/%.o : $(SOURCE_DIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) -MMD -c $< -o $@

.PHONY : clean
clean :
	-rm -r $(BUILD_DIR)