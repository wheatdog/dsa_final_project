CPPC = g++ 
CPPFLAGS = -O2 -std=c++11 -Wall
BINDIR = ./bin
TARGETS = newmain #main
OBJ = bank.o newmain.o

PREFIX_TARGET = $(addprefix $(BINDIR)/,$(TARGETS))
PREFIX_OBJ = $(addprefix $(BINDIR)/,$(OBJ))

all: $(PREFIX_TARGET)

$(BINDIR)/%.o:%.c
	$(CC) $(CFLAGS) $< -c -o $@

$(BINDIR)/%.o:%.cpp
	$(CXX) $(CXXFLAGS) $< -c -o $@

$(BINDIR)/%: %.c
	gcc $(CFLAGS) $< -o $@

$(BINDIR)/%: %.cpp
	g++ $(CPPFLAGS) $< -o $@

$(BINDIR)/main: main.cpp bank.h
	$(CPPC) $(CPPFLAGS) $< -o $@

$(BINDIR)/newmain: $(PREFIX_OBJ)
	$(CPPC) $(CPPFLAGS) $(PREFIX_OBJ) -o $@

clean:
	rm $(PREFIX_TARGET)

.PHONY: all clean distclean
