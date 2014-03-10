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

CFLAGS=-std=gnu99 -I./src/array -I./src/linked_list -I./src/string -Wall -Werror
LFLAGS=-L. $(subst lib,-l,$(LIBNAME))

SRCFILES=src/array/array.c src/array/pointer_array.c src/linked_list/sll.c src/linked_list/dll.c src/string/cstr.c
OBJFILES=$(subst .c,.o,$(SRCFILES))

TESTSRCFILES=src/tests/main.c src/tests/arraytests.c src/tests/lltests.c
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