# Compiler
ifeq ($(shell uname), Darwin)
	CXX = clang++
else
	CXX= g++
endif

# Compiler flags
CXXFLAGS = -Wall -g -std=c++17

# Directories
SRCDIR = src
HEADDIR = src/headers
BUILDDIR = build

# Target
TARGET = agency

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

# Object files
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SOURCES))

# Header files
HEADERS = $(wildcard $(HEADDIR)/*.h)

# Default target
all: $(TARGET)

# Compile source files into object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -I$(HEADDIR) -c $< -o $@

# Link
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Clean the trash
clean:
	$(RM) -r $(OBJECTS)

.PHONY: all clean
