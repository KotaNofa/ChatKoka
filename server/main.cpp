#include "SFML/Network.hpp"

#include <iostream>
#include <string>
#include <array>
#include <thread>
#include <chrono>

class serverEnv {
    private: 
        sf::TcpListener server;
        std::string ip;
        int port;
        sf::TcpSocket remoteClient;
        bool isBound;
    public:
        serverEnv();
        void bind(std::string ip, int port);
        void accept();
        void update();
        // this would be better served as an enum
        bool bindState();
};

serverEnv::serverEnv() {
    bool isBound = false;
}

bool serverEnv::bindState() {
    return isBound;
}

void serverEnv::bind(std::string ip, int port) {
    std::cout << "### Starting ChatKokaServer" << std::endl;
    if (server.listen(port, ip) != sf::TcpListener::Done) {
        std::cout << "!!! Failed to bind to port" << std::endl;
    } else {
        isBound = true;
        std::cout << "### Successfully bound to listen on port: " << server.getLocalPort() << std::endl;
        
    }
}

void serverEnv::accept() {
    if (server.accept(remoteClient) != sf::TcpListener::Done) {
        std::cout << "!!! Failed to accept client" << std::endl;
    } else {
        std::cout << "### Client connection accepted from: " << remoteClient.getRemoteAddress() << ":" << remoteClient.getRemotePort() << std::endl;
    }
}

void serverEnv::update() {
    sf::Packet chatPacket;
    std::string message;
    std::cout << "hi "<<  std::endl;
    std::cin >> message;
    chatPacket << message;
    remoteClient.send(chatPacket);
    chatPacket.clear();
}

int main() {

    serverEnv server;
    server.bind("127.0.0.1",42069);
    while (server.bindState() == true) {
        server.accept();
        server.update();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }    

    return 0;
}