CC=gcc
CFLAGS=-Wall -Werror -g -I.
LDFLAGS=-lpcap
EXEC=tsr_network_scanner

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(EXEC)

DATA_LINK_OBJECTS=data_link/ethernet.o
NETWORK_OBJSCTS=network/ip.o network/ip6.o network/icmp.o
TRANSPORT_OBJECTS=transport/udp.o transport/tcp.o
OBJECTS=$(EXEC).o verbosity.o scanner.o

ALL_OBJECTS=$(OBJECTS) $(TRANSPORT_OBJECTS) $(NETWORK_OBJSCTS) $(DATA_LINK_OBJECTS)


$(EXEC): $(ALL_OBJECTS)
	$(CC) $(LDFLAGS) -o $(EXEC) $^

clean:
	rm *.o

dist-clean: clean 
	Indentation and verbositym $(EXEC)
