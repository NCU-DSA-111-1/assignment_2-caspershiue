#include "../inc/shogi.h"
#include "../inc/file.h"
#include "../inc/timer.h"

extern char *optarg;
extern int optind, opterr, optopt;

int main(int argc, char **argv)
{
    int mode,status;
    char action;
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
    //the first node
    current=(NODE*)malloc(sizeof(NODE)); 
    current->prev=NULL;
    current->next=NULL;
    first=current;
    if(mode==1){
        chessinitial(); //Initialize the chessboard
    }
    else{
        system("clear");
        readdata(); //Read old game file
        chessprint();
    }
    while(1){
        //Mode 1: creating new game files
        while (mode==1) {
            player = count % 2;  //Determine which player's term
            //Player X's turn
            if (player == 1) {
                timer();  //Start the timer and print it
                scanf("%c", &bx);  //timer stop and get input
                getchar();
                if (bx == '0') {  //Enter 0 to return the chess move
                    chessback();
                    count--;
                    continue;
                }
                else if(bx=='s'||bx=='S'){  //Enter s or S to write the game and the time into a file
                    datawrite();
                    printf(" 遊戲已儲存！\n");
                    sleep(1);
                    continue;
                }
                else if(bx=='h'||bx=='H'){  //Enter h or H to hit in the chess
                    if(hitin()){
                        count++;
                        continue;
                    }
                    else{
                        free(newnode);
                        printf("無法打入\n");
                        sleep(1);
                        continue;
                    }    
                }
                else if(bx=='x'||bx=='X'){  //Enter x or X to end the game
                    fclose(cfptr);
                    return 0;
                }
                else {
                    scanf("%d", &by);
                    getchar();  
                    timerm(); //Start the timer of chessmove
                    scanf("%d%d", &ax, &ay);  //timerm stop and read the location of the target 
                    getchar();
                }
            }
            //Player Y's turn
            else {
                timer();
                scanf("%c", &bx);
                getchar();
                if (bx == '0') {
                    chessback();
                    count--;
                    continue;
                }
                else if(bx=='s'||bx=='S'){
                    datawrite();
                    printf(" 遊戲已儲存！\n");
                    sleep(1);
                    continue;
                }
                else if(bx=='h'||bx=='H'){
                    if(hitin()){
                        count++;
                        continue;
                    }
                    else{
                        free(newnode);
                        printf("無法打入\n");
                        sleep(1);
                        continue;
                    }    
                }
                else if(bx=='x'||bx=='X'){
                    fclose(cfptr);
                    return 0;
                }
                else {
                    scanf("%d", &by);
                    timerm();
                    scanf("%d%d", &ax,&ay);
                    getchar();
                }
            }
            //Chage the location from input to computer location form
            bx = -(bx - 48) + 9; 
            by = by - 1;
            ax = -ax + 9;
            ay = ay - 1;
            if (movecheck() && eatchess()) { //Confirm that if the chess move follows the rule or eat the chess
                system("clear");
                chessmove(); // Print the result of the chess move
                if (current->eatenchessx[numx - 1] == 'K' || current->eatenchessy[numy - 1] == 'k') {   //Confirm that if there is anyone win
                    win();
                    datawrite();    //Save the game and the time to the file
                    fclose(cfptr);  //Close the file
                    return 0;
                }
                //If there is any chance to promotion
                chesspromote();
                count++;
            }
            else {
                printf(" 無效移動，請重新輸入\n");
                sleep(1);
            }
        }
        //Mode 2: reading old game file
        while(mode==2){
            //numx is the max steps of player X, and numy is the max steps of player Y.
            if(count%2==0){
                numx=count/2;  
                numy=numx-1;
            }
            else{
                numx=(count-1)/2;
                numy=numx;
            }
            if(current->next!=NULL && current->prev!=NULL){   
                printf(" 移動下一手請輸入f\n 退回上一手請輸入b\n 繼續玩請輸入p\n 關檔請輸入x\n");
                scanf("%c",&action);
                getchar();
                if(action=='f'||action=='F'){  //Enter f to print the next move 
                    current=current->next;
                    system("clear");
                    chessprint();
                    count++;
                }
                else if(action=='b'||action=='B'){  //Enter f to print the next move 
                    current=current->prev;
                    system("clear");
                    chessprint();
                    count--;
                }
                else if(action=='p'||action=='P'){  //Enter p to play the game basic on this step 
                    mode=1;
                    system("clear");
                    // Read the game time that has been played last time
                    xhour = xusedtime / 3600;
                    xminute = (xusedtime - xhour * 3600)/60;
                    xsecond = xusedtime - xhour * 3600 - xminute * 60;
                    yhour = yusedtime / 3600;
                    yminute = (yusedtime - yhour * 3600)/60;
                    ysecond = yusedtime - yhour * 3600 - yminute * 60;
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
                printf(" 退回上一手請輸入b\n 繼續玩請輸入p\n 關檔請輸入x\n");
                scanf("%c",&action);
                getchar();
                if(action=='f'||action=='F'){
                    printf("無下一手棋\n");
                    sleep(1);
                    system("clear");
                    chessprint();
                }
                else if(action=='b'||action=='B'){
                    current=current->prev;
                    system("clear");
                    chessprint();
                    count--;
                }
                else if(action=='p'||action=='P'){
                    mode=1;
                    system("clear");
                    xhour = xusedtime / 3600;
                    xminute = (xusedtime - xhour * 3600)/60;
                    xsecond = xusedtime - xhour * 3600 - xminute * 60;
                    yhour = yusedtime / 3600;
                    yminute = (yusedtime - yhour * 3600)/60;
                    ysecond = yusedtime - yhour * 3600 - yminute * 60;
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
            else if(current->prev==NULL){    
                printf(" 移動下一手請輸入f\n 繼續遊玩請輸入p\n 關檔請輸入x\n");
                scanf("%c",&action);
                getchar();
                if(action=='f'||action=='F'){
                    current=current->next;
                    system("clear");
                    chessprint();
                    count++;
                }
                else if(action=='b'||action=='B'){
                    printf("無上一手棋\n");
                    sleep(1);
                    system("clear");
                    chessprint();
                }   
                else if(action=='p'||action=='P'){
                    mode=1;
                    system("clear");
                    xhour = xusedtime / 3600;
                    xminute = (xusedtime - xhour * 3600)/60;
                    xsecond = xusedtime - xhour * 3600 - xminute * 60;
                    yhour = yusedtime / 3600;
                    yminute = (yusedtime - yhour * 3600)/60;
                    ysecond = yusedtime - yhour * 3600 - yminute * 60;
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