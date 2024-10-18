#include "../kernel/types.h"
#include "./user.h"

int main(int argc, char *argv[]){

    if(argc>2){
        write(2,"Too many arguments\n",20);
        exit(1);
    }
    else if(argc<2){
        write(2,"No command line argument\n",26);
        exit(1);
    }

    int num=atoi(argv[1]);

    printf("Sleeping..\n");
    sleep(num);
    exit(0);




}