all: cmark-roff

cmark-roff: cmark-roff.c cmark-roff-backend.h cmark-roff-backend.c
	cc -I/usr/local/include -L/usr/local/lib -lcmark -o cmark-roff cmark-roff.c cmark-roff-backend.c

debug: cmark-roff.c cmark-roff-backend.h cmark-roff-backend.c
	cc -g -I/usr/local/include -L/usr/local/lib -lcmark -o cmark-roff cmark-roff.c cmark-roff-backend.c

clean:
	rm -f cmark-roff *.o

strip: cmark-roff
	strip cmark-roff
