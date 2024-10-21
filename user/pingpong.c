#include "../kernel/types.h"
#include "./user.h"

int main(int argc, char *argv[]){
    int cToP[2]; // p[0] is read, p[1] is write
    int pToC[2];

    // pipe creation
    pipe(cToP);
    pipe(pToC);

    int pid=fork();

    //parent execution
    if(pid>0){ 
    char h_byte='h';
    write(pToC[1], &h_byte,1);

    char received_byte;
    read(cToP[0],&received_byte,1);
    //%c doesnt work in xv6 anymore so we are printing the ascii code of the chars
    printf("%d: received ping %d\n",pid,received_byte);
    }

    // child execution
    else if(pid==0){ 
    char received_byte;
    read(cToP[0],&received_byte,1); // read waits for input
    printf("%d: received ping %d\n",getpid(),received_byte);
    received_byte++;
    write(pToC[1], &received_byte,1);

    }


    else{
        fprintf(2,"fork() failed");
    }
    
    exit(0);
}