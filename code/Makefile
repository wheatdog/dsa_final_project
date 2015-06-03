CPPC = g++ 
CPPFLAGS = -O2 -std=c++11 -Wall
BINDIR = ./bin
TARGETS = main
OBJ = bank.o main.o

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

$(BINDIR)/main: $(PREFIX_OBJ)
	$(CPPC) $(CPPFLAGS) $(PREFIX_OBJ) -o $@

clean:
	rm $(PREFIX_TARGET)

.PHONY: all clean distclean
