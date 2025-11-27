all: libimpl1.so libimpl2.so prog1 prog2

libimpl1.so: lib1.o
	gcc -shared -o libimpl1.so lib1.o -lm

libimpl2.so: lib2.o
	gcc -shared -o libimpl2.so lib2.o -lm

lib1.o: lib1.c
	gcc -c -fPIC lib1.c

lib2.o: lib2.c
	gcc -c -fPIC lib2.c

prog1: prog1.c libimpl1.so
	gcc prog1.c -L. -limpl1 -o prog1 -Wl,-rpath,.

prog2: prog2.c libimpl1.so libimpl2.so
	gcc prog2.c -o prog2 -ldl

clean:
	rm -f *.o *.so prog1 prog2
