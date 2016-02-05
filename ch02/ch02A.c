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
*/
FILE* prepare(){
    FILE* fp=fopen("numbers.txt","w+");
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
    return fp;
}

int main(int argc, char* argv[]){

    FILE* fp=prepare();


    fclose(fp);
    return 0;
}
