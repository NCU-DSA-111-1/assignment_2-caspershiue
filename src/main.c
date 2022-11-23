#include"shogi.h"
#include"file.h"

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
        chessprint();
    }
    while(1){
        //Mode 1: creating new game files
        while (mode==1) {   
            player = count % 2;  //determine which player's term
            printf(" 打入棋子請輸入H\n 悔棋請輸入0\n 儲存先前對弈過程請輸入S\n 關閉遊戲請輸入x\n");
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
                else if(locbx=='h'||locbx=='H'){
                    if(hitin(locay,locax)){
                        system("clear");
                        chessprint();
                        count++;
                        continue;
                    }
                    else{
                        free(newnode);
                        printf("無法打入\n");
                        sleep(1);
                        system("clear");
                        chessprint();
                        continue;
                    }    
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
                else if(locbx=='h'||locbx=='H'){
                    if(hitin(locay,locax)){
                        system("clear");
                        chessprint();
                        count++;
                        continue;
                    }
                    else{
                        free(newnode);
                        printf("無法打入\n");
                        sleep(1);
                        system("clear");
                        chessprint();
                        continue;
                    }    
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
            if(current->next!=NULL && current->prev!=NULL){   
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
                else if(action=='r'||action=='R'){
                    printf("無上一手棋\n");
                    sleep(1);
                    system("clear");
                    chessprint();
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