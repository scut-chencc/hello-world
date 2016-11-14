#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

int main(int argc,char* argv[])
{
    char szbuf[32]={0};
    int fd1=open("./a.txt",O_RDWR);
    int fd2=dup(fd1);
    read(fd1,szbuf,4);
    puts(szbuf);
    close(fd1);

    //lseek(fd2,0,SEEK_SET);
    read(fd2,szbuf,sizeof(szbuf));
    puts(szbuf);
    close(fd2);
    /*/--------------------------
    int fd=open("b.txt",O_WRONLY|O_CREAT);
    if(fd==-1)
    {
        perror("open error");
        exit(-1);
    }
    printf("\n");
    close(1);//关闭标准输出;
    int fd3=dup(fd);//fd2分配为未用最低位即１;
    printf("hello world to b.txt\n");//printf指向１即b.txt
    close(fd3);*/
    //---------------------------
	//memset(szbuf,0,32);
    int fda=open("./a.txt",O_RDONLY);
    int fdb=open("./b.txt",O_RDONLY);
	printf("fdb 1th is:%d",fdb);
    int fdbb=dup(fdb);
    int f1=dup2(fda,fdb);
    printf("f1:%d",f1);
    //int f1=dup2(fda,5);
    printf("fda:%d,fdb:%d,fdbb:%d",fda,fdb,fdbb);
    read(fdb,szbuf,sizeof(szbuf)-1);
    printf("result is:%s\n",szbuf);
    close(fda);
    close(fdb);
    close(fdbb);
    close(f1);
    return 0;
}
