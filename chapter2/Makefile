CPPFLAGS = -g

all: copyfile copyfile-complex


copyfile: copyfile.o 
	$(CXX) -o $@ $^

copyfile-complex: copyfile-complex.o 
	$(CXX) -o $@ $^

.PHONY: clean
clean:
	rm -f test_json