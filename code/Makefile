CPPC = g++ 
CPPFLAGS = -O2 -std=c++11 -Wall
BINDIR = ./bin
TARGETS = main

PREFIX_TARGET = $(addprefix $(BINDIR)/,$(TARGETS))

all: $(PREFIX_TARGET)

$(BINDIR)/%: %.c
	gcc $(CFLAGS) $< -o $@

$(BINDIR)/%: %.cpp
	g++ $(CPPFLAGS) $< -o $@

$(BINDIR)/main: main.cpp bank.h
	$(CPPC) $(CPPFLAGS) $< -o $@

clean:
	rm $(PREFIX_TARGET)

.PHONY: all clean distclean
