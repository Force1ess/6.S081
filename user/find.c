#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;
  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
  {
    return p;
  }
  memmove(buf, p, strlen(p));
  buf[strlen(p)]=0;
  return buf;
}
int
strcm(const char *p, const char *q)
{
  while(*p && *p == *q)
    p++, q++;
  printf("p:%s\n",*p);
  printf("q:%s\n",*q);
  return (uchar)*p - (uchar)*q;
}
void find(char * path,char * obj)
{
    char buf[512];
    struct stat st;
    struct dirent de;
    char * na;
    int fd;
    if((fd = open(path, 0)) < 0)
    {
    fprintf(2, "find: cannot open %s\n", path);
    return;
    }
    if(fstat(fd, &st) < 0){
    fprintf(2, "find: cannot stat %s\n", path);
    close(fd);
    return;
    }
    switch (st.type)
    {
    case T_FILE:
        na= fmtname(path);
        na[strlen(na)]=0;
        if(strcmp(obj,na)==0)
        {
            printf("%s\n",path);
        }
        break;
    
    case T_DIR:
        if(strlen(path)+1+DIRSIZ+1>sizeof(buf))
        {
            fprintf(2,"find:path too long\n");
            break;
        }
        strcpy(buf,path);
        char *p=buf+strlen(buf);
        *p++='/';
        while(read(fd,&de,sizeof(de))==sizeof(de))
        {
            if(de.inum == 0)continue;
            memmove(p,de.name,sizeof(de.name));
            p[sizeof de.name]=0;
            if(strcmp(de.name,".")==0||strcmp(de.name,"..")==0)
            continue;
            find(buf,obj);
        }
    }
    close(fd);
}
void main (int argc,char * argv[])
{
    if(argc!=3)
    {
        fprintf(2,"find need 2 arguments\n");
        exit(-1);
    }
    else
    {
        find(argv[1],argv[2]);
        exit(0);
    }
}