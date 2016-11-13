#include "apue.h"
#include <fcntl.h>
int main(int argc,char* argv[])
{
  int val;
  if (argc !=2) {
    err_quit("usage: a.out<descriptor#>");
  }
  if ((val=fcntl(atoi(argv[1]),F_GETFL,0))<0){
    err_sys("fcntl error for fd %d",atoi(argv[1]));
    switch (val & O_ACCMODE) {
      case O_RDONLY:
        printf("read only");
        break;
      case O_WRONLY:
        printf("WRITE ONLY\n");
        case O_RDWR:
        printf("READ WRITE\n");
        default:
        err_dump("unknown access mode");
    }
  }
  exit(0);
}
