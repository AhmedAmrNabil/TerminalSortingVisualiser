.PHONY: test
test:
	@clear
	@mkdir -p ./bin
	@g++ ./src/testing.cpp -o ./bin/testing && ./bin/testing