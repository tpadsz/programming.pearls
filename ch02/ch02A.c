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
*/
FILE* prepare(){
    FILE* fp=fopen("d:\\numbers.txt","w+");
    if(fp==NULL){
        perror("Failed to open file.");
        exit(1);
    }
    unsigned int i;
    for(i=0;i<NUMBERS;i++){
        fprintf(fp,"%d\n",i);
    }
    return fp;
}

int main(int argc, char* argv[]){

    FILE* fp=prepare();


    fclose(fp);
    return 0;
}
