#include "../kernel/types.h"
#include "./user.h"

int main(int argc, char *argv[]){
    printf("%d\n",uptime());
    exit(0);
}