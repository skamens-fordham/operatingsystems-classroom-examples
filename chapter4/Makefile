CPPFLAGS = -g
LDFLAGS = -lpthread

all: sumthread-single sumthread-multi

sumthread-single: sumthread-single.o 
	$(CXX) -o $@ $^ $(LDFLAGS)

sumthread-multi: sumthread-multi.o 
	$(CXX) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm sumthread-single sumthread-multi
