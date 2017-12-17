#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <zconf.h>

char buf[100];
int main() {
    int sock;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM,0);
    if(sock < 0){
        std::cout<< "error socket"<<std::endl;
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(5555);
    addr.sin_addr.s_addr =htonl(INADDR_LOOPBACK);

    if(connect(sock,(struct sockaddr*)&addr, sizeof(addr))  < 0){
        std::cout<< "error connect"<<std::endl;
        exit(2);
    }

    std::string message;
    while(1) {
        std::cin >> message;
        if(message == "exit") break;
        send(sock, message.c_str(), message.length(), 0);

        recv(sock, buf, sizeof(buf), 0);
        std::cout << buf << std::endl;
    }
    close(sock);
    return 0;
}