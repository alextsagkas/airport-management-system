exec: key rbt scaffold
	gcc scaffold.o rbt.o key.o -o exec
	./exec

scaffold: scaffold.c
	gcc -c scaffold.c 

key: key.c key.h
	gcc -c key.c

rbt: rbt.c rbt.h
	gcc -c rbt.c

clean: 
	rm *.o