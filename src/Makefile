CHARMC=/home/nikhil/charm/net-linux-x86_64/bin/charmc $(OPTS)

OBJS = RTCharm.o

all: RTCharm

RTCharm: $(OBJS)
	$(CHARMC) -language charm++ -o RTCharm $(OBJS)

RTCharm.decl.h: RTCharm.ci
	$(CHARMC)  RTCharm.ci

clean:
	rm -f *.decl.h *.def.h conv-host *.o RTCharm charmrun

RTCharm.o: RTCharm.C RTCharm.decl.h
	$(CHARMC) -c RTCharm.C

test: all
	./charmrun RTCharm +p4 ++local $(TESTOPTS)

