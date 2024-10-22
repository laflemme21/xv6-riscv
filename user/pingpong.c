#include "../kernel/types.h"
#include "./user.h"

int main(int argc, char *argv[]){
    int cToP[2]; // p[0] is read, p[1] is write
    int pToC[2];

    // pipe creation
    pipe(cToP);
    pipe(pToC);

    int pid=fork();

    // child execution
    if(pid==0){ 
        char charr;
        pid =getpid();
        read(pToC[0],&charr,1);
        printf("%d received %d\n",pid,charr);
        charr++;
        write(cToP[1],&charr,1);
    }
    //parent execution
    else if(pid>0){ 
        pid =getpid();
        char charr='H';
        write(pToC[1],&charr,1);
        wait(0);
        read(cToP[0],&charr,1);
        printf("%d received %d\n",pid,charr);


    }


    else{
        fprintf(2,"fork() failed");
    }
    
    exit(0);
}