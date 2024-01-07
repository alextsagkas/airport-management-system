exec: rbt scaffold
	gcc scaffold.o rbt.o -o exec
	./exec

scaffold: scaffold.c
	gcc -c scaffold.c 

rbt: rbt.c rbt.h
	gcc -c rbt.c

clean: 
	rm *.o