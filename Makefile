all: build

build:
	g++ src/*.cpp -o international_checkers -std=c++11

clean:
	rm -f international_checkers
