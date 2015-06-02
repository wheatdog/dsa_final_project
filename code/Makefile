CPPC = g++ 
CPPFLAGS = -O2 -std=c++11 -Wall
TARGET = main

all: $(TARGET)

%: %.c
	gcc $(CFLAGS) $< -o $@

%: %.cpp
	g++ $(CPPFLAGS) $< -o $@

main: main.cpp bank.h
	$(CPPC) $(CPPFLAGS) $< -o $@

clean:
	rm $(TARGET)

