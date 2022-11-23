#ifndef SHOGI_H
#define SHOGI_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#define PRINT_ATTR_GLI
#define ROW 9
#define COLUMN 9
#define RECORDS 500

struct node {
    char eatenchessx[RECORDS/2],eatenchessy[RECORDS/2],chess[ROW][COLUMN];
    struct node *next,*prev; 
};

typedef struct node NODE;

extern NODE *first,*current,*previous;
extern NODE* newnode;

extern char locbx;
extern int locby,locax,locay;
extern int ax, ay, bx, by;
extern int numx, numy;
extern int count,player;

void chessinitial();
void chessprint();
void chessmove();
void chessback();
int win();
int movecheck();
int eatchess();
int hitin();
int chesstransform();

#endif