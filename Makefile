shogi: main.o shogi.o file.o
	gcc build/main.o build/shogi.o build/file.o -o bin/shogi

main.o: src/main.c
	gcc -c src/main.c -o build/main.o

shogi.o: src/shogi.c
	gcc -c src/shogi.c -o build/shogi.o

file.o: src/file.c
	gcc -c src/file.c -o build/file.o

clean:
	-rm build/main.o build/shogi.o build/file.o
	-rm bin/shogi