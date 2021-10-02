#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
void main(int argc,char * argv[])
{
    char buf[10];

    if(argc!=1)
    {
        fprintf(2,"pingpong needs no data");
        exit(-1);
    }
    int rpw[2];
    int wpr[2];
    pipe(rpw);
    pipe(wpr);
    if(fork()==0)
    {
        close(rpw[0]);
        close(wpr[1]);
        read(wpr[0],buf,4);
        printf("%d: received %s\n",getpid(),buf);
        write(rpw[1],"pong",4);
        close(rpw[0]);
        exit(0);
    }
    else
    {
        close(rpw[1]);
        close(wpr[0]);
        write(wpr[1],"ping",4);
        close(wpr[1]);
        read(rpw[0],buf,4);
        printf("%d: received %s\n",getpid(),buf);
        exit(0);
    }
}