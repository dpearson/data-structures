# Copyright 2014 David Pearson.
# BSD License.

HAS_CLANG=$(shell which clang > /dev/null; echo $$?)
ifeq "$(HAS_CLANG)" "0"
	CC=clang
else
	CC=gcc
endif

RM=rm -rf

CFLAGS=-std=gnu99 -I./src/array -Wall -Werror
LFLAGS=

SRCFILES=src/array/array.c src/array/pointer_array.c src/tests/main.c src/tests/arraytests.c
OBJFILES=$(subst .c,.o,$(SRCFILES))

OUTFILE=test_all

all: test

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

test: $(OBJFILES)
	$(CC) -o $(OUTFILE) $(OBJFILES) $(LFLAGS)

cleanobjs:
	$(RM) $(OBJFILES)

clean: cleanobjs
	$(RM) $(OUTFILE)
