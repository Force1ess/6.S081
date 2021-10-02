#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
void main()
{
    int num[35];
    int pid;
    int index = 0;
    int fd[2];
    for (int i = 2; i <= 35; i++)
    {
        num[index++] = i;
    }
    while (index > 0)
    {
        pipe(fd);
        if ((pid = fork()) < 0)
        {
            fprintf(2, "fork failed");
            exit(-1);
        }
        if (pid == 0)
        {
            close(fd[1]);
            index = -1;
            int temp;
            int prime = 0;
            while (read(fd[0], &temp,sizeof(int)))
            {
                if (index == -1)
                {
                    prime = temp;
                    index++;
                }
                else
                {
                    if (temp % prime != 0)
                    {
                        num[index++] = temp;
                    }
                }
            }
            close(fd[0]);
            printf("prime %d\n", prime);
            //如果把此進程也關閉，整個程序就結束了
        }
        else
        {
            close(fd[0]);
            for (int i = 0; i < index; i++)
            {
                write(fd[1], &num[i], 4);
            }
            close(fd[1]);
            wait((int *)0);
            exit(0);
        }
    }
    exit(0);
}