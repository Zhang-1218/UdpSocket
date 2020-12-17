#include "UdpSocket.h"

UdpSocket::UdpSocket()
    :_sockfd(-1)
{}

UdpSocket::~UdpSocket()
{
    _sockfd = -1;
}

bool UdpSocket::Socket()
{
    _sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(_sockfd < 0)
    {
        perror("socket error");
        return false;
    }
    
    return true;
}


bool UdpSocket::Bind(const std::string &ip, const u_int16_t port)
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    socklen_t len = sizeof(addr);
    int ret = bind(_sockfd, (struct sockaddr*)&addr, len);
    if(ret < 0)
    {
        perror("bind error");
        return false;
    }
        
    return true;
}

bool UdpSocket::Recv(std::string *buf, std::string *ip, u_int16_t *port)
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    socklen_t len = sizeof(addr);
    char tmp[1024] = {0};
    int ret = recvfrom(_sockfd, tmp, 1024, 0, (struct sockaddr*)&addr, &len);
    if(ret < 0)
    {
        perror("recvfrom error");
        return false;
    }
    buf->assign(tmp, ret);                      // assign从指定字符串中截取指定长度的数据到目标字符串中中
    if(ip != nullptr)
    {
        *ip = inet_ntoa(addr.sin_addr);    
    }
    if(port != nullptr)
    {
        *port = ntohs(addr.sin_port);
    }

    return true;
}

bool UdpSocket::Send(std::string &data, const std::string &ip, const u_int16_t port)
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    socklen_t len = sizeof(addr);
    int ret = sendto(_sockfd, data.c_str(), data.size(), 0, (struct sockaddr*)&addr, len);
    if(ret < 0)
    {
        perror("send error");
        return false;
    }

    return true;
}

bool UdpSocket::Close()
{
    if(_sockfd > 0)
    {
        close(_sockfd);
    }

    return true;
}


