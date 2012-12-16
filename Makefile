CC=gcc
CFLAGS=-Wall -Werror -g -I.
LDFLAGS=-lpcap
EXEC=tsr_network_scanner

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(EXEC)

DATA_LINK_OBJECTS=data_link/ethernet.o
NETWORK_OBJSCTS=network/ip.o network/ip6.o network/icmp.o network/arp.o
TRANSPORT_OBJECTS=transport/udp.o transport/tcp.o
APPLICATION_OBJECTS=application/dhcp.o application/dns.o application/ftp.o application/http.o
OBJECTS=$(EXEC).o verbosity.o scanner.o output.o

ALL_OBJECTS=$(OBJECTS) $(APPLICATION_OBJECTS) $(TRANSPORT_OBJECTS) $(NETWORK_OBJSCTS) $(DATA_LINK_OBJECTS)


$(EXEC): $(ALL_OBJECTS)
	$(CC) $(LDFLAGS) -o $(EXEC) $^

clean:
	find -iname "*.o" | xargs rm
	

dist-clean: clean 
	rm $(EXEC)
