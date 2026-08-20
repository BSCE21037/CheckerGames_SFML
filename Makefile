# Cross-platform Makefile for CheckerGames_SFML
#
#   macOS  : brew install sfml@2   then  make run
#   Linux  : sudo apt install libsfml-dev   then  make run
#   Windows: uses the bundled SFML-2.5.1 (MinGW) folder,  mingw32-make run

CXX      := g++
CXXFLAGS := -std=c++17 -O2
TARGET   := checkers

# main.cpp #includes the other .cpp files, so it is the only translation unit.
SRCS     := main.cpp

SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

UNAME_S := $(shell uname -s 2>/dev/null)

ifeq ($(OS),Windows_NT)
    # ---- Windows: bundled SFML ----
    TARGET  := checkers.exe
    INCLUDE := -ISFML-2.5.1/include
    LDFLAGS := -LSFML-2.5.1/lib
    RM      := del /Q
    CLEANME := $(TARGET) *.o
else ifeq ($(UNAME_S),Darwin)
    # ---- macOS: Homebrew SFML 2 (keg-only, so query its prefix) ----
    SFML_PREFIX := $(shell brew --prefix sfml@2 2>/dev/null || brew --prefix sfml 2>/dev/null)
    INCLUDE := -I$(SFML_PREFIX)/include
    LDFLAGS := -L$(SFML_PREFIX)/lib -Wl,-rpath,$(SFML_PREFIX)/lib
    RM      := rm -f
    CLEANME := $(TARGET) *.o
else
    # ---- Linux ----
    INCLUDE :=
    LDFLAGS :=
    RM      := rm -f
    CLEANME := $(TARGET) *.o
endif

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(SRCS) -o $(TARGET) $(LDFLAGS) $(SFML_LIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	$(RM) $(CLEANME)

.PHONY: all run clean
