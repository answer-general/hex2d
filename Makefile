CXX=g++
CXXFLAGS+=-Wall -pedantic -Wno-long-long -O0 -std=c++11 -g
LDFLAGS=-O0 -std=c++11 -lncurses -lmenu -lpanel -g

TARGET=./titovden
SRCDIR=./src

EXEC=hexed
SOURCES=$(addprefix src/, \
  ObjectContainer.cpp \
  Level.cpp \
  FileHelper.cpp \
  Config.cpp \
  screens/MainMenu.cpp \
  screens/LevelSelect.cpp \
  screens/GameScreen.cpp \
  UI.cpp \
  KeyboardInput.cpp \
  ActorMage.cpp \
  Game.cpp \
  main.cpp \
)
OBJECTS=$(SOURCES:.cpp=.o)

all: compile

compile: $(TARGET)/$(EXEC)

$(TARGET)/$(EXEC): $(OBJECTS)
	mkdir -p $(TARGET)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $(TARGET)/$(EXEC)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY clean:
	rm -rf $(TARGET)
	rm -f $(SRCDIR)/*.o
	rm -f $(SRCDIR)/screens/*.o
