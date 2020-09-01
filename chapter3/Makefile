CPPFLAGS = -g

all: forkexec forktree zombie orphan

forkexec: forkexec.o 
	$(CXX) -o $@ $^

forktree: forktree.o 
	$(CXX) -o $@ $^

zombie: zombie.o
	$(CXX) -o $@ $^

orphan: orphan.o
	$(CXX) -o $@ $^

.PHONY: clean
clean:
	rm -f forkexec forktree zombie orphan
