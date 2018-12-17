#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int main_receiver()
{
    int fd;
    char* myfifo="/tmp/myfifo";

    fd=open(myfifo,O_RDONLY);
    char msgbuff[64];
    read(fd,msgbuff,sizeof(msgbuff));
    close(fd);

    printf("Received Message: %s",msgbuff);

    return EXIT_SUCCESS;
}
