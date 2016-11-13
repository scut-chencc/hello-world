#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <stdlib.h>
int main(int argc,char* argv[])
{
    if(argc!=2)
    {
        printf("argc is error!\n");
        exit(0);
    }
    int fd=open(argv[1],O_RDONLY);
    if(fd==-1)
    {
        perror("open error");
    }
    struct stat buf;
    int iret=fstat(fd,&buf);
    if(iret==-1)
    {
        perror("fstat error");
    }
    if(S_ISDIR(buf.st_mode))
    {
        printf("this is dirctory!\n");
    }
    printf("the size of the file is:%d\n",buf.st_size);
    time_t tt=buf.st_atime;
    struct tm* pt=gmtime(&tt);
    printf("%4d-%02d-%02d %02d:%02d:%02d\n",(1900+pt->tm_year),(1+pt->tm_mon),pt->tm_mday,(8+pt->tm_hour),pt->tm_min,pt->tm_sec);
    printf("the last access time is :%d\n",buf.st_atime);
    close(fd);
    return 0;
}
