
CC = g++

LDFLAGS = -g
CCFLAGS = -g -c

SOURCES = $(wildcard ./source/*.cpp)
HEADERS = $(wildcard ./source/*.hpp)

OBJS = $(subst .cpp,.opp,$(subst source,obj,$(SOURCES)))

all: $(OBJS)
	$(CC) $(LDFLAGS) -o bin/eeg-c $^
	@rm -rf obj/*
	@echo ' '
	@./bin/eeg-c

./obj/%.opp: ./source/%.cpp ./source/%.hpp
	$(CC) $(CCFLAGS) $< -o $@

./obj/main.opp: ./source/main.cpp $(HEADERS)
	$(CC) $(CCFLAGS) $< -o $@