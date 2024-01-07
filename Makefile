exec: RBT scaffold
	gcc scaffold.o RBT.o -o exec
	./exec

scaffold: scaffold.c
	gcc -c scaffold.c 

RBT: RBT.c RBT.h
	gcc -c RBT.c

clean: 
	rm *.o