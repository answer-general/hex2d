CXX=g++
CXXFLAGS+=-Wall -pedantic -Wno-long-long -O0 -std=c++11 -g
LDFLAGS+=-O0 -std=c++11 `pkg-config --libs ncurses menu panel` -g

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
  screens/MapView.cpp \
  screens/GameScreen.cpp \
  UI.cpp \
  KeyboardInput.cpp \
  GameObject.cpp \
  ActorMage.cpp \
  ActorImp.cpp \
  Bomb.cpp \
  Bonus.cpp \
  Engine.cpp \
  Game.cpp \
  BSDSocket.cpp \
  main.cpp \
)

OBJECTS=$(SOURCES:.cpp=.o)

all: compile

compile: $(TARGET)/$(EXEC)

$(TARGET)/$(EXEC): $(OBJECTS)
	mkdir -p $(TARGET)
	$(CXX) $(OBJECTS) -o $(TARGET)/$(EXEC) $(LDFLAGS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY clean:
	rm -rf $(TARGET)
	rm -f $(SRCDIR)/*.o
	rm -f $(SRCDIR)/screens/*.o
