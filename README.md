# Shogi in C

Environment：Linux

Need to install lbev：

1.Download and Install
```
wget http://dist.schmorp.de/libev/libev-4.33.tar.gz
tar -xzf libev-4.33.tar.gz
cd libev-4.33
./configure
make
sudo make install
```

2.Configure Dynamic Linker

```
sudo sh -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/libev.conf'
sudo ldconfig
```
3.Set Set LD_LIBRARY_PATH
```
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
echo 'export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH' >> ~/.bashrc
source ~/.bashrc
```

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
sudo make
```
# Run
#To create new game :
```
sudo ./bin/shogi -n -s chessgame.txt
```
or
```
sudo make run1
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
sudo ./bin/shogi -l chessgame.txt 
```
or
```
sudo make run2
```


Enter f to see the next chessboard.

Enter b to see the Previous chessboard.

Enter p to continue playing the game basic on the step you see.

Enter x to end reading.
