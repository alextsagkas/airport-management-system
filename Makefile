all: exec_airport_management exec_evretirio exec_tsdda exec_tsevr exec_rbt exec_int exec_string

# ------------------------------------------------------- #

exec_airport_management: airportmanagement evretirio tsdda tsevr rbt
	gcc AirportManagement.o index/Evretirio.o  index/TSDDA.o index/TSEvr.o rbt_module/rbt.o -o executables/exec_airport_management
	# ./executables/exec_airport_management

exec_evretirio: rbt tsdda tsevr evretirio scaffold_evretirio
	gcc rbt_module/rbt.o index/tsdda.o index/TSEvr.o scaffolds/scaffold_evretirio.o index/Evretirio.o -o executables/exec_evretirio
	# ./executables/exec_evretirio

exec_tsdda: tsdda scaffold_tsdda
	gcc scaffolds/scaffold_tsdda.o index/tsdda.o -o executables/exec_tsdda
	# ./executables/exec_tsdda

exec_tsevr: tsevr scaffold_tsevr
	gcc scaffolds/scaffold_tsevr.o index/TSEvr.o -o executables/exec_tsevr
	# ./executables/exec_tsevr

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

scaffold_tsdda: scaffolds/scaffold_tsdda.c
	gcc -c scaffolds/scaffold_tsdda.c -o scaffolds/scaffold_tsdda.o

scaffold_tsevr: scaffolds/scaffold_tsevr.c
	gcc -c scaffolds/scaffold_tsevr.c -o scaffolds/scaffold_tsevr.o

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

tsevr: index/TSEvr.c index/TSEvr.h
	gcc -c index/TSEvr.c -o index/TSEvr.o

tsdda: index/tsdda.c index/tsdda.h
	gcc -c index/tsdda.c -o index/tsdda.o

evretirio: index/Evretirio.c index/Evretirio.h
	gcc -c index/Evretirio.c -o index/Evretirio.o

# ------------------------------------------------------- #

clean: 
	find . -name "*.o" -type f -delete
	find . -name "exec_*" -type f -delete
	rm -rf ./data/linux/test/*

# ------------------------------------------------------- #