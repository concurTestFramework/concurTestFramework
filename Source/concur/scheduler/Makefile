CC = g++
AR = ar
CFLAGS = -O0 -g
ARFLAGS =

OBJS = utilities.o typeUtils.o logger.o sched.o
HDRS = utilities.o typeUtils.h logger.h sched.h 

libsched.a: $(OBJS)
	$(AR)  -r libsched.a $(OBJS)

# Compile .cpp into .o
%.o:    %.cpp $(HDRS)
	$(CC) $(CFLAGS) -c $*.cpp
#        $(CC)  -lpthread $(CFLAGS) -c $*.cpp
 

clean:
	-rm -rf *.a
	-rm -rf *.o
