SOURCES = src/main.cpp src/graphics.cpp src/map.cpp
EXECUTABLE = game

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	g++ -o $(EXECUTABLE) $(SOURCES) -lncurses

clean:
	rm -f $(EXECUTABLE)