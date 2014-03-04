# Copyright 2014 David Pearson.
# BSD License.

HAS_CLANG=$(shell which clang > /dev/null; echo $$?)
ifeq "$(HAS_CLANG)" "0"
	CC=clang
else
	CC=gcc
endif

AR=ar
RM=rm -rf

LIBNAME=libstructs
OUTFILE=test_all

CFLAGS=-std=gnu99 -I./src/array -Wall -Werror
LFLAGS=-L. $(subst lib,-l,$(LIBNAME))

SRCFILES=src/array/array.c src/array/pointer_array.c
OBJFILES=$(subst .c,.o,$(SRCFILES))

TESTSRCFILES=src/tests/main.c src/tests/arraytests.c
TESTOBJFILES=$(subst .c,.o,$(TESTSRCFILES))

all: lib test

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

lib: $(OBJFILES)
	$(AR) rcs $(LIBNAME).a $(OBJFILES)

test: $(TESTOBJFILES)
	$(CC) -o $(OUTFILE) $(TESTOBJFILES) $(LFLAGS)

cleanobjs:
	$(RM) $(OBJFILES) $(TESTOBJFILES)

clean: cleanobjs
	$(RM) $(OUTFILE) $(LIBNAME).a
