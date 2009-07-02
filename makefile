CC = g++

CCFLAGS = -I /opt/local/var/macports/software/boost/1.39.0_2/opt/local/include -Wall

OBJS =	dynamic.o \
		types.o \
		ctor.o \
		array.o \
		list.o \
		dict.o \
		set.o \
		assign.o \
		relational.o

dynamic.a: $(OBJS)
	echo build dynamic.a

types.o: types.cpp dynamic.h
	$(CC) -c $(CCFLAGS) $< -o $@

dynamic.o: dynamic.cpp dynamic.h
	$(CC) -c $(CCFLAGS) $< -o $@

ctor.o: ctor.cpp dynamic.h
	$(CC) -c $(CCFLAGS) $< -o $@

array.or: array.cpp dynamic.h
	$(CC) -c $(CCFLAGS) $< -o $@

list.o: list.cpp dynamic.h
	$(CC) -c $(CCFLAGS) $< -o $@

dict.o: dict.cpp dynamic.h
	$(CC) -c $(CCFLAGS) $< -o $@

set.o: set.cpp dynamic.h
	$(CC) -c $(CCFLAGS) $< -o $@

assign.o: assign.cpp dynamic.h
	$(CC) -c $(CCFLAGS) $< -o $@

relational.o: relational.cpp dynamic.h
	$(CC) -c $(CCFLAGS) $< -o $@

clean:
	rm *.o