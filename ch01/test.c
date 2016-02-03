#include<stdarg.h>
#include<stddef.h>
#include<stdio.h>
#include<errno.h>

int test(int argc,char* argv[]){
    FILE* fp=fopen("d:\\numbers.txt","r");


    int number=-1;
    fscanf(fp,"%d",&number);
    printf("%d\n",number);
    fscanf(fp,"%d",&number);
    printf("%d\n",number);

    printf("11 mod 8 = %d\n",11%8);


    fclose(fp);
}
