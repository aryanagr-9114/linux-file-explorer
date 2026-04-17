CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2
SRCDIR = src
SRCS = $(SRCDIR)/main.cpp $(SRCDIR)/explorer.cpp $(SRCDIR)/fileops.cpp
TARGET = file-explorer

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)
