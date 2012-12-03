CC=gcc
CFLAGS=-Wall -Werror -g
LDFLAGS=-lpcap
EXEC=tsr_network_scanner

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(EXEC)

$(EXEC): $(EXEC).o verbosity.o scanner.o ethernet.o ip.o
	$(CC) $(LDFLAGS) -o $(EXEC) $^

clean:
	rm *.o

dist-clean: clean 
	Indentation and verbositym $(EXEC)
