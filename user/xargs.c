#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"
#define max 1024
void main(int argc,char *argv[])
{
    char line[max];
    char * param[MAXARG];
    int n,argindex=0;
    int i;
    char * cmd=argv[1];
    for(i=1;i<argc;i++)param[argindex++]=argv[i];
    while((n=read(0,line,max))>0)
    {
        if((fork())==0)
        {
            char *arg = (char *)malloc(sizeof (line));
            int index=0;
            for (i=0;i<n;i++)
            {
                if(line[i]==' '||line[i]=='\n')
                {
                    arg[index]=0;
                    param[argindex++]=arg;
                    //不能free掉
                    index=0;
                    arg=(char *)malloc(sizeof(line));
                }
                else arg[index++]=line[i];
            }
            arg[index]=0;
            param[argindex]=0;
            exec(cmd,param);
        }
        else wait((int *)0);
    }
    exit(0);
}