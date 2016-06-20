CXX=g++
CXXFLAGS+=-Wall -pedantic -Wno-long-long -O0 -std=c++11 -ggdb
LDFLAGS+=-O0 -std=c++11 `pkg-config --libs ncurses menu panel` -ggdb

SRCDIR=./src

EXEC=titovden

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
  AIInput.cpp \
  GameObject.cpp \
  ActorMage.cpp \
  ActorImp.cpp \
  Bomb.cpp \
  Bonus.cpp \
  Engine.cpp \
  Game.cpp \
  main.cpp \
)

OBJECTS=$(SOURCES:.cpp=.o)

all: compile

compile: $(EXEC)

doc:
	mkdir -p ./doc
	cp $(SRCDIR)/doc/*.png ./doc/
	doxygen

install:
	mkdir -p $$HOME/.config/HexedMan
	cp -r $(SRCDIR)/assets/* $$HOME/.config/HexedMan/

run: compile
	./titovden

$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXEC) $(LDFLAGS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY clean:
	rm -f $(SRCDIR)/*.o
	rm -f $(SRCDIR)/screens/*.o
	rm -rf ./doc
	rm -rf $(EXEC)
