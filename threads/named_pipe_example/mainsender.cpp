#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

int main()
{
    int fd;
    char* myfifo="/tmp/myfifo";
    mkfifo(myfifo,0666);

    fd=open(myfifo,O_WRONLY);
    write(fd,"Hello World!",sizeof("Hello World!"));
    close(fd);

    unlink(myfifo);
    return EXIT_SUCCESS;
}
