#pragma once

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>


class UdpSocket
{
public:
    UdpSocket();

    bool Socket();

    bool Bind(const std::string& ip, const u_int16_t port);

    //bool Recv(std::string* buf, std::string* ip, u_int16_t* port);
    bool Recv(std::string *buf, std::string *ip = nullptr, u_int16_t *port = nullptr);

    bool Send(std::string &data, const std::string& ip, const u_int16_t port);

    bool Close();

    ~UdpSocket();

private:
    int _sockfd;
};

