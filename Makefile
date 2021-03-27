obj_assembler = table_class.o array_class.o assembler.o
obj_cpu = stack_class.o CPU_class.o

asm: $(obj_assembler)
	g++ -o asm $(obj_assembler)

table_class.o: headers/table_class.cpp
	g++ -c headers/table_class.cpp

array_class.o: headers/array_class.cpp
	g++ -c headers/array_class.cpp

assembler.o: assembler.cpp
	g++ -c assembler.cpp

	
CPU: $(obj_cpu)
	g++ -o CPU $(obj_cpu)	

stack_class.o: headers/stack_class.cpp
	g++ -c headers/stack_class.cpp

CPU_class.o: headers/CPU_class.cpp
	g++ -c headers/CPU_class.cpp


.PHONY : clean
clean:
	rm -rf *.o asm
	rm -rf *.o CPU
	













