# Makefile for Aufgabenblock_3

CXX = g++
CXXFLAGS = -std=c++17 -I/workspaces/InfoPraktikum2/libs/boost/ -O0 -g3 -Wall -c -fmessage-length=0
LDFLAGS = -L/workspaces/InfoPraktikum2/libs/boost/libs -lpthread

SRCDIR = .
BUILDDIR = Debug
TARGET = $(BUILDDIR)/Aufgabenblock_3

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BUILDDIR)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -MF"$(@:.o=.d)" -MT"$@" -o $@ $<

clean:
	rm -rf $(BUILDDIR)/*.o $(BUILDDIR)/*.d $(TARGET)

-include $(OBJECTS:.o=.d)

.PHONY: all clean