CC = gcc

# Generation of the executables/binaries

exec_airport_management: airport_management index tebst teindex rbt
	@echo ""
	@echo "Compiling and running the airport management program..."
	@echo ""
	$(CC) airport_management.o index_module/index.o  ebst_module/tebst.o eindex_module/teindex.o rbt_module/rbt.o -o executables/exec_airport_management
	./executables/exec_airport_management

exec_index: rbt tebst teindex index scaffold_index
	@echo ""
	@echo "Compiling and running the index program..."
	@echo ""
	$(CC) rbt_module/rbt.o ebst_module/tebst.o eindex_module/teindex.o scaffolds/scaffold_index.o index_module/index.o -o executables/exec_index
	./executables/exec_index

exec_tebst: tebst scaffold_tebst
	@echo ""
	@echo "Compiling and running the tebst program..."
	@echo ""
	$(CC) scaffolds/scaffold_tebst.o ebst_module/tebst.o -o executables/exec_tebst
	./executables/exec_tebst

exec_teindex: teindex scaffold_teindex
	@echo ""
	@echo "Compiling and running the teindex program..."
	@echo ""
	$(CC) scaffolds/scaffold_teindex.o eindex_module/teindex.o -o executables/exec_teindex
	./executables/exec_teindex

exec_rbt: int string rbt scaffold_rbt
	@echo ""
	@echo "Compiling and running the rbt program..."
	@echo ""
	$(CC) scaffolds/scaffold_rbt.o rbt_module/rbt.o int_module/int.o string_module/string.o -o executables/exec_rbt
	./executables/exec_rbt

exec_int: int scaffold_int
	@echo ""
	@echo "Compiling and running the int program..."
	@echo ""
	$(CC) scaffolds/scaffold_int.o int_module/int.o -o executables/exec_int
	./executables/exec_int

exec_string: string scaffold_string
	@echo ""
	@echo "Compiling and running the string program..."
	@echo ""
	$(CC) scaffolds/scaffold_string.o string_module/string.o -o executables/exec_string
	./executables/exec_string

# Scaffold compilation

airport_management: airport_management.c airport_management.o
	$(CC) -c airport_management.c -o airport_management.o

scaffold_index: scaffolds/scaffold_index.c scaffolds/scaffold_index.o
	$(CC) -c scaffolds/scaffold_index.c -o scaffolds/scaffold_index.o

scaffold_tebst: scaffolds/scaffold_tebst.c scaffolds/scaffold_tebst.o
	$(CC) -c scaffolds/scaffold_tebst.c -o scaffolds/scaffold_tebst.o

scaffold_teindex: scaffolds/scaffold_teindex.c scaffolds/scaffold_teindex.o
	$(CC) -c scaffolds/scaffold_teindex.c -o scaffolds/scaffold_teindex.o

scaffold_rbt: scaffolds/scaffold_rbt.c scaffolds/scaffold_rbt.o
	$(CC) -c scaffolds/scaffold_rbt.c -o scaffolds/scaffold_rbt.o

scaffold_int: scaffolds/scaffold_int.c scaffolds/scaffold_int.o
	$(CC) -c scaffolds/scaffold_int.c -o scaffolds/scaffold_int.o

scaffold_string: scaffolds/scaffold_string.c scaffolds/scaffold_string.o
	$(CC) -c scaffolds/scaffold_string.c -o scaffolds/scaffold_string.o

# Module compilation

int: int_module/int.c int_module/int.h int_module/int.o
	$(CC) -c int_module/int.c -o int_module/int.o

string: string_module/string.c string_module/string.h string_module/string.o
	$(CC) -c string_module/string.c -o string_module/string.o 

rbt: rbt_module/rbt.c rbt_module/rbt.h rbt_module/rbt.o
	$(CC) -c rbt_module/rbt.c -o rbt_module/rbt.o 

teindex: eindex_module/teindex.c eindex_module/teindex.h eindex_module/teindex.o
	$(CC) -c eindex_module/teindex.c -o eindex_module/teindex.o

tebst: ebst_module/tebst.c ebst_module/tebst.h ebst_module/tebst.o
	$(CC) -c ebst_module/tebst.c -o ebst_module/tebst.o

index: index_module/index.c index_module/index.h index_module/index.o
	$(CC) -c index_module/index.c -o index_module/index.o

# Maintenance tasks

diff:
	@echo "The status of the repository and the volume of per-file changes:"
	@echo ""
	@git status
	@git --no-pager diff --stat

clean: 
	find . -name "*.o" -type f -delete
	find . -name "exec_*" -type f -delete
	rm -rf ./data/test/*

# ------------------------------------------------------- #