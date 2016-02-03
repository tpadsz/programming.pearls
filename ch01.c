#include<stdarg.h>
#include<stddef.h>
#include<stdio.h>
#include<errno.h>
#include "ch01.h"

/**
*   Prepares the file which contains 1000000 numbers.
*   If the file already exists, will clear it.
*/
FILE* prepare(){
    FILE* fp=fopen("d:\\numbers.txt","w+");
    if(fp==NULL){
        perror("Failed to open file.");
        exit(1);
    }
    int i;
    for(i=0;i<NUMBERS;i++){
        fprintf(fp,"%d\n",i);
    }
    return fp;
}

/**
*   parameters:
*   void* bitmap, the bitmap buffer which contains all the numbers as individual bits.
*   int bitmapSize, the size of the bitmap.
*   int number, the number to mark. If the number is larger the buffer can hold, returns -1.
*   return: <0 if an error occurs. >=0 if the bit is set.
*/
int markNumber(U8* bitmap, int bitmapSize, int number){

    if(number>=bitmapSize){
        return ERR_OUT_OF_BUFFER;
    }
    int pos=number/8;
    int offset=number%8;

    // TODO set bit.
    U8 byte=(U8)(*(bitmap+pos));
    U8 bit=((U8)1)<<offset;


    if((byte>>offset)%2==1){  // If the bit is already set.
        return number;
    }else{  // If not, set it.

//        if(number==8421119){
//            printf("Set for number %d, pos %d, offset %d, bitmap line: %02X\n",number,pos,offset,*(bitmap+pos));
//        }

        byte+=bit;
        memcpy(bitmap+pos,&byte,1);
        return number;
    }
    return ERR_UNKNOWN;
}

int main(int argc, char* argv[]){
    FILE* fp=prepare();

    U8* bitmap=(U8*)malloc(_BITMAP_SIZE);
    memset(bitmap,0,_BITMAP_SIZE);

    if(bitmap<1){
        perror("Unable to allocate memory.");
        exit(1);
    }

    int result=0xFFFF;
    int number=-1;
    rewind(fp);
    while((result=fscanf(fp,"%d",&number))!=EOF){
        if(markNumber(bitmap,NUMBERS,number)<0){
            perror("Error when set bit.");
            exit(1);
        }
    }

    int i=0;
    for(i;i<NUMBERS;i++){
        printf("%d\n",*(bitmap+i));
    }

    fclose(fp);
    return 0;
}
