default:
	gcc -c src/student_t.c -I src/include -lm -o build/student_t.o
	gcc -c src/main.c -I src/include -lm -o build/main.o
	gcc -o build/main build/student_t.o build/main.o -I src/include -lm
