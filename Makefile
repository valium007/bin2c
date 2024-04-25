# Compiler
CXX := g++

# Source file
SRC := bin2c.cpp

# Output file
TARGET := bin2c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) -o $(TARGET) $(SRC)