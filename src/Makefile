#CHARMDIR = /dcsdata/home/ginsbur3/charm
#CHARMDIR = /home/nikhil/charm/net-linux-x86_64-smp
CHARMDIR =  /home/josh/gitRepos/charm
#CHARMDIR = /Users/harinirajesh/Desktop/charm/net-darwin-x86_64-smp/
#[put Charm++ install directory here] ^
CHARMC = $(CHARMDIR)/bin/charmc $(OPTS)

default: all
all: pixelchare

pixelchare : main.o pixelchare.o
	$(CHARMC) -language charm++ -module liveViz -balancer GreedyLB -o pixelchare main.o pixelchare.o -memory paranoid # -balancer RefineLB -tracemode projections

main.o : main.C main.h main.decl.h main.def.h pixelchare.decl.h common.h
	$(CHARMC) -g -o main.o main.C

main.decl.h main.def.h : main.ci
	$(CHARMC) main.ci

pixelchare.o : pixelchare.C pixelchare.h pixelchare.decl.h pixelchare.def.h main.decl.h ray.h vecmath.h
	$(CHARMC) -g -o pixelchare.o pixelchare.C

pixelchare.decl.h pixelchare.def.h : pixelchare.ci
	$(CHARMC) pixelchare.ci

clean:
	rm -f main.decl.h main.def.h main.o
	rm -f pixelchare.decl.h pixelchare.def.h pixelchare.o
	rm -f pixelchare.*.log.gz *~
	rm -f pixelchare.projrc pixelchare.sts pixelchare.topo
	rm -f myvalg_txt.*****
	rm -f pixelchare charmrun 
test:
	./charmrun pixelchare 520 520 8 3 +p8 +balancer GreedyLB ++server ++server-port 1237 +LBOff
