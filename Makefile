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

test: parser_test
	./parser_test

parser_test: libP1.a 
	$(GCC) -o $@ $^

clean:
	$(RM) -f P2
	$(RM) -f parser_test
	$(RM) -f libscanner.a
	$(RM) -f *.o
	$(RM) -f *~
