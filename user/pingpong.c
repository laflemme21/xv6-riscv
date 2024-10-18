#include "../kernel/types.h"
#include "./user.h"

int main(int argc, char *argv[]){
    int cToP[2];
    int pToC[2];
    // pipe creation
    pipe(cToP);
    pipe(pToC);

    int pid=fork();

    //child execution
    if(pid==0){ 
    char *ping="";
    int fdC;
    //closing the read end of the child to parent pipe
    close(cToP[0]);

    close(0);
    fdC=dup(pToC[0]);
    sleep(20);
    read(fdC,ping,2);
    //writing on the c to p pipe
    printf("%d: received ping %s\n",getpid(),ping);
    write(cToP[1],"i",1);
    }

    // parent execution
    else if(pid>0){ 
    char *pong="";
    int fdP;
    //closing the read end of the parent to child pipe
    close(pToC[0]);
    //writing on the p to c pipe
    write(pToC[1],"h",1);
    sleep(60);

    close(0);
    fdP=dup(cToP[0]);
    read(fdP,pong,2);

    printf("%d: received pong %s\n",getpid(),pong);
    }

    else{
        fprintf(2,"fork() failed");
    }
    exit(0);
}