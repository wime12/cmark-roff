all: cmark-roff

cmark-roff: cmark-roff.c cmark-roff-backend.h cmark-roff-backend.c
	cc -Wall -I/usr/local/include -L/usr/local/lib -o cmark-roff cmark-roff.c cmark-roff-backend.c -lcmark

debug: cmark-roff.c cmark-roff-backend.h cmark-roff-backend.c
	cc -Wall -g -I/usr/local/include -L/usr/local/lib -o cmark-roff.debug cmark-roff.c cmark-roff-backend.c -lcmark

clean:
	rm -f cmark-roff cmark-roff.debug *.o

strip: cmark-roff
	strip cmark-roff
