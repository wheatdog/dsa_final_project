CPPC = g++ 
CPPFLAGS = -O2 -std=c++11 -Wall
BINDIR = ./bin
TARGETS = main
OBJ = bank.o main.o

CREATE_BINDIR = mkdir -p $(BINDIR)
RM = rm -rf

PREFIX_TARGET = $(addprefix $(BINDIR)/,$(TARGETS))
PREFIX_OBJ = $(addprefix $(BINDIR)/,$(OBJ))

all: $(PREFIX_TARGET)

$(BINDIR)/%.o: %.c
	@$(CREATE_BINDIR)
	$(CC) $(CFLAGS) $< -c -o $@

$(BINDIR)/%.o: %.cpp
	@$(CREATE_BINDIR)
	$(CXX) $(CXXFLAGS) $< -c -o $@

$(BINDIR)/main: $(PREFIX_OBJ)
	@$(CREATE_BINDIR)
	$(CPPC) $(CPPFLAGS) $(PREFIX_OBJ) -o $@

clean:
	$(RM) $(BINDIR)

.PHONY: all clean
