build:
	g++ -std=c++17 -I. -obin/wordle_solver main.cpp -D _DEBUG -g

build_release:
	g++ -std=c++17 -obin/wordle_solver main.cpp

run:
	rm -rf ./bin/wordle_solver
	make build
	./bin/wordle_solver
