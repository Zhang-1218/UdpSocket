#include <iostream>
#include "UdpSocket.h"

#define CHECK_RET(q) if((q)==false){return false;}

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        std::cout << "arguments error, please input : ./udp_server ip port\n" << std::endl;
        return -1;
    }

    uint16_t port = std::stoi(argv[2]);
    std::string ip = argv[1];

    UdpSocket srv_sock;
    CHECK_RET(srv_sock.Socket());
    CHECK_RET(srv_sock.Bind(ip, port));

    while(1)
    {
        std::string buf;
        std::string clnt_ip;
        uint16_t clnt_port;
        CHECK_RET(srv_sock.Recv(&buf, &clnt_ip, &clnt_port));
        std::cout << "Client [" << clnt_ip << ":" << clnt_port << "] send messages: " << buf << std::endl;
        buf.clear();
        std::cout << "Server send message: ";
        std::cin >> buf;
        CHECK_RET(srv_sock.Send(buf, clnt_ip, clnt_port));
    }
    
    srv_sock.Close();
    return 0;
}

