BUILD_DIR := build
BIN := $(BUILD_DIR)/minic

.PHONY: all clean test

all: $(BIN)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN): $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake .. && cmake --build .

test: $(BIN)
	bash tests/run_tests.sh

clean:
	rm -rf $(BUILD_DIR)
