CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = file_explorer
SRCS = src/main.cpp src/explorer.cpp src/fileops.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
