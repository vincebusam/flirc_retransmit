all: flirc_retransmit

flirc_retransmit: flirc_retransmit.c
	gcc -g -I ~/src/flirc-sdk/libs/flirc -I ~/src/flirc-sdk/cli/include -o flirc_retransmit flirc_retransmit.c ~/src/flirc-sdk/libs/Linux_armv6l/libflirc.a -lusb-1.0 -lhidapi-hidraw

clean:
	rm -f flirc_retransmit *.o
