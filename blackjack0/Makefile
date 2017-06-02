CPP=g++
CPPFLAGS=-std=c++11

src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

LDFLAGS = -lncurses

all: blackjack

blackjack: $(obj)
	$(CPP) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) blackjack

run:
	./blackjack
