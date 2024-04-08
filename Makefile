.PHONY: test
test:
	@clear
	@mkdir -p ./bin
	@g++ ./src/testing.cpp ./src/Visualiser/Visualiser.cpp -o ./bin/testing && ./bin/testing