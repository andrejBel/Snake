OUTPUTS = snake
CC = g++

all: $(OUTPUTS)

clean:
	rm -f $(OUTPUTS)

snake: main.cpp Snake.cpp packet.h GameArea.cpp Game.cpp client.cpp CONSTANTS.h KeyboardInput.cpp
	$(CC) -o snake -O3 -std=c++14 -pthread main.cpp Snake.cpp packet.h GameArea.cpp Game.cpp client.cpp CONSTANTS.h KeyboardInput.cpp -lsfml-graphics -lsfml-window -lsfml-system
