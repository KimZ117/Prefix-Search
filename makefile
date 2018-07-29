autocomplete: main_1.o main_2.o ternary.o
				gcc -o autocomplete1 main_1.o ternary.o -std=c99
				gcc -o autocomplete2 main_2.o ternary.o -std=c99

main_1.o: main_1.c ternary.h
			gcc -c main_1.c -std=c99
main_2.o: main_2.c ternary.h
			gcc -c main_2.c -std=c99
ternary.o: ternary.h
			gcc -c ternary.c -std=c99

clean:
		rm *o
		rm autocomplete1.exe
		rm autocomplete2.exe