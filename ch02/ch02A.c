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
    U32b i;
    for(i=0;i<NUMBERS;i++){
        // Using unsigned numbers for programmers
        // to check them clearly.
        fprintf(fp,"%u\n",i);
    }

    fflush(fp);
    return fp;
}

/**
*   Sets bit for target at position pos counting
*   from the higher bits to the lower bits. That
*   is to say, position 0 means the highest (or
*   the right most) bit and position 31 means the
*   lowest (or the left most) bit.
*   int* target, the target number to set bit.
*   pos, pos starting at 0 and must be smaller
*    than sizeof(U32b) or will return
*    ERR_INDEX_OUT_OF_BOUND.
*   returns ERR_NO_ERROR if bit is successfully
*    set or ERR_INDEX_OUT_OF_BOUND.
*
*/
int setBit(U32b* target, U32b pos){
    if(pos<0||pos>=sizeof(U32b)){
        return ERR_INDEX_OUT_OF_BOUND;
    }
    U32b mask=((U32b)HIHEST_U32b_BIT) >> pos;

    if(mask & *target != mask){
        *target+=mask;
    }

    return EER_NO_ERROR;
}


U32b binarySearchMissingNumber(const FILE* fp){

    U32b i;
    U32b ret=0;
    U32b num;
    FILE* fpSmallerPart=fp;
    FILE* fpPartA;
    FILE* fpPartB;
    long long sizeA;
    long long sizeB;
    rewind(fpSmallerPart);
    for(i=0;i<sizeof(U32b);i++){

        U32b mask=((U32b)HIHEST_U32b_BIT)>>i;
        fpPartA=fopen(PART_A_FILENAME,"w");
        fpPartB=fopen(PART_B_FILENAME,"w");

        while(fscanf(fpSmallerPart,"%u",&num)!=EOF){
            if(num & mask == mask){
                fprintf(fpPartA,"%u\n",num);
            }else{
                fprintf(fpPartB,"%u\n",num);
            }
        }
        fflush(fpPartA);
        fflush(fpPartB);
        sizeA=ftell(fpPartA);
        sizeB=ftell(fpPartB);

        fclose(fpSmallerPart);

        if(sizeA>sizeB){
            fpSmallerPart=fpPartB;
            remove(PART_A_FILENAME);
        }else{

            fpSmallerPart=fpPartA;
            remove(PART_B_FILENAME);
            setBit(ret,i);
        }
        rewind(fpSmallerPart);
    }
    remove(PART_A_FILENAME);
    remove(PART_B_FILENAME);

    return ret;
}

int main(int argc, char* argv[]){

    FILE* fp=prepare();
    rewind(fp);

    U32b missing=binarySearchMissingNumber(fp);

    printf("%u",missing);


    fclose(fp);
    /*
    if(remove(CH02A_4B_FILE_NAME)!=0){
        perror("Failed to delete file.");
    }
    */
    return 0;
}
