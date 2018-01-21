OUTPUTS = server
CC = g++

all: $(OUTPUTS)

clean:
	rm -f $(OUTPUTS)

server: main.cpp ThreadPool.cpp Server.cpp packet.h Matrix.h Game.cpp Client.cpp constants.h
	$(CC) -o server -O3 -std=c++14 -pthread main.cpp ThreadPool.cpp Server.cpp packet.h Matrix.h Game.cpp Client.cpp constants.h
