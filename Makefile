SRC_DIR = .
BIN_DIR = ./bin
INCLUDE = ./include
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
BINS = $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%, $(SRCS))
HEADERS = $(wildcard $(INCLUDE)/*.h $(INCLUDE)/*.hpp)

.PHONY: all clean
all: $(BINS)

CC = g++
CXXFLAGS = -fdiagnostics-color=always -std=c++17 -g3 -ggdb -Wall -Wextra

$(BIN_DIR):
	mkdir -p $@

$(BIN_DIR)/%: $(SRC_DIR)/%.cpp $(HEADERS) | $(BIN_DIR)
	$(CC) $(CXXFLAGS) $< -I $(INCLUDE) -o $@

clean:
	rm -rf $(BIN_DIR)/*