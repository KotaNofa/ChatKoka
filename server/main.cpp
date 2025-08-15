#include "SFML/Network.hpp"

#include <iostream>
#include <string>
#include <array>
#include <thread>
#include <chrono>

class chatEnv {
    private: 
        sf::TcpListener server;
        std::string ip;
        int port;
        sf::TcpSocket remoteClient;
        bool isBound;
    public:
        chatEnv();
        void bind(std::string ip, int port);
        void accept();
        void update();
        // this would be better served as an enum
        bool bindState();
};

chatEnv::chatEnv() {
    bool isBound = false;
}

bool chatEnv::bindState() {
    return isBound;
}

void chatEnv::bind(std::string ip, int port) {
    std::cout << "### Starting ChatKokaServer" << std::endl;
    if (server.listen(port, ip) != sf::TcpListener::Done) {
        std::cout << "!!! Failed to bind to port" << std::endl;
    } else {
        isBound = true;
        std::cout << "### Successfully bound to listen on port: " << server.getLocalPort() << std::endl;
        
    }
}

void chatEnv::accept() {
    if (server.accept(remoteClient) != sf::TcpListener::Done) {
        std::cout << "!!! Failed to accept client" << std::endl;
    } else {
        std::cout << "### Client connection accepted from: " << remoteClient.getRemoteAddress() << ":" << remoteClient.getRemotePort() << std::endl;
    }
}

void chatEnv::update() {
    
}

int main() {

    chatEnv server;
    server.bind("127.0.0.1",42069);
    while (server.bindState() == true) {
        server.accept();
        server.update();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }    

    return 0;
}