obj_assembler = table_class.o array_class.o assembler.o
obj_cpu = stack_class.o CPU_class.o CPU.o

asm: $(obj_assembler)
	g++ -o asm $(obj_assembler)

table_class.o: headers/table_class.cpp
	g++ -c headers/table_class.cpp

array_class.o: headers/array_class.cpp
	g++ -c headers/array_class.cpp

assembler.o: assembler.cpp
	g++ -c assembler.cpp

	
my_CPU: $(obj_cpu)
	g++ -o my_CPU $(obj_cpu)	

stack_class.o: headers/stack_class.cpp
	g++ -c headers/stack_class.cpp

CPU_class.o: headers/CPU_class.cpp
	g++ -c headers/CPU_class.cpp

CPU.0: CPU.cpp CPU_class.cpp
	g++ -c CPU.cpp

.PHONY : git_commit
git_commit:
	git add . 
	git commit -m "This was automatic commit"

.PHONY : clean
clean:
	rm -rf *.o asm
	rm -rf *.o CPU
	
