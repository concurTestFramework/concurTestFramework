CC = g++
AR = ar
CFLAGS = -O0 -g
ARFLAGS =

OBJS = typeUtils.o sched.o
HDRS = typeUtils.h sched.h 

libsched.a: $(OBJS)
	$(AR)  -r libsched.a $(OBJS)

# Compile .cpp into .o
%.o:    %.cpp $(HDRS)
	$(CC) $(CFLAGS) -c $*.cpp
#        $(CC)  -lpthread $(CFLAGS) -c $*.cpp
 

clean:
	-rm -rf *.a
	-rm -rf *.o
