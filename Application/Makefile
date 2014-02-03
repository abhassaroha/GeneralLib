CC=gcc
CFLAGS= -Wall -c
IFLAGS=-I ./includes/

all:
	echo "There is no all"

smc_src=src/SimpleChatClient.c src/Client.c src/Server.c
smc_obj=$(smc_src:.c=.o)
smc: $(smc_obj)
	$(CC) $(IFLAGS) $(smc_obj) -o $@
.c.o:
	$(CC) $(CFLAGS) $(IFLAGS) $< -o $@

clean:
	rm -f src/*.o

