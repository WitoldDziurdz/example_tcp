#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <zconf.h>

int main() {
    int listener;
    struct sockaddr_in addr;

    int sock = socket(AF_INET, SOCK_STREAM,0);
    if(sock < 0){
        std::cout<< "error socket"<<std::endl;
        exit(1);
    }

    listener = socket(AF_INET, SOCK_STREAM,0);
    if(listener < 0){
        std::cout<< "error socket"<<std::endl;
        exit(1);
    }


    addr.sin_family = AF_INET;
    addr.sin_port = htons(5555);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);


    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        std::cout<< "error connect"<<std::endl;
        exit(2);
    }

    listen(listener, 1);

    while(1){

        sock = accept(listener,NULL,NULL);
        if(sock < 0){
            std::cout<< "error accept"<<std::endl;
            exit(3);
        }

        char buf[1024];
        int bytes_read;
        while(1){
            bytes_read = recv(sock,buf, 1024,0);
            if(bytes_read <= 0) break;
            send(sock, buf, bytes_read,0);
        }
        close(sock);
    }
    close(listener);
    return 0;
}