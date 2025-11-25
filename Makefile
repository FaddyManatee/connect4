# Compiler and flags.
CXX := g++
CXXFLAGS := -I src/include -MMD -MP
DBGFLAGS := -g -O0 -DDEBUG

# Directories.
SRC_DIR := src
BIN_DIR := bin

# Sources and objects.
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

# Output binary.
TARGET := $(BIN_DIR)/connect4
DEBUG_TARGET := $(BIN_DIR)/connect4-debug

.PHONY: all clean debug

all: $(TARGET)

debug: CXXFLAGS += $(DBGFLAGS)
debug: $(DEBUG_TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@

$(DEBUG_TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@

# Pattern rule for object files.
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN_DIR)

-include $(DEPS)
