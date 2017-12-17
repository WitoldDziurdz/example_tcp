#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <zconf.h>

char msg1[] = "Hello there!\n";
char msg2[] = "Datagram nr1 connect\n";
char msg3[] = "Datagram nr2 connect\n";
char msg4[] = "Bay\n";

int main()
{
    int sock;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        std::cout << "socket"<<std::endl;
        //exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3333);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    sendto(sock, msg1, sizeof(msg1), 0,
           (struct sockaddr *)&addr, sizeof(addr));

    connect(sock, (struct sockaddr *)&addr, sizeof(addr));
    send(sock, msg2, sizeof(msg2), 0);

    send(sock, msg3, sizeof(msg3), 0);
    send(sock, msg4, sizeof(msg4), 0);

    close(sock);

    return 0;
}
