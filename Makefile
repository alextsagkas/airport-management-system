exec: key rbt scaffold
	gcc scaffold.o rbt.o key.o -o exec
	./exec

scaffold: scaffold.c
	gcc -c scaffold.c 

scaffold_key: key
	gcc scaffold_key.c key.o -o scaffold_key
	./scaffold_key

key: key.c key.h
	gcc -c key.c

rbt: rbt.c rbt.h
	gcc -c rbt.c

clean: 
	rm *.o