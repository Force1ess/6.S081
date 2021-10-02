#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
void main(int argc,char * args[])
{
    if(argc!=2)
    {
        fprintf(2,"You need indicate one number to sleep\n");
        exit(-1);
    }
    else
    {
        sleep(atoi(args[1]));
        exit(0);
    }
}