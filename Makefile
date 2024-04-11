


test:compile
	@clear && ./bin/main
compile:
	@mkdir -p ./bin
	g++ ./src/testing.cpp ./src/Visualiser/Visualiser.cpp -o ./bin/main