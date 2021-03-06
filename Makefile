all: cmark-roff

cmark-roff: cmark-roff.c backend.h backend.c
	cc -Wall -I/usr/local/include -L/usr/local/lib -O2 -o cmark-roff cmark-roff.c backend.c -lcmark

debug: cmark-roff.c backend.h backend.c
	cc -Wall -g -I/usr/local/include -L/usr/local/lib -o cmark-roff.debug cmark-roff.c backend.c -lcmark

clean:
	rm -f cmark-roff cmark-roff.debug *.o

strip: cmark-roff
	strip cmark-roff

install: strip
	cp cmark-roff $(HOME)/.local/bin
