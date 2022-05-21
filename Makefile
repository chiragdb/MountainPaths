INCLUDES=-I includes/
CXXFLAGS=-std=c++20 -stdlib=libc++ -lc++abi -g -O0 -Wall -Wextra -Werror -pedantic $(INCLUDES)
CXX=clang++

exec: bin/main.out
	- $<

tests: bin/tests.out
	- $<

clean:
	rm -f bin/*

bin/main.out: ./src/driver.cc ./src/color.cc ./src/elevation_dataset.cc ./src/grayscale_image.cc ./src/path_image.cc ./src/path.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/tests.out: ./tests/tests.cc ./src/color.cc ./src/elevation_dataset.cc ./src/grayscale_image.cc ./src/path_image.cc ./src/path.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

src/%.cc: includes/%.hpp
	touch $@

.DEFAULT_GOAL := tests
.PHONY: test clean exec