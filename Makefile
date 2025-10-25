# ===============================================
# Android Performance Profiler - Makefile
# Target: Android ARM64 (aarch64)
# ===============================================

# --- Configurable Variables ---
NDK_PATH ?= $(HOME)/android-ndk-r27d
CC       := $(NDK_PATH)/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android30-clang

SRC_DIR  := src
INC_DIR  := $(SRC_DIR)/include
BUILD_DIR := build

TARGET   := profiler
SRC      := $(wildcard $(SRC_DIR)/*.c)
CFLAGS   := -Wall -O2 -Iinclude

# --- Build Target ---
all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(SRC)
	@mkdir -p $(BUILD_DIR)
	@echo "🔧 Building Android ARM64 binary..."
	$(CC) $(CFLAGS) $(SRC) -o $(BUILD_DIR)/$(TARGET)
	@echo " Build complete: $(BUILD_DIR)/$(TARGET)"

# --- Clean Target ---
clean:
	rm -rf $(BUILD_DIR)
	@echo " Cleaned build directory."

.PHONY: all clean
