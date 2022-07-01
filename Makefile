TARGET    := test

CC        := g++
OBJ_DIR   := build
SRC_DIR   := src

SRC_FILES := $(shell find $(SRC_DIR) -type f -name "*.cpp") 
OBJ_FILES := $(patsubst $(SRC_DIR)%.cpp,$(OBJ_DIR)%.o,$(SRC_FILES))
DEP_FILES := $(patsubst $(SRC_DIR)%.cpp,$(OBJ_DIR)%.d,$(SRC_FILES))

OBJ_FILES += build/glad/glad.o

SRC_SUBDIRS := $(shell find $(SRC_DIR) -type d)
OBJ_SUBDIRS := $(patsubst $(SRC_DIR)%,$(OBJ_DIR)%,$(SRC_SUBDIRS)) build/glad/

CPPFLAGS += -Wall -Wextra -pedantic -std=c++20 -I glad/include -I src/ -Wno-unused -O2
LDFLAGS += -lglfw -lGL -lpng

.PHONY: all clean segf

all: $(TARGET)
segf: CPPFLAGS += -Og -g -fsanitize=address
segf: LDFLAGS += -Og -g -fsanitize=address
segf: $(TARGET)

$(TARGET): $(OBJ_SUBDIRS) $(OBJ_FILES)
	$(CC) -o $@ $(OBJ_FILES) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -MMD -MP $(CPPFLAGS) -c $< -o $@

build/glad/glad.o: glad/src/glad.cpp
	$(CC) -MMD -MP $(CPPFLAGS) -c $< -o $@

$(OBJ_SUBDIRS):
	mkdir -p $@

clean:
	rm -rf $(TARGET) $(OBJ_SUBDIRS) 

-include $(DEP_FILES)
