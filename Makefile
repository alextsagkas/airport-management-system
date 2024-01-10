# ------------------------------------------------------- #

exec_rbt: int rbt scaffold_rbt
	gcc scaffold_rbt.o rbt.o int.o -o exec_rbt
	./exec_rbt

exec_int: int scaffold_int
	gcc scaffold_int.o int.o -o exec_int
	./exec_int

exec_string: string scaffold_string
	gcc scaffold_string.o string.o -o exec_string
	./exec_string

# ------------------------------------------------------- #

scaffold_rbt: scaffold_rbt.c
	gcc -c scaffold_rbt.c 

scaffold_int: scaffold_int.c
	gcc -c scaffold_int.c 

scaffold_string: scaffold_string.c
	gcc -c scaffold_string.c 

int: int.c int.h
	gcc -c int.c

string: string.c string.h
	gcc -c string.c

rbt: rbt.c rbt.h
	gcc -c rbt.c

# ------------------------------------------------------- #

clean: 
	rm *.o
	rm exec_*

# ------------------------------------------------------- #