shogi: main.o shogi.o file.o timer.o
	gcc build/main.o build/shogi.o build/file.o build/timer.o -o bin/shogi -lev

main.o: src/main.c
	gcc -c src/main.c -o build/main.o

shogi.o: src/shogi.c
	gcc -c src/shogi.c -o build/shogi.o

file.o: src/file.c
	gcc -c src/file.c -o build/file.o

timer.o: src/timer.c
	gcc -c src/timer.c -o build/timer.o

clean:
	-rm build/main.o build/shogi.o build/file.o build/timer.o
	-rm bin/shogi