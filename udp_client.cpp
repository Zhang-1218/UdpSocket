#include <iostream>
#include "UdpSocket.h"

#define CHECK_RET(q) if((q)==false){return false;}

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        std::cout << "arguments error, please input : ./udp_client ip port\n" << std::endl;
        return -1;
    }

    uint16_t srv_port = std::stoi(argv[2]);
    std::string srv_ip = argv[1];

    UdpSocket clnt_sock;
    CHECK_RET(clnt_sock.Socket());

    while(1)
    {
        std::string buf;
        std::cout << "Client send message: ";
        std::cin >> buf;
        CHECK_RET(clnt_sock.Send(buf, srv_ip, srv_port));
        
        buf.clear();
        CHECK_RET(clnt_sock.Recv(&buf));
        std::cout << "Server [" << srv_ip << ":" << srv_port << "] send messages: " << buf << std::endl;
    }

    clnt_sock.Close();

    return 0;
}

