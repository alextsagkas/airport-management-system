# ------------------------------------------------------- #

exec_rbt: int string rbt scaffold_rbt
	gcc scaffolds/scaffold_rbt.o rbt_module/rbt.o int_module/int.o string_module/string.o -o executables/exec_rbt
	./executables/exec_rbt

exec_int: int scaffold_int
	gcc scaffolds/scaffold_int.o int_module/int.o -o executables/exec_int
	./executables/exec_int

exec_string: string scaffold_string
	gcc scaffolds/scaffold_string.o string_module/string.o -o executables/exec_string
	./executables/exec_string

# ------------------------------------------------------- #

scaffold_rbt: scaffolds/scaffold_rbt.c
	gcc -c scaffolds/scaffold_rbt.c -o scaffolds/scaffold_rbt.o

scaffold_int: scaffolds/scaffold_int.c
	gcc -c scaffolds/scaffold_int.c -o scaffolds/scaffold_int.o

scaffold_string: scaffolds/scaffold_string.c
	gcc -c scaffolds/scaffold_string.c -o scaffolds/scaffold_string.o

int: int_module/int.c int_module/int.h
	gcc -c int_module/int.c -o int_module/int.o

string: string_module/string.c string_module/string.h
	gcc -c string_module/string.c -o string_module/string.o 

rbt: rbt_module/rbt.c rbt_module/rbt.h
	gcc -c rbt_module/rbt.c -o rbt_module/rbt.o 

# ------------------------------------------------------- #

clean: 
	find . -name "*.o" -type f -delete
	find . -name "exec_*" -type f -delete

# ------------------------------------------------------- #