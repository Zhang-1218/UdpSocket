
WAL = -g -Wall

ALL:udp_server udp_client

udp_server:udp_server.cpp UdpSocket.cpp
	g++ -std=c++11 $^ -o $@ $(WAL)

udp_client:udp_client.cpp UdpSocket.cpp
	g++ -std=c++11 $^ -o $@ $(WAL)

.PHONY:
clean:
	-rm -rf udp_server udp_client
