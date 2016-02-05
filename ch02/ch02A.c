#include "ch02A.h"
#include<stdarg.h>
#include<stddef.h>
#include<stdio.h>
#include<errno.h>
#include"../include/tpad_errno.h"
#include"../include/tpad_types.h"


/**
*   Prepares the file which contains <NUMBERS> numbers.
*   If the file already exists, will clear it.
*   Buckle up! In this problem, NUMBERS is 4 billion and
*   this function produces a text file with 42GB in size!
*   Check your disk space first!
*   Alternatively, this function also checks whether the
*   CH02A_4B_FILE_NAME file which is supposed to contain
*   the 4 billion numbers already exists. If it does,
*   this function will use it regardless its real content.
*/
FILE* prepare(){
    FILE* fp=NULL;

    if((fp=fopen(CH02A_4B_FILE_NAME,"r"))!=NULL){
        return fp;
    }

    fp=fopen(CH02A_4B_FILE_NAME,"w+");
    if(fp==NULL){
        perror("Failed to open file.");
        exit(1);
    }
    unsigned int i;
    for(i=0;i<NUMBERS;i++){
        // Using unsigned numbers for programmers
        // to check them clearly.
        fprintf(fp,"%u\n",i);
    }

    fflush(fp);
    return fp;
}

int main(int argc, char* argv[]){

    FILE* fp=prepare();
    rewind(fp);


    fclose(fp);



    if(remove(CH02A_4B_FILE_NAME)!=0){
        perror("Failed to delete file.");
    }

    return 0;
}
