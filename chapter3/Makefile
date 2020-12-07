CPPFLAGS = -g

all: forkexec forktree forktree_simple zombie orphan

forkexec: forkexec.o 
	$(CXX) -o $@ $^

forktree: forktree.o 
	$(CXX) -o $@ $^

forktree_simple: forktree_simple.o 
	$(CXX) -o $@ $^

zombie: zombie.o
	$(CXX) -o $@ $^

orphan: orphan.o
	$(CXX) -o $@ $^

.PHONY: clean
clean:
	rm -f forkexec forktree zombie orphan
