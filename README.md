# Shogi in C

Assignment 2

# Compile
```
gcc -c src/main.c -o build/main.o
gcc -c src/shogi.c -o build/shogi.o
gcc -c src/file.c -o build/file.o
gcc -c src/timer.c -o build/timer.o
gcc build/main.o build/shogi.o build/file.o build/timer.o -o bin/shogi -lev
```
or
```
make
```
# Run
#To create new game :
```
./bin/shogi -n -s chessgame.txt
```
or
```
make run1
```


Player Enter the location of the chess you want to move.(location entering way: X space Y)


Player Enter the location where you want to move the chess to.


If the movement meets the rule the chess will move and change the player's turn.


If anyone go into the enemy's area, he can chose to promotion the chess.


Enter h to let the chess return to the game(hit in).


If anyone regrets the movement, he can return the chess by entering 0.


Enter s to save the game and the playing time. 


Enter x to end the game.

#To load old game :

```
./bin/shogi -l chessgame.txt 
```
or
```
make run2
```


Enter f to see the next chessboard.

Enter b to see the Previous chessboard.

Enter p to continue playing the game basic on the step you see.

Enter x to end reading.
