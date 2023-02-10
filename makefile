SOURCES = src/main.cpp src/graphics.cpp src/map.cpp src/storing.cpp src/entities.cpp src/game.cpp src/utils.cpp
EXECUTABLE = eternal_run

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	g++ -o $(EXECUTABLE) $(SOURCES) -lncurses

clean:
	rm -f $(EXECUTABLE)