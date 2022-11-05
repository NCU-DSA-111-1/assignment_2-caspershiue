#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <unistd.h>
#define PRINT_ATTR_GLI
#define ROW 9
#define COLUMN 9
#define RECORDS 500
#define CHESSNUMBER 20;
void chessinitial();
void chessprint();
void chessmove();
void chessback();
void datawrite();
void readdata();
int chesstransform();
int win();
int movecheck();
int eatchess();
extern char *optarg;
extern int optind, opterr, optopt;
int mode,status;
FILE* cfptr;
int x, y;
int locby,locax,locay,ax, ay, bx, by;
char locbx;
int numx=0, numy=0;
int count=1,player;
char action;
struct node {
    char eatenchessx[RECORDS/2], eatenchessy[RECORDS/2],chess[ROW][COLUMN];
    struct node *next,*prev; 
};
typedef struct node NODE;
NODE *first,*current,*previous;
int main(int argc, char **argv)
{
    while((status=getopt(argc,argv,"ns:l:"))!=-1){   //Select the mode between creating new game files or reading old game files
        switch(status){
        case'n':
            mode=1;
            break;
        case's':
	        if ((cfptr = fopen(optarg, "w+")) == NULL){ //Create new file
		        printf("File could not be opened\n");
                return 0;
            }
            break;
        case'l':
            if ((cfptr = fopen(optarg, "r+")) == NULL){ //Open old file
		        printf("File could not be opened\n");
                return 0;
            }
            mode=2;
            break;
        default:
            return 0;
        }

    }
    current=(NODE*)malloc(sizeof(NODE));
    current->prev=NULL;
    current->next=NULL;
    first=current;
    if(mode==1){
        chessinitial();//Initialize the chessboard
        system("clear");
        chessprint();//Print the chessboard and the chess
    }
    else{
        system("clear");
        readdata();
        current=first;
        chessprint();
    }
    while(1){
        //Mode 1: creating new game files
        while (mode==1) {   
            player = count % 2;  //determine which player's term
            printf(" 悔棋請輸入0\n 儲存先前對弈過程請輸入S\n 關閉遊戲請輸入x\n");
            //Player x's turn
            if (player == 1) {  
                printf(" 玩家X輸入移動棋子的 X 座標與 Y 座標: "); //Enter the location of the chess you want to move
                scanf("%c", &locbx);  //get input
                getchar();
                if (locbx == '0') {  //Enter 0 to return the chess move
                    chessback(); 
                    count--;
                    continue;
                }
                else if(locbx=='s'||locbx=='S'){  //Enter s or S to write the game into a file
                    datawrite();
                    system("clear");
                    chessprint();
                    continue;
                }
                else if(locbx=='x'||locbx=='X'){  //Enter x or X to end the game
                    fclose(cfptr);
                    return 0;
                }
                else {
                    scanf("%d", &locby);  
                    printf(" 玩家X輸入目標 X 座標與 Y 座標: ");
                    scanf("%d%d", &locax, &locay); //Enter the location that the chess move to
                }
            }
            //Player y's turn
            else {
                printf(" 玩家Y輸入移動棋子的 X 座標與 Y 座標: ");  // Player y's turn
                scanf("%c", &locbx);
                getchar();
                if (locbx == '0') {
                    chessback();
                    count--;
                    continue;
                }
                else if(locbx=='s'||locbx=='S'){
                    datawrite();
                    system("clear");
                    chessprint();
                    continue;
                }
                else if(locbx=='x'||locbx=='X'){
                    fclose(cfptr);
                    return 0;
                }
                else {
                    scanf("%d", &locby);
                    printf(" 玩家Y輸入目標 X 座標與 Y 座標: ");
                    scanf("%d%d", &locax, &locay);
                }
            }
            getchar();
            //Chage the location from input to computer location form
            bx = -(locbx - 48) + 9; 
            by = locby - 1;
            ax = -locax + 9;
            ay = locay - 1;
            if (movecheck() && eatchess()) { //Confirm that if the chess move follows the rule or eat the chess
                system("clear");
                chessmove(); // Print the result of the chess move
                if (current->eatenchessx[numx - 1] == 'K' || current->eatenchessy[numy - 1] == 'k') {   //Confirm that if there is anyone win
                    win();
                    datawrite();    //Save the game to the file
                    fclose(cfptr);  //close the file
                    return 0;
                }
                //If there is any chance to promotion
                if(chesstransform()){
                    system("clear");
                    chessprint();
                }
                count++;
            }
            else {
                printf(" 無效移動，請重新輸入\n");
                sleep(1);
                system("clear");
                chessprint();
            }
        }
        //Mode 2: reading old game file
        while(mode==2){   
            if(count%2==0){
                numx=count/2;
                numy=numx-1;
            }
            else{
                numx=(count-1)/2;
                numy=numx;
            }
            if(current->next!=NULL||current->prev!=NULL){   
                printf(" 移動下一手請輸入f\n 退回上一手請輸入r\n 繼續玩請輸入p\n 關檔請輸入x\n");
                scanf("%c",&action);
                getchar();
                if(action=='f'||action=='F'){  //Enter f to print the next move 
                    current=current->next;
                    system("clear");
                    chessprint();
                    count++;
                }
                else if(action=='r'||action=='R'){  //Enter f to print the next move 
                    current=current->prev;
                    system("clear");
                    chessprint();
                    count--;
                }
                else if(action=='p'||action=='P'){  //Enter p to play the game basic on this step 
                    mode=1;
                    system("clear");
                    chessprint();
                }
                else if(action=='x'||action=='X'){  //Enter x to close the file 
                    fclose(cfptr);
                    return 0;
                }
                else{
                printf("無效指令，請重新輸入\n");
                sleep(1);
                system("clear");
                chessprint();
                }
            }
            //On the final step
            else if(current->next==NULL){   
                printf(" 退回上一手請輸入r\n 繼續玩請輸入p\n 關檔請輸入x\n");
                scanf("%c",&action);
                getchar();
                if(action=='f'||action=='F'){
                    printf("無下一手棋\n");
                    sleep(1);
                    system("clear");
                    chessprint();
                }
                else if(action=='r'||action=='R'){
                    current=current->prev;
                    system("clear");
                    chessprint();
                    count--;
                }
                else if(action=='p'||action=='P'){
                    mode=1;
                    system("clear");
                    chessprint();
                }
                else if(action=='x'||action=='X'){
                    fclose(cfptr);
                    return 0;
                }
                else{
                printf("無效指令，請重新輸入\n");
                sleep(1);
                system("clear");
                chessprint();
                }
            }
            //On the first step
            else if(current->prev=NULL){     
                printf(" 移動下一手請輸入f\n 繼續遊玩請輸入p\n 關檔請輸入x\n");
                scanf("%c",&action);
                getchar();
                if(action=='f'||action=='F'){
                    current=current->next;
                    system("clear");
                    chessprint();
                    count++;
                }
                else if(action=='r'||action=='R'){
                    printf("無上一手棋\n");
                    sleep(1);
                    system("clear");
                    chessprint();
                    count--;
                }   
                else if(action=='p'||action=='P'){
                    mode=1;
                    system("clear");
                    chessprint();
                }
                else if(action=='x'||action=='X'){
                    fclose(cfptr);
                    return 0;
                }
                else{
                printf("無效指令，請重新輸入\n");
                sleep(1);
                system("clear");
                chessprint();
                }
            }
        }
    }
}
void chessinitial()
{
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
int movecheck()
{
    int i;
    if (player == 1) {
        switch (current->chess[by][bx]) {
        case'p':
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
        case'n':
            if (ay == by + 2 && (ax == bx + 1 || ax == bx - 1))
                return 1;
            else
                return 0;
            break;
        case's':
            if ((ay == by + 1 && ax == bx) || (ay == by + 1 && ax == bx - 1) || (ay == by + 1 && ax == bx + 1) || (ay == by - 1 && ax == bx - 1) || (ay == by - 1 && ax == bx + 1))
                return 1;
            else
                return 0;
            break;
        
        case'g':
        case'c':
        case't':
        case'e':
        case'j':
            if ((ay == by + 1 && ax == bx) || (ay == by + 1 && ax == bx - 1) || (ay == by + 1 && ax == bx + 1) || (ay == by - 1 && ax == bx) || (ay == by && ax == bx + 1) || (ay == by && ax == bx - 1))
                return 1;
            else
                return 0;
            break;
        case'k':
            if (abs(ax - bx) < 2 && abs(ay - by) < 2)
                return 1;
            else
                return 0;
            break;
        case'f':
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
        case'd':
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
        case'a':
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
        case'h':
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
        case'w':
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
void chessmove()
{
    for(y=0;y<ROW;y++){
        for(x=0;x<COLUMN;x++){
            current->chess[y][x]=previous->chess[y][x];
        }
    }
    current->chess[ay][ax] = current->chess[by][bx];
    current->chess[by][bx] = 'b';
    chessprint();
}
int eatchess()
{   
    previous=current;
    current=(NODE*)malloc(sizeof(NODE));
    current->prev=previous;
    current->next=NULL;
    previous->next=current;
    for(x=0;x<RECORDS/2;x++){
        current->eatenchessx[x]=previous->eatenchessx[x];
        current->eatenchessy[x]=previous->eatenchessy[x];
    }
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
int win()
{
    //If anyone eat 王 or 玉,he is wins
    if (current->eatenchessx[numx-1] == 'K') { 
        printf("\n遊戲結束！玩家1獲勝");
        return 1;
    }
    else if (current->eatenchessy[numy-1] == 'k') {
        printf("\n遊戲結束！玩家2獲勝");
        return 1;
    }
    else
        return 0;
}
void chessback()
{
    current=previous;
    previous=previous->prev;
    current->next=NULL;
    if(player==1)
        numy=numy-1;
    else
        numx=numx-1;
    system("clear");
    chessprint();
}
void datawrite()
{
    rewind(cfptr);
    current=first;
    while(current!=NULL){
        for (x = 0; x < RECORDS/2; x++) {
        fprintf(cfptr, "%c", current->eatenchessx[x]);
        }
        fprintf(cfptr, "\n");
        for (x = 0; x < RECORDS/2; x++){
            fprintf(cfptr, "%c", current->eatenchessy[x]);
        }
        fprintf(cfptr, "\n");
        for(y=0;y<ROW;y++){
            for(x=0;x<COLUMN;x++){
                fprintf(cfptr,"%c",current->chess[y][x]);
            }
        }
        fprintf(cfptr,"\n\n");
        if(current->next==NULL)
            break;
        else
            current=current->next;
    }
    fprintf(cfptr,"0");
    fflush(cfptr);
}
void readdata()
{
    while(!feof(cfptr)){
        fscanf(cfptr, "%s", current->eatenchessx);
         //when read 0, stop reading the file
        if(current->eatenchessx[0]=='0'){
            current=previous;
            current->next=NULL;
            previous=previous->prev;
            return;
        }
        else{
            fscanf(cfptr, "%s", current->eatenchessy);
            fscanf(cfptr,"\n");
            for(y=0;y<ROW;y++){
                for(x=0;x<COLUMN;x++){
                    fscanf(cfptr,"%c",&(current->chess[y][x]));
                }
            }
        previous=current;
        current=(NODE*)malloc(sizeof(NODE));
        current->prev=previous;
        current->next=NULL;
        previous->next=current;
        }
    }
}
int chesstransform()
{
    char turn;
    while(1){
        switch(current->chess[ay][ax]){
        case'p':
            if(ay==8){
                current->chess[ay][ax]='c';
                return 1;
            }
            else if(by>5||ay>5){
                printf("升變請輸入y\n不升變請輸入n\n");
                scanf("%c",&turn);
                getchar();
                if(turn=='y'){
                    current->chess[ay][ax]='c';
                    return 1;
                }
                else if(turn=='n'){
                    system("clear");
                    chessprint();
                    return 0;
                }
                else{
                printf("無效指令請重新輸入\n");
                    sleep(1);
                    system("clear");
                    chessprint();
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
                printf("升變請輸入y\n不升變請輸入n\n");
                scanf("%c",&turn);
                getchar();
                if(turn=='y'){
                    current->chess[ay][ax]='t';
                    return 1;
                }
                else if(turn=='n'){
                    system("clear");
                    chessprint();
                    return 0;
                }
                else{
                    printf("無效指令請重新輸入\n");
                    sleep(1);
                    system("clear");
                    chessprint();
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
                printf("升變請輸入y\n不升變請輸入n\n");
                scanf("%c",&turn);
                getchar();
                if(turn=='y'){
                    current->chess[ay][ax]='j';
                    return 1;
                }
                else if(turn=='n'){
                    system("clear");
                    chessprint();
                    return 0;
                }
                else{
                    printf("無效指令請重新輸入\n");
                    sleep(1);
                    system("clear");
                    chessprint();
                    break;                
                }
            }
            else
                return 0; 
        case's':
            if(by>5||ay>5){
                printf("升變請輸入y\n不升變請輸入n\n");
                scanf("%c",&turn);
                getchar();
                if(turn=='y'){
                    current->chess[ay][ax]='e';
                    return 1;
                }
                else if(turn=='n'){
                    system("clear");
                    chessprint();
                    return 0;
                }
                else{
                    printf("無效指令請重新輸入\n");
                    sleep(1);
                    system("clear");
                    chessprint();
                    break;
                }
            }
            else
                return 0;
        case'f':
            if(by>5||ay>5){
                printf("升變請輸入y\n不升變請輸入n\n");
                scanf("%c",&turn);
                getchar();
                if(turn=='y'){
                    current->chess[ay][ax]='d';
                    return 1;
                }
                else if(turn=='n'){
                    system("clear");
                    chessprint();
                    return 0;
                }
                else{
                    printf("無效指令請重新輸入\n");
                    sleep(1);
                    system("clear");
                    chessprint();
                    break;
                }
            }
            else
                return 0;
        case'a':
            if(by>5||ay>5){
                printf("升變請輸入y\n不升變請輸入n\n");
                scanf("%c",&turn);
                getchar();
                if(turn=='y'){
                    current->chess[ay][ax]='h';
                    return 1;
                }
                else if(turn=='n'){
                    system("clear");
                    chessprint();
                    return 0;
                }
                else{
                    printf("無效指令請重新輸入\n");
                    sleep(1);
                    system("clear");
                    chessprint();
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
                printf("升變請輸入y\n不升變請輸入n\n");
                scanf("%c",&turn);
                getchar();
                if(turn=='y'){
                    current->chess[ay][ax]='C';
                    return 1;
                }
                else if(turn=='n'){
                    system("clear");
                    chessprint();
                    return 0;
                }
                else{
                    printf("無效指令請重新輸入\n");
                    sleep(1);
                    system("clear");
                    chessprint();
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
                printf("升變請輸入y\n不升變請輸入n\n");
                scanf("%c",&turn);
                getchar();
                if(turn=='y'){
                    current->chess[ay][ax]='T';
                    return 1;
                }
                else if(turn=='n'){
                    system("clear");
                    chessprint();
                    return 0;
                }
                else{
                    printf("無效指令請重新輸入\n");
                    sleep(1);
                    system("clear");
                    chessprint();
                    break;
                }
            }
        case'S':
            if(by<3||ay<3){
                printf("升變請輸入y\n不升變請輸入n\n");
                scanf("%c",&turn);
                getchar();
                if(turn=='y'){
                    current->chess[ay][ax]='E';
                    return 1;
                }
                else if(turn=='n'){
                    system("clear");
                    chessprint();
                    return 0;
                }
                else{
                    printf("無效指令請重新輸入\n");
                    sleep(1);
                    system("clear");
                    chessprint();
                    break;
                }
            }
            else
                return 0;
        case'F':
            if(by<3||ay<3){
                printf("升變請輸入y\n不升變請輸入n\n");
                scanf("%c",&turn);
                getchar();
                if(turn=='y'){
                    current->chess[ay][ax]='D';
                    return 1;
                    break;
                }
                else if(turn=='n'){
                    system("clear");
                    chessprint();
                    return 0;
                }
                else{
                    printf("無效指令請重新輸入\n");
                    sleep(1);
                    system("clear");
                    chessprint();
                    break;
                }
            }
            else
                return 0;
        case'A':
            if(by<3||ay<3){
                printf("升變請輸入y\n不升變請輸入n\n");
                scanf("%c",&turn);
                getchar();
                if(turn=='y'){
                    current->chess[ay][ax]='H';
                    return 1;
                    break;
                }
                else if(turn=='n'){
                    system("clear");
                    chessprint();
                    return 0;
                }
                else{
                    printf("無效指令請重新輸入\n");
                    sleep(1);
                    system("clear");
                    chessprint();
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
                printf("升變請輸入y\n不升變請輸入n\n");
                scanf("%c",&turn);
                getchar();
                if(turn=='y'){
                    current->chess[ay][ax]='J';
                    return 1;
                }
                else if(turn=='n'){
                    system("clear");
                    chessprint();
                    return 0;
                }
                else{
                    printf("無效指令請重新輸入\n");
                    sleep(1);
                    system("clear");
                    chessprint();
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