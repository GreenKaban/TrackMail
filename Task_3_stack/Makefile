CC := g++
CFLAGS := -Wall -Wextra -Werror -Wno-unused -std=gnu++17 -fsanitize=address
FILES := main.cpp stack.hpp stacklib.hpp logs.hpp templates.hpp
	
all: main

main: $(FILES) 
	 $(CC) $(CFLAGS) -D NDEBUG -D DEBUG_LEVEL=0 main.cpp -o main

debug-dump: $(FILES)
	 $(CC) $(CFLAGS) -g -D DEBUG_LEVEL=1 main.cpp -o debug-dump

debug-canary: $(FILES)
	 $(CC) $(CFLAGS) -g -D DEBUG_LEVEL=2 main.cpp -o debug-canary

debug-hash: $(FILES)
	 $(CC) $(CFLAGS) -g -D DEBUG_LEVEL=3 main.cpp -o debug-hash

clean:
	rm -f *.o main debug-*