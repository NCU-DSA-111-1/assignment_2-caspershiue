#include "../inc/shogi.h"
#include "../inc/timer.h"

NODE *first,*current,*previous;
NODE* newnode;

char bx;
int by, ax, ay;
int numx=0, numy=0;
int count=1,player;

void chessinitial()
{
    int x,y;
    //initail eatenchess (b denotes that there is nothing in the space)
    for (x = 0; x < RECORDS/2; x++) {
        current->eatenchessx[x] = 'b';
        current->eatenchessy[x] = 'b';
    }
    //initial chess location
    for (y = 0; y < ROW; y++)
    {
        for (x = 0; x < COLUMN; x++)
        {
            current->chess[y][x] = 'b';
        }
    }
    current->chess[0][0] = 'p';
    current->chess[0][1] = 'n';
    current->chess[0][2] = 's';
    current->chess[0][3] = 'g';
    current->chess[0][4] = 'k';
    current->chess[0][5] = 'g';
    current->chess[0][6] = 's';
    current->chess[0][7] = 'n';
    current->chess[0][8] = 'p';
    current->chess[8][0] = 'P';
    current->chess[8][1] = 'N';
    current->chess[8][2] = 'S';
    current->chess[8][3] = 'G';
    current->chess[8][4] = 'K';
    current->chess[8][5] = 'G';
    current->chess[8][6] = 'S';
    current->chess[8][7] = 'N';
    current->chess[8][8] = 'P';
    current->chess[1][1] = 'f';
    current->chess[1][7] = 'a';
    current->chess[7][1] = 'A';
    current->chess[7][7] = 'F';
    for (x = 0; x < COLUMN; x++)
    {
        current->chess[2][x] = 'w';
        current->chess[6][x] = 'W';
    }
}
void chessprint()
{
    int x,y;
    //Print the chess player x ate
    for(x=0;x<=numx;x++){
        switch(current->eatenchessx[x]){
        case'P':
            printf("\033[31m香\033[m");
            break;
        case'N':
            printf("\033[31m桂\033[m");
            break;
        case'S':
            printf("\033[31m銀\033[m");
            break;
        case'G':
            printf("\033[31m金\033[m");
            break;
        case'K':
            printf("\033[31m玉\033[m");
            break;
        case'F':
            printf("\033[31m飛\033[m");
            break;
        case'A':
            printf("\033[31m角\033[m");
            break; 
        case'W':
            printf("\033[31m步\033[m");
            break;
        default:
            break;
        }
    }
    printf("\n  9 8 7 6 5 4 3 2 1\n ====================\n");//Print the board boundary and coordinate number
    //Print the chess
    for (y = 0; y < ROW; y++)
    {
        printf("||");
        for (x = 0; x < COLUMN; x++)
        {
            switch(current->chess[y][x]) {
            case'p':
                printf("\033[34m香\033[m");
                break;
            case'P':
                printf("\033[31m香\033[m");
                break;
            case'c':
                printf("\033[34m杏\033[m");
                break;
            case'C':
                printf("\033[31m杏\033[m");
                break;
            case'n':
                printf("\033[34m桂\033[m");
                break;
            case'N':
                printf("\033[31m桂\033[m");
                break;
            case't':
                printf("\033[34m圭\033[m");
                break;
            case'T':
                printf("\033[31m圭\033[m");
                break;
            case's':
                printf("\033[34m銀\033[m");
                break;
            case'S':
                printf("\033[31m銀\033[m");
                break;
            case'e':
                printf("\033[34m全\033[m");
                break;
            case'E':
                printf("\033[31m全\033[m");
                break;
            case'g':
                printf("\033[34m金\033[m");
                break;
            case'G':
                printf("\033[31m金\033[m");
                break;
            case'k':
                printf("\033[34m王\033[m");
                break;
            case'K':
                printf("\033[31m玉\033[m");
                break;
            case'f':
                printf("\033[34m飛\033[m");
                break;
            case'F':
                printf("\033[31m飛\033[m");
                break;
            case'd':
                printf("\033[34m龍\033[m");
                break;
            case'D':
                printf("\033[31m龍\033[m");
                break;
            case'a':
                printf("\033[34m角\033[m");
                break;
            case'A':
                printf("\033[31m角\033[m");
                break;
            case'h':
                printf("\033[34m馬\033[m");
                break;
            case'H':
                printf("\033[31m馬\033[m");
                break;
            case'w':
                printf("\033[34m步\033[m");
                break;
            case'W':
                printf("\033[31m步\033[m");
                break;
            case'j':
                printf("\033[34mと\033[m");
                break;
            case'J':
                printf("\033[31mと\033[m");
                break;
            default:
                printf("．");
                break;
            }
            
        }
        printf("||%d\n", y + 1);
    }
    printf(" ====================\n");
    //Print the chess player y ate
    for(x=0;x<=numy;x++){
        switch(current->eatenchessy[x]) {
        case'p':
            printf("\033[34m香\033[m");
            break;
        case'n':
            printf("\033[34m桂\033[m");
            break;
        case's':
            printf("\033[34m銀\033[m");
            break;
        case'g':
            printf("\033[34m金\033[m");
            break;
        case'k':
            printf("\033[34m王\033[m");
            break;
        case'f':
            printf("\033[34m飛\033[m");
            break;
        case'a':
            printf("\033[34m角\033[m");
            break;
        case'w':
            printf("\033[34m步\033[m");
            break;
        default:
            break;
        }
    }
    printf("\n");
}
//The rule of the chess movement
int movecheck()
{
    int i;
    if (player == 1) {
        switch (current->chess[by][bx]) {
        //Player X's chess(up)
        case'p':  //香
            if (ax == bx && ay > by){
                for (i = by + 1; i < ay; i++) {
                    if (current->chess[i][bx] != 'b')
                        return 0;
                }
                return 1;
            }
            else
                return 0;
            break;
        case'n':  //桂
            if (ay == by + 2 && (ax == bx + 1 || ax == bx - 1))
                return 1;
            else
                return 0;
            break;
        case's':  //銀
            if ((ay == by + 1 && ax == bx) || (ay == by + 1 && ax == bx - 1) || (ay == by + 1 && ax == bx + 1) || (ay == by - 1 && ax == bx - 1) || (ay == by - 1 && ax == bx + 1))
                return 1;
            else
                return 0;
            break;
        
        case'g':  //金
        case'c':  //杏(香 promote)
        case't':  //圭(桂 promote)
        case'e':  //全(銀 promote)
        case'j':  //と(步 promote)
            if ((ay == by + 1 && ax == bx) || (ay == by + 1 && ax == bx - 1) || (ay == by + 1 && ax == bx + 1) || (ay == by - 1 && ax == bx) || (ay == by && ax == bx + 1) || (ay == by && ax == bx - 1))
                return 1;
            else
                return 0;
            break;
        case'k':  //王
            if (abs(ax - bx) < 2 && abs(ay - by) < 2)
                return 1;
            else
                return 0;
            break;
        case'f':  //飛
            if (ax == bx && ay > by){
                for (i = by + 1; i < ay; i++) {
                    if (current->chess[i][bx] != 'b')
                        return 0;
                }
                return 1;
            }
            else if (ax == bx && ay < by){
                for (i = by - 1; i > ay; i--) {
                    if (current->chess[i][bx] != 'b')
                        return 0;
                }
                return 1;
            }
            else if (ay == by && ax > bx){
                for (i = bx + 1; i < ax; i++) {
                    if (current->chess[by][i] != 'b')
                        return 0;
                }
                return 1;
            }
            else if (ay == by && ax < bx){
                for (i = bx - 1; i > ax; i--) {
                    if (current->chess[by][i] != 'b')
                        return 0;
                }
                return 1;
            }
            else
                return 0;
            break;
        case'd':  //龍(飛 promote)
            if (ax == bx && ay > by){
                for (i = by + 1; i < ay; i++) {
                    if (current->chess[i][bx] != 'b')
                        return 0;
                }
                return 1;
            }
            else if (ax == bx && ay < by){
                for (i = by - 1; i > ay; i--) {
                    if (current->chess[i][bx] != 'b')
                        return 0;
                }
                return 1;
            }
            else if (ay == by && ax > bx){
                for (i = bx + 1; i < ax; i++) {
                    if (current->chess[by][i] != 'b')
                        return 0;
                }
                return 1;
            }
            else if (ay == by && ax < bx){
                for (i = bx - 1; i > ax; i--) {
                    if (current->chess[by][i] != 'b')
                        return 0;
                }
                return 1;
            }
            else if (abs(ax - bx) < 2 && abs(ay - by) < 2)
                return 1;
            else
                return 0;
            break;
        case'a':  //角
            if(ax - bx > 0 && ax - bx == ay - by){
                for (i = by + 1; i < ay; i++) {
                    if (current->chess[i][bx + i - by] != 'b')
                        return 0;
                }
                return 1;
            }
            else if(ax - bx < 0 && ax - bx == -(ay - by)){
                for (i = by + 1; i < ay; i++) {
                    if (current->chess[i][bx - i + by] != 'b')
                        return 0; 
                }
                return 1; 
            }
            else if(ax - bx > 0 && ax - bx == - (ay - by)){
                for (i = by - 1; i > ay; i--) {
                    if (current->chess[i][bx - i + by] != 'b')
                        return 0;    
                }
                return 1;
            }
            else if(ax - bx < 0 && ax - bx == ay - by){
                for (i = by - 1; i > ay; i--) {
                    if (current->chess[i][bx + i - by] != 'b')
                        return 0; 
                }
                return 1;
            }
            else
                return 0;
            break;
        case'h':  //馬(角 promote)
            if(ax - bx > 0 && ax - bx == ay - by){
                for (i = by + 1; i < ay; i++) {
                    if (current->chess[i][bx + i - by] != 'b')
                        return 0;
                }
                return 1;
            }
            else if(ax - bx < 0 && ax - bx == -(ay - by)){
                for (i = by + 1; i < ay; i++) {
                    if (current->chess[i][bx - i + by] != 'b')
                        return 0; 
                }
                return 1; 
            }
            else if(ax - bx > 0 && ax - bx == - (ay - by)){
                for (i = by - 1; i > ay; i--) {
                    if (current->chess[i][bx - i + by] != 'b')
                        return 0;    
                }
                return 1;
            }
            else if(ax - bx < 0 && ax - bx == ay - by){
                for (i = by - 1; i > ay; i--) {
                    if (current->chess[i][bx + i - by] != 'b')
                        return 0; 
                }
                return 1;
            }
            else if (abs(ax - bx) < 2 && abs(ay - by) < 2)
                return 1;
            else
                return 0;
            break;
        case'w':  //步
            if (ay == by + 1 && ax == bx)
                return 1;
            else
                return 0;
            break;
        default:
            return 0;
            break;
        }
    }
    else {
        switch (current->chess[by][bx]) {
        //Player Y's chess
        case'P':
            if (ax == bx && ay < by){
                for (i = by - 1; i > ay; i--) {
                    if (current->chess[i][bx] != 'b')
                        return 0;
                }
                return 1;
            }
            else
                return 0;
            break;
        case'N':
            if (ay == by - 2 && (ax == bx + 1 || ax == bx - 1))
                return 1;
            else
                return 0;
            break;
        case'S':
            if ((ay == by - 1 && ax == bx) || (ay == by - 1 && ax == bx - 1) || (ay == by - 1 && ax == bx + 1) || (ay == by + 1 && ax == bx - 1) || (ay == by + 1 && ax == bx + 1))
                return 1;
            else
                return 0;
            break;
        case'G':
        case'C':
        case'T':
        case'E':
        case'J':
            if ((ay == by - 1 && ax == bx) || (ay == by - 1 && ax == bx - 1) || (ay == by - 1 && ax == bx + 1) || (ay == by + 1 && ax == bx) || (ay == by && ax == bx + 1) || (ay == by && ax == bx - 1))
                return 1;
            else
                return 0;
            break;
        case'K':
            if (abs(ax - bx) < 2 && abs(ay - by) < 2)
                return 1;
            else
                return 0;
            break;
        case'F':
            if (ax == bx && ay > by){
                for (i = by + 1; i < ay; i++) {
                    if (current->chess[i][bx] != 'b')
                        return 0;
                }
                return 1;
            }
            else if (ax == bx && ay < by){
                for (i = by - 1; i > ay; i--) {
                    if (current->chess[i][bx] != 'b')
                        return 0;
                }
                return 1;
            }
            else if ((ay == by && ax > bx)){
                for (i = bx + 1; i < ax; i++) {
                    if (current->chess[by][i] != 'b')
                        return 0;
                }
                return 1;
            }
            else if ((ay == by && ax < bx)){
                for (i = bx - 1; i > ax; i--) {
                    if (current->chess[by][i] != 'b')
                        return 0;
                }
                return 1;
            }
            else
                return 0;
            break;
        case'D':
            if (ax == bx && ay > by){
                for (i = by + 1; i < ay; i++) {
                    if (current->chess[i][bx] != 'b')
                        return 0;
                }
                return 1;
            }
            else if (ax == bx && ay < by){
                for (i = by - 1; i > ay; i--) {
                    if (current->chess[i][bx] != 'b')
                        return 0;
                }
                return 1;
            }
            else if ((ay == by && ax > bx)){
                for (i = bx + 1; i < ax; i++) {
                    if (current->chess[by][i] != 'b')
                        return 0;
                }
                return 1;
            }
            else if ((ay == by && ax < bx)){
                for (i = bx - 1; i > ax; i--) {
                    if (current->chess[by][i] != 'b')
                        return 0;
                }
                return 1;
            }
            else if (abs(ax - bx) < 2 && abs(ay - by) < 2)
                return 1;
            else
                return 0;
            break;
        case'A':
            if(ax - bx > 0 && ax - bx == ay - by){
                for (i = by + 1; i < ay; i++) {
                    if (current->chess[i][bx + i - by] != 'b')
                        return 0;
                } 
                return 1;
            }
            else if(ax - bx < 0 && ax - bx == -(ay - by)){
                for (i = by + 1; i < ay; i++) {
                    if (current->chess[i][bx - i + by] != 'b')
                        return 0;
                }
                return 1; 
            }
            else if(ax - bx > 0 && ax - bx == - (ay - by)){
                for (i = by - 1; i > ay; i--) {
                    if (current->chess[i][bx - i + by] != 'b')
                        return 0;
                }
                return 1;
            }
            else if(ax - bx < 0 && ax - bx == ay - by){
                for (i = by - 1; i > ay; i--) {
                    if (current->chess[i][bx + i - by] != 'b')
                        return 0;
                }
                return 1;
            }
            else
                return 0;
            break;
        case'H':
            if(ax - bx > 0 && ax - bx == ay - by){
                for (i = by + 1; i < ay; i++) {
                    if (current->chess[i][bx + i - by] != 'b')
                        return 0;
                } 
                return 1;
            }
            else if(ax - bx < 0 && ax - bx == -(ay - by)){
                for (i = by + 1; i < ay; i++) {
                    if (current->chess[i][bx - i + by] != 'b')
                        return 0;
                }
                return 1; 
            }
            else if(ax - bx > 0 && ax - bx == - (ay - by)){
                for (i = by - 1; i > ay; i--) {
                    if (current->chess[i][bx - i + by] != 'b')
                        return 0;
                }
                return 1;
            }
            else if(ax - bx < 0 && ax - bx == ay - by){
                for (i = by - 1; i > ay; i--) {
                    if (current->chess[i][bx + i - by] != 'b')
                        return 0;
                }
                return 1;
            }
            else if (abs(ax - bx) < 2 && abs(ay - by) < 2)
                return 1;
            else
                return 0;
            break;
        case'W':
            if (ay == by - 1 && ax == bx)
                return 1;
            else
                return 0;
            break;
        default:
            return 0;
            break;
        }
    }        
}
//Save the thing that the target saved(include 'b')
int eatchess()
{
    int x;
    previous=current;
    current=(NODE*)malloc(sizeof(NODE)); //Create a node to save this step
    //Link the link list
    current->prev=previous;
    current->next=NULL;
    previous->next=current;
    //Save the eaten chess being eaten before
    for(x=0;x<RECORDS/2;x++){
        current->eatenchessx[x]=previous->eatenchessx[x];  
        current->eatenchessy[x]=previous->eatenchessy[x];
    }
    //Save the eaten chess being eaten this step
    switch (previous->chess[by][bx]) {
    case'p':
    case'n':
    case's':
    case'g':
    case'k':
    case'f':
    case'a':
    case'w':
    case'c':
    case't':
    case'e':
    case'j':
    case'd':
    case'h':
        switch (previous->chess[ay][ax]) {
        case'P':
        case'N':
        case'S':
        case'G':
        case'W':
        case'F':
        case'A':
        case'K':
        case'b': 
            current->eatenchessx[numx] = previous->chess[ay][ax];
            numx=numx+1;
            return 1;
            break;
        //The promoted chess should turn back if being eaten
        case'C':
            current->eatenchessx[numx]='P';
            numx=numx+1;
            return 1;
            break;
        case'T':
            current->eatenchessx[numx]='N';
            numx=numx+1;
            return 1;
            break;
        case'E':
            current->eatenchessx[numx]='S';
            numx=numx+1;
            return 1;
            break;

        case'J':
            current->eatenchessx[numx]='W';
            numx=numx+1;
            return 1;
            break;
        case'D':
            current->eatenchessx[numx]='F';
            numx=numx+1;
            return 1;
            break;
        case'H':
            current->eatenchessx[numx]='A';
            numx=numx+1;
            return 1;
            break; 
        default:
            return 0;
            break;
        }
        break;
    case'P':
    case'N':
    case'S':
    case'G':
    case'K':
    case'F':
    case'A':
    case'W':
    case'C':
    case'T':
    case'E':
    case'J':
    case'D':
    case'H':
        switch (previous->chess[ay][ax]) {
        case'p':
        case'n':
        case's':
        case'g':
        case'f':
        case'a':
        case'w':
        case'k':
        case'b':
            current->eatenchessy[numy] = previous->chess[ay][ax];
            numy=numy+1;
            return 1;
            break;
        case'c':
            current->eatenchessy[numy]='p';
            numy=numy+1;
            return 1;
            break;
        case't':
            current->eatenchessy[numy]='n';
            numy=numy+1;
            return 1;
            break;
        case'e':
            current->eatenchessy[numy]='s';
            numy=numy+1;
            return 1;
            break;

        case'j':
            current->eatenchessy[numy]='w';
            numy=numy+1;
            return 1;
            break;
        case'd':
            current->eatenchessy[numy]='f';
            numy=numy+1;
            return 1;
            break;
        case'h':
            current->eatenchessy[numy]='a';
            numy=numy+1;
            return 1;
            break; 
        default:
            return 0;
            break;
        }
        break;
    default:
        return 0;
    }
}
int hitin()
{
    int x,y;
    int tempeatchenchess[20];
    int ordinal,number=0,temp;
    newnode=(NODE*)malloc(sizeof(NODE));
    newnode->next=NULL;
    timerh1();  //Start the timer of hit in
    // timerh1 stop
    scanf("%d",&ordinal);  //Read the chess you want to hit in by entering the ordinal of it in the eatenchess   
    getchar();
    timerh2(); //Start the timer again
    ordinal--; //Change the number into the array number of eatenchess
    if(player==1){
        for(x=0;x<numx;x++){
            if(current->eatenchessx[x]!='b'){
                tempeatchenchess[number]=current->eatenchessx[x];  //tempeatenchess only save the word denote chess in eatenchess(discard 'b')
                if(number==ordinal)  //Find the chess choosen
                    temp=x;  //Save the location of the chess in eatenchess
                number++;
            }
        }
    }
    else{
        for(x=0;x<numy;x++){
            if(current->eatenchessy[x]!='b'){
                tempeatchenchess[number]=current->eatenchessy[x];
                if(number==ordinal)
                    temp=x;
                number++;
            }
        }
    }
    //timerh2 stop
    scanf("%d%d",&ax,&ay); //Read the location you want to hit in to
    getchar();
    //Change to the computer locaton
    ax=-ax+9;  
    ay=ay-1;
    if(current->chess[ay][ax]!='b'){ // If there isn't a chess ,return wrong 
        free(newnode);
        return 0;
    }
    //Remove the chosen chess in eatenchess by change it to 'b'   
    else{
        for(x=0;x<RECORDS/2;x++){
            newnode->eatenchessx[x]=current->eatenchessx[x];
        }
        for(x=0;x<RECORDS/2;x++){
            newnode->eatenchessy[x]=current->eatenchessy[x];
        }
        for(y=0;y<ROW;y++){
            for(x=0;x<COLUMN;x++){
                newnode->chess[y][x]=current->chess[y][x];  //Put the chess into the chessboard
            }
        }
        //The rule of hit in
        switch(tempeatchenchess[ordinal]){
        case'P':
            if(ay==8)
                return 0;
            else{
                previous=current;
                current=newnode;
                current->prev=previous;
                previous->next=current;
                current->chess[ay][ax]='p';
                current->eatenchessx[temp]='b';
                numx++;
                return 1;
            }
        case'N':
            if(ay>6){
                free(newnode);
                return 0;
            }
            else{
                previous=current;
                current=newnode;
                current->prev=previous;
                previous->next=current;
                current->chess[ay][ax]='n';
                current->eatenchessx[temp]='b';
                numx++;
                return 1;
            }
        case'S':
            previous=current;
            current=newnode;
            current->prev=previous;
            previous->next=current;
            current->chess[ay][ax]='s';
            current->eatenchessx[temp]='b';
            numx++;
            return 1;
        case'G':
            previous=current;
            current=newnode;
            current->prev=previous;
            previous->next=current;
            current->chess[ay][ax]='g';
            current->eatenchessx[temp]='b';
            numx++;
            return 1;
        case'W':
            if(ay==8)
                return 0;
            else{
                for(y=0;y<ROW;y++){
                    if(current->chess[y][ax]=='w'){
                        free(newnode);
                        return 0;
                    }
                }
                previous=current;
                current=newnode;
                current->prev=previous;
                previous->next=current;
                current->chess[ay][ax]='w';
                current->eatenchessx[temp]='b';
                numx++;
                return 1;
            }
        case'F':
            previous=current;
            current=newnode;
            current->prev=previous;
            previous->next=current;
            current->chess[ay][ax]='f';
            current->eatenchessx[temp]='b';
            numx++;
            return 1;
        case'A':
            previous=current;
            current=newnode;
            current->prev=previous;
            previous->next=current;
            current->chess[ay][ax]='a';
            current->eatenchessx[temp]='b';
            numx++;
            return 1;
        case'p':
            if(ay==0){
                free(newnode);
                return 0;
            }
            else{
                previous=current;
                current=newnode;
                current->prev=previous;
                previous->next=current;
                current->chess[ay][ax]='P';
                current->eatenchessy[temp]='b';
                numy++;
                return 1;
            }
        case'n':
            if(ay<3){
                free(newnode);
                return 0;
            }
            else{
                previous=current;
                current=newnode;
                current->prev=previous;
                previous->next=current;
                current->chess[ay][ax]='N';
                current->eatenchessy[temp]='b';
                numy++;
                return 1;
            }
        case's':
            previous=current;
            current=newnode;
            current->prev=previous;
            previous->next=current;
            current->chess[ay][ax]='S';
            current->eatenchessy[temp]='b';
            numy++;
            return 1;
        case'g':
            previous=current;
            current=newnode;
            current->prev=previous;
            previous->next=current;
            current->chess[ay][ax]='G';
            current->eatenchessy[temp]='b';
            return 1;
        case'f':
            previous=current;
            current=newnode;
            current->prev=previous;
            previous->next=current;
            current->chess[ay][ax]='F';
            current->eatenchessy[temp]='b';
            numy++;
            return 1;
        case'a':
            previous=current;
            current=newnode;
            current->prev=previous;
            previous->next=current;
            current->chess[ay][ax]='A';
            current->eatenchessy[temp]='b';
            numy++;
            return 1;
        case'w':
            if(ay==0){
                free(newnode);
                return 0;
            }
            else{
                for(y=0;y<ROW;y++){
                    if(current->chess[y][ax]=='W'){
                        free(newnode);
                        return 0;
                    }
                }
                previous=current;
                current=newnode;
                current->prev=previous;
                previous->next=current;
                current->chess[ay][ax]='W';
                current->eatenchessy[temp]='b';
                numy++;
                return 1;
            }
        default:
            free(newnode);
            return 0;
        }
    }
}
void chessmove()
{
    int x,y;
    for(y=0;y<ROW;y++){
        for(x=0;x<COLUMN;x++){
            current->chess[y][x]=previous->chess[y][x];
        }
    }
    current->chess[ay][ax] = current->chess[by][bx];
    current->chess[by][bx] = 'b';
    chessprint();
}
int win()
{
    //If anyone eat 王 or 玉,he is wins
    if (current->eatenchessx[numx-1] == 'K') { 
        printf("\n遊戲結束！玩家X獲勝");
        return 1;
    }
    else if (current->eatenchessy[numy-1] == 'k') {
        printf("\n遊戲結束！玩家Y獲勝");
        return 1;
    }
    else
        return 0;
}
void chessback()
{
    int x;
    NODE *temp;
    //return to last node
    temp=current;
    current=previous;
    previous=previous->prev;
    current->next=NULL;
    if(player==1)
        numy--;
    else
        numx--;
    free(temp); //free the last node's space
}
int chesspromote()
{
    char turn;
    //Rule of shogi promotion
    while(1){
        switch(current->chess[ay][ax]){
        case'p':
            if(ay==8){
                current->chess[ay][ax]='c';
                return 1;
            }
            else if(by>5||ay>5){
                timerp();
                scanf("%c",&turn);
                getchar();
                if(turn=='y'){
                    current->chess[ay][ax]='c';
                    return 1;
                }
                else if(turn=='n'){
                    return 0;
                }
                else{
                    printf("無效指令請重新輸入\n");
                    sleep(1);
                    break;
                }
            }
            else
                return 0;
        case'n':
            if(ay==7||ay==8){
                current->chess[ay][ax]='t';
                return 1;
            }
            else if(by>5||ay>5){
                timerp();
                scanf("%c",&turn);
                getchar();
                if(turn=='y'){
                    current->chess[ay][ax]='t';
                    return 1;
                }
                else if(turn=='n'){
                    return 0;
                }
                else{
                    printf("無效指令請重新輸入\n");
                    sleep(1);
                    break;
                }
            }
            else
                return 0;
        case'w':
            if(ay==8){
                current->chess[ay][ax]='j';
                return 1;
            }
            else if(by>5||ay>5){
                timerp();
                scanf("%c",&turn);
                getchar();
                if(turn=='y'){
                    current->chess[ay][ax]='j';
                    return 1;
                }
                else if(turn=='n'){
                    return 0;
                }
                else{
                    printf("無效指令請重新輸入\n");
                    sleep(1);
                    break;
                }
            }
            else
                return 0; 
        case's':
            if(by>5||ay>5){
                timerp();
                scanf("%c",&turn);
                getchar();
                if(turn=='y'){
                    current->chess[ay][ax]='e';
                    return 1;
                }
                else if(turn=='n'){
                    return 0;
                }
                else{
                    printf("無效指令請重新輸入\n");
                    sleep(1);
                    break;
                }
            }
            else
                return 0;
        case'f':
            if(by>5||ay>5){
                timerp();
                scanf("%c",&turn);
                getchar();
                if(turn=='y'){
                    current->chess[ay][ax]='d';
                    return 1;
                }
                else if(turn=='n'){
                    return 0;
                }
                else{
                    printf("無效指令請重新輸入\n");
                    sleep(1);
                    break;
                }
            }
            else
                return 0;
        case'a':
            if(by>5||ay>5){
                timerp();
                scanf("%c",&turn);
                getchar();
                if(turn=='y'){
                    current->chess[ay][ax]='h';
                    return 1;
                }
                else if(turn=='n'){
                    return 0;
                }
                else{
                    printf("無效指令請重新輸入\n");
                    sleep(1);
                    break;
                }
            }
            else
                return 0;
        case'P':
            if(ay==0){
                current->chess[ay][ax]='C';
                return 1;
            }
            else if(by<3||ay<3){
                timerp();
                scanf("%c",&turn);
                getchar();
                if(turn=='y'){
                    current->chess[ay][ax]='C';
                    return 1;
                }
                else if(turn=='n'){
                    return 0;
                }
                else{
                    printf("無效指令請重新輸入\n");
                    sleep(1);
                    break;
                }
            }
            else
                return 0;
        case'N':
            if(ay==1||ay==0){
                current->chess[ay][ax]='T';
                return 1;
            }
            else if(by<3||ay<3){
                timerp();
                scanf("%c",&turn);
                getchar();
                if(turn=='y'){
                    current->chess[ay][ax]='T';
                    return 1;
                }
                else if(turn=='n'){
                    return 0;
                }
                else{
                    printf("無效指令請重新輸入\n");
                    sleep(1);
                    break;
                }
            }
        case'S':
            if(by<3||ay<3){
                timerp();
                scanf("%c",&turn);
                getchar();
                if(turn=='y'){
                    current->chess[ay][ax]='E';
                    return 1;
                }
                else if(turn=='n'){
                    return 0;
                }
                else{
                    printf("無效指令請重新輸入\n");
                    sleep(1);
                    break;
                }
            }
            else
                return 0;
        case'F':
            if(by<3||ay<3){
                timerp();
                scanf("%c",&turn);
                getchar();
                if(turn=='y'){
                    current->chess[ay][ax]='D';
                    return 1;
                    break;
                }
                else if(turn=='n'){
                    return 0;
                }
                else{
                    printf("無效指令請重新輸入\n");
                    sleep(1);
                    break;
                }
            }
            else
                return 0;
        case'A':
            if(by<3||ay<3){
                timerp();
                scanf("%c",&turn);
                getchar();
                if(turn=='y'){
                    current->chess[ay][ax]='H';
                    return 1;
                    break;
                }
                else if(turn=='n'){
                    return 0;
                }
                else{
                    printf("無效指令請重新輸入\n");
                    sleep(1);
                    break;
                }
            }
            else
                return 0;
        case'W':
            if(ay==0){
                current->chess[ay][ax]='J';
                return 1;
            }
            else if(by<3||ay<3){
                timerp();
                scanf("%c",&turn);
                getchar();
                if(turn=='y'){
                    current->chess[ay][ax]='J';
                    return 1;
                }
                else if(turn=='n'){
                    return 0;
                }
                else{
                    printf("無效指令請重新輸入\n");
                    sleep(1);
                    break;
                }
            }
            else
                return 0;
        default:
            return 0;
        }
    }
}