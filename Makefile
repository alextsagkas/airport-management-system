all: exec_airport_management exec_evretirio exec_tebst exec_teindex exec_rbt exec_int exec_string

# ------------------------------------------------------- #

exec_airport_management: airportmanagement evretirio tebst teindex rbt
	gcc AirportManagement.o index/Evretirio.o  index/tebst.o index/teindex.o rbt_module/rbt.o -o executables/exec_airport_management
	# ./executables/exec_airport_management

exec_evretirio: rbt tebst teindex evretirio scaffold_evretirio
	gcc rbt_module/rbt.o index/tebst.o index/teindex.o scaffolds/scaffold_evretirio.o index/Evretirio.o -o executables/exec_evretirio
	# ./executables/exec_evretirio

exec_tebst: tebst scaffold_tebst
	gcc scaffolds/scaffold_tebst.o index/tebst.o -o executables/exec_tebst
	# ./executables/exec_tebst

exec_teindex: teindex scaffold_teindex
	gcc scaffolds/scaffold_teindex.o index/teindex.o -o executables/exec_teindex
	# ./executables/exec_teindex

exec_rbt: int string rbt scaffold_rbt
	gcc scaffolds/scaffold_rbt.o rbt_module/rbt.o int_module/int.o string_module/string.o -o executables/exec_rbt
	# ./executables/exec_rbt

exec_int: int scaffold_int
	gcc scaffolds/scaffold_int.o int_module/int.o -o executables/exec_int
	# ./executables/exec_int

exec_string: string scaffold_string
	gcc scaffolds/scaffold_string.o string_module/string.o -o executables/exec_string
	# ./executables/exec_string

# ------------------------------------------------------- #

airportmanagement: AirportManagement.c 
	gcc -c AirportManagement.c -o AirportManagement.o

scaffold_evretirio: scaffolds/scaffold_evretirio.c
	gcc -c scaffolds/scaffold_evretirio.c -o scaffolds/scaffold_evretirio.o

scaffold_tebst: scaffolds/scaffold_tebst.c
	gcc -c scaffolds/scaffold_tebst.c -o scaffolds/scaffold_tebst.o

scaffold_teindex: scaffolds/scaffold_teindex.c
	gcc -c scaffolds/scaffold_teindex.c -o scaffolds/scaffold_teindex.o

scaffold_rbt: scaffolds/scaffold_rbt.c
	gcc -c scaffolds/scaffold_rbt.c -o scaffolds/scaffold_rbt.o

scaffold_int: scaffolds/scaffold_int.c
	gcc -c scaffolds/scaffold_int.c -o scaffolds/scaffold_int.o

scaffold_string: scaffolds/scaffold_string.c
	gcc -c scaffolds/scaffold_string.c -o scaffolds/scaffold_string.o

# ------------------------------------------------------- #

int: int_module/int.c int_module/int.h
	gcc -c int_module/int.c -o int_module/int.o

string: string_module/string.c string_module/string.h
	gcc -c string_module/string.c -o string_module/string.o 

rbt: rbt_module/rbt.c rbt_module/rbt.h
	gcc -c rbt_module/rbt.c -o rbt_module/rbt.o 

teindex: index/teindex.c index/teindex.h
	gcc -c index/teindex.c -o index/teindex.o

tebst: index/tebst.c index/tebst.h
	gcc -c index/tebst.c -o index/tebst.o

evretirio: index/Evretirio.c index/Evretirio.h
	gcc -c index/Evretirio.c -o index/Evretirio.o

# ------------------------------------------------------- #

clean: 
	find . -name "*.o" -type f -delete
	find . -name "exec_*" -type f -delete
	rm -rf ./data/linux/test/*

# ------------------------------------------------------- #