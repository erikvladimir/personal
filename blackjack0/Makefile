CPP=g++
CPPFLAGS=-std=c++14

src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

LDFLAGS = -lncurses

all: clean build test run 

build: blackjack

blackjack: $(obj)
	$(CPP) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) blackjack

run:
	./blackjack

test:
	./blackjack test

