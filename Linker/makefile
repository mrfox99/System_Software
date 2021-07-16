BIN = linker
BUILD_DIR = ./build
SOURCE_DIR = ./src

CPP = $(wildcard $(SOURCE_DIR)/*.cpp)
OBJ = $(CPP:$(SOURCE_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEP = $(OBJ:%.o=%.d)

$(BIN) : $(OBJ)
	$(CXX) $(CXX_FLAGS) $^ -o $@

-include $(DEP)

$(BUILD_DIR)/%.o : $(SOURCE_DIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) -MMD -c $< -o $@

.PHONY : clean
clean :
	-rm -r $(BUILD_DIR)