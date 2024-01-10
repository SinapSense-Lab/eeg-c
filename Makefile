
CC = g++

LDFLAGS = -g -std=c++17 -I/usr/local/include -I/opt/homebrew/include -L/opt/homebrew/lib -L/usr/local/lib/ -Wl,-rpath,/usr/local/lib -lfCWT -lfCWT.2.0 -v -fdeclspec -Wdeprecated-declarations
CCFLAGS = -g -std=c++17 -c -fdeclspec -Wdeprecated-declarations

SOURCES = $(wildcard ./source/*.cpp)
HEADERS = $(wildcard ./source/*.hpp)

OBJS = $(subst .cpp,.opp,$(subst source,obj,$(SOURCES)))
#OBJS_CORE = $(subst .cpp,.opp,$(subst source,obj,$(CORE)))

all: $(OBJS)
	$(CC) $(LDFLAGS) -o ./bin/eeg-c $^
	@rm -rf obj/*
	@echo ' '
	@./bin/eeg-c test/raw/ test/output/

./obj/%.opp: ./source/%.cpp ./source/%.hpp
	$(CC) $(CCFLAGS) $< -o $@

./obj/main.opp: ./source/main.cpp $(HEADERS)
	$(CC) $(CCFLAGS) $< -o $@