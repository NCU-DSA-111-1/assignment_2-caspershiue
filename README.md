# Shogi in C

Assignment 2

# Compile
```
gcc -c src/main.c -o build/main.o
gcc -c src/shogi.c -o build/shogi.o
gcc -c src/file.c -o build/file.o
gcc build/main.o build/shogi.o build/file.o -o bin/shogi
```
or
```
make
```
# Run
```
./bin/shogi -n -s chessgame.txt
```

Player x Enter the location of the chess you want to move.


Player x Enter the location where you want to move the chess to.


Player y Enter the location of the chess you want to move.


Player y Enter the location where you want to move the chess to.


If anyone go into the enemy's area, he can chose to promotion the chess.


Enter h to let the chess return to the game(hit in).


If anyone regrets the movement, he can return the chess by entering 0.


Enter s to save the game. 


Enter x to end the game.
```
./bin/shogi -l chessgame.txt 
```
Enter f to see the next chessboard.


Enter r to see the Previous chessboard.


Enter p to continue playing the game basic on the step you see.


Enter x to end reading.
