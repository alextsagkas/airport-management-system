exec_rbt: key rbt scaffold_rbt
	gcc scaffold_rbt.o rbt.o key.o -o exec_rbt
	./exec_rbt

exec_key: key scaffold_key
	gcc scaffold_key.o key.o -o exec_key
	./exec_key

scaffold_rbt: scaffold_rbt.c
	gcc -c scaffold_rbt.c 

scaffold_key: key
	gcc -c scaffold_key.c 

key: key.c key.h
	gcc -c key.c

rbt: rbt.c rbt.h
	gcc -c rbt.c

clean: 
	rm *.o
	rm exec_*