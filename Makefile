.PHONY: clean compile test

GCC := g++
CFLAGS := -g
CPPFLAGS := --std=c++98
RM := rm
AR := ar

.cpp.o:
	$(GCC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

all: test

#P2: libP1.a

libscanner.a: scanner.o token.o
	$(AR) rcs $@ $^

test: parser_test node_factory_test
	./parser_test
	./node_factory_test

parser_test: parser_test.o libscanner.a 
	$(GCC) -o $@ $^

node_factory_test: node_factory_test.o node_factory.o libscanner.a
	$(GCC) -o $@ $^ libscanner.a

clean:
	$(RM) -f P2
	$(RM) -f parser_test
	$(RM) -f libscanner.a
	$(RM) -f *.o
	$(RM) -f *~
