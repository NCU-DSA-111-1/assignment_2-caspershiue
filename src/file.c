#include "../inc/file.h"
#include"shogi.h"

void readdata()
{
    int x,y;
    NODE* temp;
    count=0;

    if (cfptr == NULL) {
        printf("NO FILE PROVIDED.");
        return;
    }

    while(!feof(cfptr)){
        fscanf(cfptr, "%s", current->eatenchessx);
         //when read 0, stop reading the file
        if(current->eatenchessx[0]=='0'){
            temp=current;
            current=previous;
            current->next=NULL;
            previous=previous->prev;
            free(temp);
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
        if(count%2==0)
            numx++;
        else
            numy++;
        count++;
        
    }
    count++;
}
void datawrite()
{
    int x,y;
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