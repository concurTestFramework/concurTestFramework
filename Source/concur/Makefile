all: orig custom

PROG = concur
OBJS = main.o sections.o util.o
HDRS = sections.h util.h 
LIBS = -lpthread

SUDS_DIR = /home/fac/elarson/concur-suds
LIBSCHED_DIR = scheduler

CPP = gcc -E
CC = gcc
LD = g++

CPPFLAGS = 
CFLAGS = $(CPPFLAGS)-O0 -Wall -Wno-implicit -g
LDFLAGS = -lpthread

ORIG_EXE = $(PROG)
ORIG_OBJS = $(OBJS)

SYNCH_EXE = $(PROG).synch.exe
SYNCH_OBJS = $(OBJS:.o=.synch.o)
SYNCH_SRC = $(OBJS:.o=.synch.c)

PPFILES = $(OBJS:.o=.i)

orig: $(ORIG_EXE) 

$(ORIG_EXE): $(ORIG_OBJS) synchlib
#	$(LD) $(LDFLAGS) -o $@ $(ORIG_OBJS) $(LIBS)
	$(LD) $(LDFLAGS) -o $@ $(ORIG_OBJS) $(LIBS) -L$(LIBSCHED_DIR) -lsched


# $(ORIG_OBJS): %.o : %.c $(HDRS)
$(ORIG_OBJS): %.o : %.i $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

custom: $(SYNCH_EXE)

$(SYNCH_EXE): $(SYNCH_OBJS) synchlib
	$(LD) $(LDFLAGS) -o $@ $(SYNCH_OBJS) $(LIBS) -L$(LIBSCHED_DIR) -lsched

$(SYNCH_OBJS): %.o : %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

$(SYNCH_SRC): $(PPFILES)
	$(SUDS_DIR)/suds -suffix synch -f $(PROG).gbl

synchlib:
	make -C $(LIBSCHED_DIR)

.DELETE_ON_ERROR: $(SYNCH_SRC)

$(PPFILES): %.i : %.c $(HDRS)
	$(CPP) $(CPPFLAGS) $< > $@

clean: 
	make -C $(LIBSCHED_DIR) clean
	rm -f $(ORIG_EXE) $(ORIG_OBJS)
	rm -f $(SYNCH_EXE) $(SYNCH_OBJS) $(SYNCH_SRC)
	rm -f *.i
	rm -f *.dump *.out *.stats
