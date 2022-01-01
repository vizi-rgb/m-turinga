a.out: main.c
	cc main.c -pedantic -Wextra -Wall -ggdb

.PHONY: clean

clean:
	rm a.out
