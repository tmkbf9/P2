.PHONY: clean compile test

GCC := g++
CFLAGS := -g
CPPFLAGS := --std=c++98
RM := rm
AR := ar

.cpp.o:
	$(GCC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

all: test frontEnd

frontEnd: P2.o parser.o available_tokens.o test_tree.o libscanner.a
	$(GCC) -o $@ $^ libscanner.a

libscanner.a: scanner.o token.o 
	$(AR) rcs $@ $^

test: parser_test
	./parser_test

parser_test: parser_test.o parser.o available_tokens.o test_tree.o libscanner.a 
	$(GCC) -o $@ $^

clean:
	$(RM) -f frontEnd
	$(RM) -f parser_test
	$(RM) -f libscanner.a
	$(RM) -f *.o
	$(RM) -f *~
